#include "globals.h"
#include "functions.h"

MOUNT* getmptr(int dev)
{
    for(int i = 0; i < NMTABLE; ++i)
    {
        if(mtable[i].dev == dev)
            return &mtable[i];
    }
    return 0;
}

int my_mount(char* filesys, char* mp)
{
    if(strcmp(filesys, "") == 0 && strcmp(mp, "") == 0)
    {
        printf("Filesystems: \n");
        printf("---------------------------------\n");
        for(int i = 0; mtable[i].dev != 0; ++i)
            printf("%s \t STATUS: %d\n", mtable[i].mntName, mtable[i].dev == dev);
        printf("---------------------------------\n\n");
        return 0;
    }

    MOUNT* mt = NULL;
    
    for(int i = 0; mtable[i].dev != 0; ++i)
    {
        if(strcmp(mtable[i].mntName, filesys) == 0)
        {
            printf("h\n");
            mt = &mtable[i];
        }
    }

    if(mt)
    {
        if(mt->mntDirPtr->mounted)
        {
            printf("Filesystem already mounted. mount failed\n");
            return 1;
        }
    }

    mt = (MOUNT*)malloc(sizeof(MOUNT));

    mt->dev = open(filesys, O_RDWR);
    char buf[BLKSIZE];
    get_block(mt->dev, 1, buf);
    SUPER* sp = (SUPER*)buf;
    if (sp->s_magic != 0xEF53)
    {
        printf("magic = %x is not an ext2 filesystem. mount failed\n", sp->s_magic);
        return 1;
    }

    int ino = getino(mp);
    MINODE* mip = iget(dev, ino);

    if(!S_ISDIR(mip->INODE.i_mode))
    {
        printf("%s is not a directory. mount failed\n", mp);
        return 1;
    }
    if(running->cwd == mip)
    {
        printf("%s is busy. mount failed\n", mp);
        return 1;
    }

    for(int i = 0; i < NMTABLE; ++i)
    {
        if(mtable[i].dev == 0)
        {
            GD* gp;
            mtable[i].dev = mt->dev;
            strcpy(mtable[i].mntName, filesys);
            mtable[i].ninodes = sp->s_inodes_count;
            mtable[i].nblocks = sp->s_blocks_count;
            get_block(mt->dev, 2, buf);
            gp = (GD*) buf;
            mtable[i].bmap = gp->bg_block_bitmap;
            mtable[i].imap = gp->bg_inode_bitmap;
            mtable[i].iblock = gp->bg_inode_table;
            mip->mntPtr = &mtable[i];
            mtable[i].mntDirPtr = mip;
            mip->mounted = 1;
            return 0;
        }
    }
    printf("No space in mount table. mount failed\n");
    return 1;
}

int my_umount(char* filesys)
{
    MOUNT* mp = NULL;
    for(int i = 0; i < NMTABLE; ++i)
    {
        if(strcmp(mtable[i].mntName, filesys) == 0 && mtable[i].mntDirPtr->mounted)
        {
            mp = &mtable[i];
            goto success;
        }
    }
    printf("File system not mounted. umount failed\n");
    return 1;
    
    success:
    if(running->cwd->dev == mp->dev)
    {
        printf("File system is busy. umount failed\n");
        return 1;
    }

    mp->mntDirPtr->mounted = 0;

    iput(mp->mntDirPtr);
    return 1;
}





