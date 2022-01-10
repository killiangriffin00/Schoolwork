#include "globals.h"
#include "functions.h"


int my_open(char* filename, int mode)
{
    int ino = getino(filename);
    if (!ino)
    {
        printf("my_open: File %s does not exist. Creating new file %s...\n", filename, filename);
        my_creat(filename);
        ino = getino(filename);
    }
    MINODE* mip = iget(dev, ino);

    if (!my_access(filename, mode))
    {
        printf("open: permission to %s denied\n", filename);
        return -1;
    }


    // ensure filename points to a regular file
    // TODO: Add check to see if file is already open with an incompatiable mode
    if (!S_ISREG(mip->INODE.i_mode))
    {
        printf("my_open: %s does not lead to a regular file\n", filename);
        return -1;
    }


    printf("my_open: Creating and initializing OFT for file %s...\n", filename);
    OFT* table = malloc(sizeof(OFT)); 
    table->mode = mode; // initializing table
    table->minodePtr = mip;
    table->refCount = 1;

    switch(mode)
    {
        case 2: // file must be emptied for write mode
            my_truncate(mip);
            table->offset = 0;
            break;
        case 3: // offset must be set to the size of the file for append
            table->offset = mip->INODE.i_size; 
            break;
        default: // offset is 0 for all other modes
            table->offset = 0;
            break;
    }

    int i = 0;
    while(running->fd[i]) // iterate to first available index in proc fd
        ++i;

    printf("my_open: Inserting OFT into current running process pid=%d...\n", running->pid);
    running->fd[i] = table; // table is inserted there

    if(mode > 0)
        mip->INODE.i_mtime = time(0L);
    mip->INODE.i_atime = time(0L);
    mip->dirty = 1;

    //pfd();
    return i;
}



int my_truncate(MINODE* mip)
{
    for(int i = 0; i < 12; ++i)
        mip->INODE.i_block[i] = 0;
    mip->INODE.i_mtime = mip->INODE.i_atime = time(0L);
    mip->INODE.i_size = 0;
    mip->dirty = 1;
    return 1;
}

int my_lseek(int fd, u32 position)
{
    if(!validatefd(fd))
    {
        printf("Invalid file descriptor %d. my_lseek failed\n", fd);
        return -1;
    }

    int orig = running->fd[fd]->offset;
    if(position < running->fd[fd]->minodePtr->INODE.i_size)
    {
        running->fd[fd]->offset;
        pfd();
        return orig;
    }
    printf("New offset exceeds file size of ino=%d. my_lseek failed\n", running->fd[fd]->minodePtr->ino);
    return -1;
}

int my_close(int fd)
{
    if(!validatefd(fd))
    {
        printf("my_close: Invalid file descriptor %d. close failed\n", fd);
        return 0;
    }

    --running->fd[fd]->refCount; // decrement the file's refcount

    if(!running->fd[fd]->refCount)
    { 
        printf("my_close: Final process pointing to file ino=%d. Releasing file...\n", running->fd[fd]->minodePtr->ino);   
        iput(running->fd[fd]->minodePtr);
    }
    running->fd[fd] = 0;
    //pfd();

    return 0;
}

int pfd()
{
    printf("fd\tmode\toffset\tINODE\n");
    printf("----\t----\t----\t----\n");
    char* mode = "";
    int i = 0;
    while(running->fd[i])
    {
        switch(running->fd[i]->mode)
        {
            case 0:
                strcpy(mode, "READ");
                break;
            case 1:
                strcpy(mode, "WRITE");
                break;
            case 2:
                strcpy(mode, "RDWR");
                break;
            case 3:
                strcpy(mode, "APEND");
                break;
        }
        printf("%d\t%s\t%d\t[ %d %d ]\t\n", i, mode, running->fd[i]->offset, running->fd[i]->minodePtr->dev, running->fd[i]->minodePtr->ino);
        i++;
    }
    printf("----\t----\t----\t----\n");
    return 0;
}


int validatefd(int fd)
{
    return running->fd[fd] != 0;

    // ! This only checks the first fd spot
    /*
    for(int i = 0; i < NFD; ++i) // fd input validation
    {
        if(running->fd[i])
            return 1;
        else
            return 0;
    }
    return 0;
    */
}

// might be needed: in 360 open/close 
// dup(int fd)
// dup2(int fd, int gd)
