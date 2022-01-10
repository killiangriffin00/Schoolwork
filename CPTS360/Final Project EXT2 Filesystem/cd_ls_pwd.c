#include "functions.h"
#include "globals.h"

char *t1 = "xwrxwrxwr-------";
char *t2 = "----------------";

void cd(char* path)
{
    int ino;
    if (path[0] == 0)
        ino = running->cwd->ino;
    else
        ino = getino(path);
    
    if (!ino)
    {
        printf("path %s not found\n", path);
        return;
    }

    MINODE *mip;

    printf("current dev: %d\n", dev);
    if(running->cwd->ino == 2 && dev != rootdev && strcmp(name[0], "..") == 0)
    {
        printf("new dev: %d\n", rootdev);
        dev = rootdev;
        running->cwd = getmptr(dev)->mntDirPtr;
    }

    mip = iget(dev, ino);
    
    if (!S_ISDIR(mip->INODE.i_mode))
    {
        printf("node with ino %d is not a DIR\n", ino);
        return;
    }
    if (my_access(path, 'x') && my_access(path, 'r'))
    {
        iput(running->cwd);
        if(mip->mounted)
        {
            running->cwd = iget(mip->mntPtr->dev, 2);
            dev = running->cwd->dev;
            printf("Mounted file. New dev: %d\n", dev);
            return;
        }
        running->cwd = mip;
    }
    else
    {
        printf("cd: permission to %s denied\n", path);
    }
}

void ls_file(MINODE *mip, char *name)
{
    struct stat i_stat, *sp;
    sp = &i_stat;
    fstat(mip->ino, &i_stat);

    if (S_ISDIR(mip->INODE.i_mode))
        putchar('d');
    else if (S_ISREG(mip->INODE.i_mode))
        putchar('-');
    else if (S_ISLNK(mip->INODE.i_mode))
        putchar('l');
    
    for (int i = 8; i >= 0; --i)
    {
        if (mip->INODE.i_mode & (1 << i))
            putchar(t1[i]);
        else
            putchar(t2[i]);
    }

    // basic file info
    printf(" %4d ", mip->INODE.i_links_count);
    printf("%4d ", mip->INODE.i_gid);
    printf("%4d ", mip->INODE.i_uid);
    printf("%8d ", mip->INODE.i_size);

    // time
    char ftime[64];
    strcpy(ftime, ctime(&sp->st_mtime));
    ftime[strlen(ftime) - 1] = 0;
    printf("%s ", ftime);

    // name
    printf("%s ", name);
    if(S_ISLNK(mip->INODE.i_mode))
    {
        char buf[BLKSIZE];
        get_block(dev, mip->INODE.i_block[0], buf);
        printf("-> %s ", buf);
    }
    
    // [ino ]
    printf("\t\t[%d %d]\n", mip->dev, mip->ino);
}

int ls_dir(MINODE* mip, char* path)
{
    char buf[BLKSIZE], temp[256];
    DIR *dp;
    char *cp;
    int ino;

    // if a path was given
    if (path[0] != 0)
    {
        if (path[0] == '/')
            dev = root->dev;
        ino = getino(path);
        if(!ino)
            return -1;
        mip = iget(dev, ino);
        printf("\n\n");
    }
    if(mip->INODE.i_mode == FILE_MODE)
    {
        ls_file(mip, basename(strdup(path)));
        return 0;
    }
    get_block(dev, mip->INODE.i_block[0], buf);
    dp = (DIR *)buf;
    cp = buf;
    
    if(mip->mounted)
    {
        int odev = dev;
        printf("mount dev: %d\n", mip->mntPtr->dev);
        dev = mip->mntPtr->dev;
        ls_dir(iget(mip->mntPtr->dev, 2), "");
        dev = odev;
        return 0;
    }

    while (cp < buf + BLKSIZE)
    {
        strncpy(temp, dp->name, dp->name_len);
        temp[dp->name_len] = 0;
        ino = dp->inode;
        mip = iget(dev, ino);

        // permission check
        ls_file(mip, temp);

        cp += dp->rec_len;
        dp = (DIR *)cp;
    }
    printf("\n");

    return 0;
}

void ls(char *pathname)
{
    ls_dir(running->cwd, pathname);
}

// TODO: Add permission check
void rpwd(MINODE *wd)
{
    int rdev = dev;
    char name[256];
    if (wd->ino == 2)
    {
        if(dev != rootdev)
        {
            wd = getmptr(dev)->mntDirPtr;
            dev = wd->dev;
        }
        else
            return;
    }
    u32 my_ino, parent_ino;

    my_ino = wd->ino;

    parent_ino = findino(wd, &my_ino);

    wd = iget(wd->dev, parent_ino);
    rpwd(wd);
    
    findmyname(wd, my_ino, name);
    printf("/%s", name);
    dev = rdev;
}

void pwd(MINODE *wd)
{
    if (wd == root)
    {
        printf("/\n");
        return;
    }
    else
    {
        rpwd(wd);
        printf("\n");
    }
}

