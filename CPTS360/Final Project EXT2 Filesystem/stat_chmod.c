#include "functions.h"
#include "globals.h"

void my_stat(char* pathname)
{
    struct stat myst;
    int ino = getino(pathname);
    MINODE* mip = iget(dev, ino);
    myst.st_dev = dev;
    myst.st_ino = ino;

    // copy mip fields into myst
    myst.st_mode = mip->INODE.i_mode;
    myst.st_uid = mip->INODE.i_uid;
    myst.st_size = mip->INODE.i_size;
    myst.st_atime = mip->INODE.i_atime;
    myst.st_ctime = mip->INODE.i_ctime;
    myst.st_mtime = mip->INODE.i_mtime;
    myst.st_gid = mip->INODE.i_gid;
    myst.st_nlink = mip->INODE.i_links_count;
    myst.st_blocks = mip->INODE.i_blocks;

    char* mode = "";
    if (S_ISREG(myst.st_mode))
        strcpy(mode, "regular file");
    else if (S_ISDIR(myst.st_mode))
        strcpy(mode, "directory");
    else
        strcpy(mode, "link");


    // print info
    printf("File: %s\n", basename(pathname));
    printf("Size: %ld\tBlocks: %ld\tIO Block: %d\t %s\n", 
        myst.st_size, myst.st_blocks, BLKSIZE, mode);
    printf("Device: %d\tInode: %ld\tLinks: %ld\n", 
        dev, myst.st_ino, myst.st_nlink);
    printf("Access: %s\tUid: ( %d/ %s)\tGid:( %d/ %s)\n", 
        "", myst.st_uid, "", myst.st_gid, "");
//    printf("Access: %s\nModify: %s\nChange: %s\nBirth: %s\n",
//        myst.st_atime, myst.st_mtime, myst.st_ctime, "-");

    iput(mip);
}