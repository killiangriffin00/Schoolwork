#include "globals.h"
#include "functions.h"

int tst_bit(char * buf, int bit)
{
    return buf[bit / 8] & (1 << (bit % 8));
}

int get_bit(u16 bt, int num)
{
    return (bt << num) % 8;
}

void set_bit(char *buf, int bit)
{
    buf[bit / 8] |= (1 << (bit % 8));
}

void clr_bit(char *buf, int bit)
{
    buf[bit / 8] &= ~(1 << (bit % 8));
}

void decFreeInodes(int dev)
{
    char buf[BLKSIZE];
    get_block(dev, 1, buf);
    sp = (SUPER *)buf;
    sp->s_free_inodes_count--;
    put_block(dev, 1, buf);
    get_block(dev, 2, buf);
    gp = (GD *)buf;
    gp->bg_free_inodes_count--;
    put_block(dev, 2, buf);
}

void decFreeBlocks(int dev)
{
    char buf[BLKSIZE];
    get_block(dev, 1, buf);
    sp = (SUPER *)buf;
    sp->s_free_blocks_count--;
    put_block(dev, 1, buf);
    get_block(dev, 2, buf);
    gp = (GD *)buf;
    gp->bg_free_blocks_count--;
    put_block(dev, 2, buf);
}

int ialloc(int dev)
{
    char buf[BLKSIZE];

    // read inode_bitmap block
    get_block(dev, getmptr(dev)->imap, buf);

    for (int i = 0; i < getmptr(dev)->ninodes; ++i)
    {
        if (tst_bit(buf, i) == 0)
        {
            set_bit(buf, i);
            put_block(dev, getmptr(dev)->imap, buf);
            decFreeInodes(dev);
            return i+1;
        }
    }
    return 0;
}

int balloc(int dev)
{
    char buf[BLKSIZE];

    get_block(dev, getmptr(dev)->bmap, buf);

    for (int i = 0; i < getmptr(dev)->nblocks; ++i)
    {
        if (tst_bit(buf, i) == 0)
        {
            set_bit(buf, i);
            put_block(dev, getmptr(dev)->bmap, buf);
            decFreeBlocks(dev);
            return i+1;
        }
    }
    return 0;
}


// enters a new [ino, name] as a new dir_entry into a parent dir
void enter_name(MINODE* pmip, int ino, char* name)
{
    //printf("enter_name : %s\n", name);
    int need_l = 4 * ((8 + strlen(name) + 3) / 4);
    int i = 0;
    char buf[BLKSIZE];
    printf("need_len for %s = %d\n", name, need_l);
    // assume: only 12 direct blocks
    for (i = 0; i < 12; ++i)
    {
        if (pmip->INODE.i_block[i] == 0)
            break;
        
        bzero(buf, BLKSIZE);

        // Get a parent's block data into a buf[]
        get_block(pmip->dev, pmip->INODE.i_block[i], buf);
        DIR* dp = (DIR *)buf;
        char* cp = buf;

        while (cp + dp->rec_len < buf + BLKSIZE)
        {
            cp += dp->rec_len;
            dp = (DIR *)cp;
        }
        printf("step to LAST entry in data block\n\n", dp->rec_len, dp->name);

        int ideal_l = 4 * ((8 + dp->name_len + 3) / 4);
        int remains = dp->rec_len - ideal_l;

        if (remains >= need_l)
        {   
            dp->rec_len = ideal_l;

            cp += dp->rec_len;
            dp = (DIR *)cp;

            // change the data of the new last node
            strncpy(dp->name, name, strlen(name));
            dp->name_len = strlen(name);
            dp->rec_len = remains;
            dp->inode = ino;
            put_block(pmip->dev, pmip->INODE.i_block[i], buf);
            return;
        }
    }

    // if an empty block is reached and it is still a direct block
    if (i < 12)
    {
        printf("enter_name : putting %s in an emtpy block\n", name);
        bzero(buf, BLKSIZE);
        get_block(pmip->dev, pmip->INODE.i_block[i], buf);
        DIR* dp = (DIR *)buf;
        dp->rec_len = BLKSIZE;
        strncpy(dp->name, name, dp->name_len);
        dp->name_len = strlen(name);
        dp->inode = ino;
        put_block(pmip->dev, pmip->INODE.i_block[i], buf);
    }
}

