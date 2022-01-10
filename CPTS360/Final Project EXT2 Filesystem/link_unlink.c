#include "globals.h"
#include "functions.h"

int my_link(char* arg1, char* arg2)
{
    printf("%s\n\n", arg2);
    char* ofname = basename(strdup(arg1));

    char* ndname = dirname(strdup(arg2));
    char* nfname = basename(strdup(arg2));

    int oino = getino(ofname);
    MINODE* omip = iget(dev, oino);

    // permission check - oldfile
    if (!my_access(arg1, 'r') || !my_access(arg1, 'w') || !my_access(arg1, 'x'))
    {
        printf("my_link: permission to %s denied\n", ofname);
        return -1;
    }
    

    if(S_ISDIR(omip->INODE.i_mode))
    {
        printf("Cannot link to directory. Link failed\n");
        return 0;
    }
    if(getino(arg2))
    {
        printf("Link file already exists. Link failed\n");
        return 0;
    }
    if(!getino(ofname))
    {
        printf("Link destination does not exist. Link failed\n");
        return 0;
    }

    int npino = getino(ndname);
    MINODE* npmip = iget(dev, npino);

    if (!my_access(ndname, 'r') || !my_access(ndname, 'w') || !my_access(ndname, 'x'))
    {
        printf("my_link: permission to %s denied\n", ndname);
        return -1;
    }

    enter_name(npmip, oino, nfname);
    printf("Created new linked file in dir=%s\n", ndname);
    omip->INODE.i_links_count++;
    printf("Link count: %d\n", omip->INODE.i_links_count);
    omip->dirty = 1;
    iput(omip);
    iput(npmip);
    return 1;
}

int my_unlink(char* filename)
{
    int ino = getino(filename);
    MINODE* mip = iget(dev, ino);

    // permission check
    if (mip->INODE.i_uid != running->uid)
    {
        printf("my_unlink: permission to %s denied. Not owner\n", filename);
        return -1;
    }

    char buff[BLKSIZE];
    get_block(dev, mip->INODE.i_block[0], buff);
    DIR* test = (DIR*)buff;
    printf("Link to: %s\n", test->name);

    if(S_ISDIR(mip->INODE.i_mode))
    {
        printf("Cannnot unlink directory. Unlink failed\n");
        return 0;
    }
    char* pname = dirname(strdup(filename));
    char* cname = basename(strdup(filename));

    int pino = getino(pname);
    MINODE* pmip = iget(dev, pino);
    rm_child(pmip, cname);

    pmip->dirty = 1;
    iput(pmip);
    mip->INODE.i_links_count--;
    if(mip->INODE.i_links_count > 0)
        mip->dirty = 1;
    else
    {
        bdalloc(dev, mip->INODE.i_block[0]);
        idalloc(dev, ino);
    }
    iput(mip);
    printf("Old file link count: %d\n", mip->INODE.i_links_count);

    return 0;
}

int my_symlink(char* arg1, char* arg2)
{
    char* ofname = basename(strdup(arg1));

    char* ndname = dirname(strdup(arg2));
    char* nfname = basename(strdup(arg2));

    int oino = getino(ofname);
    
    if(getino(arg2))
    {
        printf("Link file already exists. Link failed\n");
        return 0;
    }
    if(!getino(ofname))
    {
        printf("Link destination does not exist. Link failed\n");
        return 0;
    }

    int npino = getino(ndname);
    MINODE* npmip = iget(dev, npino);

    int nino = ialloc(dev);

    printf("Setting symbolic link to file %s...\n", ofname);
    MINODE* nmip = iget(dev, nino);

    nmip->INODE.i_uid = running->uid;
    nmip->INODE.i_gid = running->gid;
    nmip->INODE.i_size = 0;
    nmip->INODE.i_links_count = 1;
    nmip->INODE.i_atime = nmip->INODE.i_ctime = nmip->INODE.i_mtime = time(0L);
    nmip->INODE.i_blocks = 0;

    nmip->INODE.i_mode = 0xA1FF;
    if(S_ISLNK(nmip->INODE.i_mode))
    {
        printf("Created new symbolic linked file in dir=%s\n", ndname);
    }
    else
    {
        printf("File created but link failed. File i_mode bits:\n");
        u16 fail = nmip->INODE.i_mode;
        for(int bit=0;bit<(sizeof(unsigned int) * 8); bit++)
        {
            printf("%i ", fail & 0x1);
            fail = fail >> 1;
        }
        printf("\n");
        return 0;
    }
    char buf[BLKSIZE];

    get_block(dev, nmip->INODE.i_block[0], buf);

    put_block(dev, nmip->INODE.i_block[0], ofname);
    nmip->INODE.i_size = strlen(ofname);

    enter_name(npmip, nino, nfname);

    nmip->dirty = 1;
    iput(nmip);

    npmip->dirty = 1;
    iput(npmip);
    return 1;
}

int my_readlink(char* filename, char* buf)
{
    char* cname = basename(strdup(filename));

    printf("Link name: %s\n", cname);

    int ino = getino(filename);
    MINODE* mip = iget(dev, ino);

    if(!S_ISLNK(mip->INODE.i_mode))
    {
        printf("Given file is not a symlink. readlink failed.\n");
        return 0;
    }

    get_block(dev, mip->INODE.i_block[0], buf);
    printf("Link read\nLinked name: %s\nLinked size: %d\n", buf, mip->INODE.i_size);

    return mip->INODE.i_size;
}