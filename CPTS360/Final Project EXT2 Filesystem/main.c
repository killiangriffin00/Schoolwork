#include "functions.h"
#include "globals.h"

void quit()
{
    for (int i = 0; i < NMINODE; i++)
    {
        MINODE *mip = &minode[i];
        if (mip->refCount && mip->dirty)
        {
            mip->refCount = 1;
            iput(mip);
        }
    }
    for(int i = 1; i < NMTABLE; ++i)
    {
        if(mtable[i].dev != 0)
        {
            close(mtable[i].dev);
        }
    }
    exit(0);
}


void fs_init()
{
    for (int i = 0; i < NMINODE; i++)       // init all minodes as FREE
        minode[i].refCount = 0;
    for (int i = 0; i < NMTABLE; i++)       // init mtables as FREE
        mtable[i].dev = 0;
    for (int i = 0; i < NOFT; i++)          // init ofts as FREE
        oft[i].refCount = 0;
    for (int i = 0; i < NPROC; ++i)         // init PROCs
    {
        proc[i].status = READY;             // ready to RUN
        proc[i].pid = i;                    // pid = 0 to NPROC-1
        proc[i].uid = i;                    // P0 is a superuser process
        for (int j = 0; j < NFD; j++)     
            proc[i].fd[j] = 0;              // all file descriptors are NULL
        proc[i].next = &proc[i+1];          // link list
    }
    proc[NPROC - 1].next = &proc[0];        // circular list
    running = &proc[0];                     // P0 runs first
}

void mount_root()
{
    printf("mount_root()\n");
    mtable[0].dev = dev;
    strcpy(mtable[0].mntName, "root");
    mtable[0].ninodes = ninodes;
    mtable[0].nblocks = nblocks;
    mtable[0].bmap = bmap;
    mtable[0].imap = imap;
    mtable[0].iblock = iblk;
    root = iget(dev, 2);
}

int main(int argc, char *argv[])
{
    char buf[BLKSIZE];
    if (argc < 2)
    {
        printf("Please enter a disk name as an argument\n");
        exit(0);
    }

    printf("checking EXT2 FS....\n");
    if ((fd = open(argv[1], O_RDWR)) < 0)
    {
        printf("open %s failed\n", argv[1]);
        exit(1);
    }

    dev = fd;   // global dev same as this fd
    rootdev = fd;
    
    // read super block
    get_block(dev, 1, buf);
    sp = (SUPER *)buf;

    // verify it's an ext2 filesystem
    if (sp->s_magic != 0xEF53)
    {
        printf("magic = %x is not an ext2 filesystem\n", sp->s_magic);
        exit(1);
    }

    printf("EXT2 FS OK\n");
    ninodes = sp->s_inodes_count;
    nblocks = sp->s_blocks_count;


    // get group descriptor
    get_block(dev, 2, buf);
    gp = (GD *)buf;

    bmap = gp->bg_block_bitmap;
    imap = gp->bg_inode_bitmap;
    iblk = gp->bg_inode_table;
    printf("bmp=%d imap=%d inode_start=%d\n", bmap, imap, iblk);

    fs_init();
    mount_root();
    printf("root refCount = %d\n", root->refCount);

    printf("creating P0 as running process\n");
    running = &proc[0];
    running->status = READY;
    running->cwd = iget(dev, 2);
    printf("root refCount = %d\n", root->refCount);

    // TODO: WRITE CODE HERE TO CREATE P1 AS A USER PROCESS

    while (1)
    {
        char* args[BLKSIZE];
        printf("input command : [ls|cd|pwd|mkdir|creat|rmdir|link|unlink|symlink|readlink|cp|cat|mount|umount|quit] ");
        fgets(line, 128, stdin);
        line[strlen(line) - 1] = 0;

        if (line[0] == 0)
            continue;
        pathname[0] = 0;

        strcpy(cmd, "");
        strcpy(pathname, "");
       
        args[0] = strtok(line, " ");
        int argCount = 1;
        while (1)
        {
            args[argCount] = strtok(NULL, " ");
            if (!args[argCount])
                break;
            argCount++;
        }


        if (args[0])
        {
            strcpy(cmd, args[0]);
            if (args[1])
                strcpy(pathname, args[1]);
        }
        else
            printf("need to enter a cmd at a minimum");

        
        
        if (strcmp(cmd, "ls") == 0)
            ls(pathname);
        else if (strcmp(cmd, "cd") == 0)
            cd(pathname);
        else if (strcmp(cmd, "pwd") == 0)
            pwd(running->cwd);
        else if (strcmp(cmd, "mkdir") == 0)
            my_mkdir(pathname);
        else if (strcmp(cmd, "creat") == 0)
            my_creat(pathname);
        else if(strcmp(cmd, "link") == 0)
            my_link(pathname, args[2]);
        else if(strcmp(cmd, "unlink") == 0)
            my_unlink(pathname);
        else if(strcmp(cmd, "symlink") == 0)
            my_symlink(pathname, args[2]);
        else if(strcmp(cmd, "readlink") == 0)
        {
            char buffer[BLKSIZE];
            my_readlink(pathname, buffer);
        }
        else if (strcmp(cmd, "rmdir") == 0)
            my_rmdir(pathname);
        else if (strcmp(cmd, "stat") == 0)
            my_stat(pathname);
        else if (strcmp(cmd, "cp") == 0)
        {
            if (args[2])
            {
                my_cp(pathname, args[2]);
            }
        }
        else if (strcmp(cmd, "cat") == 0)
        {
            my_cat(pathname);
        }
        else if (strcmp(cmd, "mount") == 0)
        {
            if(pathname[0] == 0 && !args[2])
            {
                printf("h\n");
                my_mount("", "");
            }
            my_mount(pathname, args[2]);
        }    
        else if (strcmp(cmd, "umount") == 0)
            my_umount(pathname);
        else if (strcmp(cmd, "open") == 0)
        {
            if (args[1] && args[2])
                my_open(args[1], atoi(args[2]));
            else
                printf("Too few args for open\n");
        }
        else if (strcmp(cmd, "read") == 0)
        {
            char b[BLKSIZE];
            if (args[1] && args[2])
            {
                my_read(atoi(args[1]), b, atoi(args[2]));
                printf("read: %s\n", b);
            }
            else
                printf("Too few args for read\n");
        }
        else if (strcmp(cmd, "write") == 0)
        {
            char b[BLKSIZE];
            if (args[1] && args[2])
            {
                args[2][strlen(args[2])] = 0;
                strcpy(b, args[2]);
                my_write(atoi(args[1]), b, strlen(b));
            }
        }
        else if (strcmp(cmd, "close") == 0)
        {
            if (args[1])
                my_close(atoi(args[1]));
            else
                printf("Too few arguments for close\n");
        }
        else if (strcmp(cmd, "quit") == 0)
            quit();
    }
}