void kmkdir(MINODE* pmip, char* fname)
{
    // allocate space in the pmip
    int ino = ialloc(pmip->dev);
    int blkno = balloc(pmip->dev);

    MINODE* mip = iget(dev, ino);
    INODE *ip = &mip->INODE;
    ip->i_mode = DIR_MODE;            // 040755: DIR type and permissions
    ip->i_uid = running->uid;       // owner uid
    ip->i_gid = running->gid;       // group ID
    ip->i_size = BLKSIZE;           // size in bytes
    ip->i_links_count = 2;          // links_count = 2 because of . and ..
    ip->i_atime = ip->i_ctime = ip->i_mtime = time(0L);
    ip->i_blocks = 2;               // LINUX: Blocks count in 512-byte chunks
    ip->i_block[0] = blkno;           // new DIR has one data block
    
    for (int i = 1; i <= 14; ++i)
    { 
        ip->i_block[i] = 0;
    }

    mip->dirty = 1;                 // mark minode dirty
    iput(mip);                      // write INODE to disk

    char buf[BLKSIZE];
    bzero(buf, BLKSIZE);
    DIR *dp = (DIR *)buf;

    // make . entry
    dp->inode = ino;
    dp->rec_len = 12;
    dp->name_len = 1;
    dp->name[0] = '.';

    // make .. entry; pino=parent DIR ino, blk = allocated block
    dp = (char *)dp + 12;
    dp->inode = pmip->ino;
    dp->rec_len = BLKSIZE - 12;     // rec_len spans block
    dp->name_len = 2;
    dp->name[0] = dp->name[1] = '.';
    put_block(dev, blkno, buf);

    enter_name(pmip, ino, fname);
}

int my_mkdir(char* path)
{
    char *dname = dirname(strdup(path));
    char *fname = basename(strdup(path));

    // permission check
    if (!my_access(dname, 'r') || !my_access(dname, 'w') || !my_access(dname, 'x'))
    {
        printf("my_mkdir: permission to %s denied\n", dname);
        return -1;
    }


    // parent node information - add new dir as a child of this
    int pino = getino(dname);
    MINODE* pmip = iget(dev, pino);

    // if the desired dir is not a DIR
    if (!S_ISDIR(pmip->INODE.i_mode))
        return -1;
    
    // check if desired filename already exists
    if (search(pmip, fname) != 0)
        return -1;
    
    kmkdir(pmip, fname);

    pmip->INODE.i_links_count++;
    pmip->dirty = 1;
    pmip->INODE.i_atime = pmip->INODE.i_ctime = pmip->INODE.i_mtime = time(0L);
    iput(pmip);

    return 0;
}

void kcreat(MINODE* pmip, char* fname)
{
    // allocated space in the pmip
    int ino = ialloc(pmip->dev);

    MINODE* mip = iget(dev, ino);
    INODE *ip = &mip->INODE;
    ip->i_mode = FILE_MODE;
    ip->i_uid = running->uid;
    ip->i_gid = running->gid;
    ip->i_size = 0;
    ip->i_links_count = 1;
    ip->i_atime = ip->i_ctime = ip->i_mtime = time(0L);
    ip->i_blocks = 0;

    for (int i = 0; i <= 14; ++i)
    {
        ip->i_block[i] = 0;
    }

    mip->dirty = 1;
    iput(mip);

    enter_name(pmip, ino, fname);
}

int my_creat(char *pathname)
{
    char *dname = dirname(strdup(pathname));
    char *fname = basename(strdup(pathname));

    if (!my_access(dname, 'r') || !my_access(dname, 'w') || !my_access(dname, 'x'))
    {
        printf("my_creat: permission to %s denied\n", dname);
        return -1;
    }

    // parent information
    int pino = getino(dname);
    MINODE* pmip = iget(dev, pino);

    // if the desired dir is not a DIR
    if (!S_ISDIR(pmip->INODE.i_mode))
    {
        printf("creat failed: %s does not lead to a DIR\n", dname);
        return -1;
    }
    if (search(pmip, fname) != 0)
    {
        printf("creat failed: file with name %s already found\n", fname);
        return -1;
    }

    kcreat(pmip, fname);

    pmip->dirty = 1;
    pmip->INODE.i_atime = pmip->INODE.i_ctime = pmip->INODE.i_mtime = time(0L);
    iput(pmip);


    return 0;
}

