#include "functions.h"
#include "globals.h"



int idalloc(int dev, int ino)
{
  char buf[BLKSIZE];

  if (ino > getmptr(dev)->ninodes){  
    printf("inumber %d out of range\n", ino);
    return -1;
  }
  
  get_block(dev, getmptr(dev)->imap, buf);  // get inode bitmap block into buf[]
  
  clr_bit(buf, ino-1);        // clear bit ino-1 to 0

  put_block(dev, getmptr(dev)->imap, buf);  // write buf back
  incFreeInodes(dev);
  return 0;
}




void incFreeInodes(int dev)
{
    char buf[BLKSIZE];
    get_block(dev, 1, buf);
    sp = (SUPER *)buf;
    sp->s_free_inodes_count++;
    put_block(dev, 1, buf);
    get_block(dev, 2, buf);
    gp = (GD *)buf;
    gp->bg_free_inodes_count++;
    put_block(dev, 2, buf);
}

int bdalloc(int dev, int bno)
{
  char buf[BLKSIZE];

  if (bno > getmptr(dev)->ninodes){  
    printf("inumber %d out of range\n", bno);
    return -1;
  }
  
  get_block(dev, getmptr(dev)->bmap, buf);  // get bnode bitmap block into buf[]
  
  clr_bit(buf, bno - 1);        // clear bit bno-1 to 0

  put_block(dev, getmptr(dev)->bmap, buf);  // write buf back

  incFreeBlocks(dev);
  return 0;
}

void incFreeBlocks(int dev)
{
    char buf[BLKSIZE];
    get_block(dev, 1, buf);
    sp = (SUPER *)buf;
    sp->s_free_blocks_count++;
    put_block(dev, 1, buf);
    get_block(dev, 2, buf);
    gp = (GD *)buf;
    gp->bg_free_blocks_count++;
    put_block(dev, 2, buf);
}

void rm_child(MINODE* pmip, char* name)
{
    printf("name : %s\n", name);
    int i = 0, c = 0;
    char buf[BLKSIZE], *cp;
    DIR* dp, *prev;
    
    for (i = 0; i < 12; ++i)
    {
        c = 0;
        printf("i = %d\n", i);
        if (pmip->INODE.i_block[i] == 0)
        {
            printf("rm_child : %s not found\n", name);
            return;
        }
        get_block(pmip->dev, pmip->INODE.i_block[i], buf);
        dp = (DIR *)buf;
        cp = buf;
        // search for name in current block
        while (cp + dp->rec_len < buf + BLKSIZE)
        {
            c += dp->rec_len;
            printf("dp->name = %s\n", dp->name);
            if (strlen(name) == dp->name_len)
            {   
                if (strncmp(dp->name, name, dp->name_len) == 0)
                {
                    // when name is found
                    // if it is the first and only entry
                    if (dp->rec_len == BLKSIZE)
                    {
                        printf("rm_child : %s is the first and only entry; removing\n", name);
                        bdalloc(pmip->dev, pmip->INODE.i_block[i]);
                        pmip->INODE.i_size -= BLKSIZE;
                        goto end;
                    }
                    else
                    {
                        // get rec_len of node to delete
                        int temp = dp->rec_len;

                        // move cp past node to delete
                        cp += dp->rec_len;

                        // copy the remainder of the block size into dp from cp
                        memcpy(dp, cp, BLKSIZE - c);

                        // navigate to the last node of the DIR
                        while (cp + dp->rec_len < buf + BLKSIZE)
                        {
                            cp += dp->rec_len;
                            dp = (DIR*)cp;
                        }

                        // add the deleted nodes rec_len to the last node
                        dp->rec_len += temp;
                        goto end;
                    }
                }
            }

            prev = dp;
            cp += dp->rec_len;
            dp = (DIR *)cp;
        }
        // check if it is the last entry
        printf("dp->name = %s\n", dp->name);
        if (strlen(name) == dp->name_len)
        {
            if (strncmp(dp->name, name, dp->name_len) == 0)
            {
                printf("rm_child : %s is the last entry; removing\n", name);
                prev->rec_len += dp->rec_len;
                dp->rec_len = 0;
                bzero(dp->name, dp->name_len);
                dp->name_len = 0;
                goto end;
            }
        }
    }
    end:
    put_block(pmip->dev, pmip->INODE.i_block[i], buf);
}


void my_rmdir(char* pathname)
{
    char* fname = basename(strdup(pathname));
    //char* dname = dirname(strdup(pathname));

    u32 ino = getino(pathname);
    MINODE* mip = iget(dev, ino);

    // permission check
    if (mip->INODE.i_uid != running->uid)
    {
        printf("my_rmdir: permission to %s denied. Not owner\n", fname);
        return;
    }


    printf("refCount = %d\n", mip->refCount);

    // ensure pathname points to a DIR
    printf("check if %s is a DIR\n", pathname);
    if (!S_ISDIR(mip->INODE.i_mode))
    {
        printf("rmdir failed: %s does not lead to a DIR\n", pathname);
        return;
    }

    // verify DIR is empty
    printf("verify %s is empty\n", pathname);
    if (mip->INODE.i_links_count > 2)
    {
        printf("rmdir failed: DIR has more than 2 links, signifying non-empty status\n");
        return;
    }

    // This checks if the directory is only . and ..
    // If .. is not requal to the remaining block size, then there is something else
    char buf[BLKSIZE];
    get_block(mip->dev, mip->INODE.i_block[0], buf);
    char* cp = buf;
    DIR* dp = (DIR *)buf;
    cp += dp->rec_len;
    dp = (DIR *)cp;
    printf("%s ===== %d\n", dp->name, dp->rec_len);
    // if rec_len == ideal_len, we know there are more entries
    if (dp->rec_len <= 12)
    {
        printf("rmdir failed: DIR %s is not empty\n", fname);
        return;
    }


    // get parents ino and inode
    int pino = findino(mip, &ino);
    MINODE* pmip = iget(mip->dev, pino);
    printf("pino = %d\n", pino);

    printf("enter rm_child\n");
    // remove name from parent directory
    rm_child(pmip, fname);

    // dec parent links_count by 1; mark pmip dirty
    pmip->INODE.i_links_count--;
    pmip->dirty = 1;
    iput(pmip);

    // deallocate its data blocks and inode
    idalloc(mip->dev, mip->ino);
    mip->dirty = 1;
    iput(mip);
}