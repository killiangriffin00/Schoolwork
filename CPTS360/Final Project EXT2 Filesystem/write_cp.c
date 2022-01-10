#include "globals.h"
#include "functions.h"


int my_write(int fd, char buf[], int nbytes)
{
    if(!validatefd(fd))
    {
        printf("Invalid file descriptor. write failed\n");
        return -1;
    }
    if(running->fd[fd]->mode == 0)
    {
        printf("File is open for read only. write failed\n");
        return -1;
    }

    OFT* oftp = running->fd[fd];
    int blk = 0;
    MINODE* mip = oftp->minodePtr;
    char* cq = buf;
    int ibuf[256];
    char wbuf[BLKSIZE];

    while (nbytes > 0)
    {
        // compute logical block (lblk) and the startByte in that lblk:
        int lblk = oftp->offset / BLKSIZE;
        int start = oftp->offset % BLKSIZE;

        //printf("lblk = %d\n", lblk);
        // direct blocks
        if (lblk < 12)
        {
            if (mip->INODE.i_block[lblk] == 0)
                mip->INODE.i_block[lblk] = balloc(mip->dev);
            blk = mip->INODE.i_block[lblk];
        }
        else if (lblk >= 12 && lblk < 256 + 12) // indirect blocks
        {
            if (mip->INODE.i_block[12] == 0)
            {
                // allocate block, zero out block on disk
                mip->INODE.i_block[12] = balloc(mip->dev);
            }
            get_block(mip->dev, mip->INODE.i_block[12], ibuf);
            blk = ibuf[lblk - 12];

            if (blk == 0)
            {
                // allocate a disk block, record it in i_block[12]
                blk = balloc(mip->dev);
                ibuf[lblk - 12] = blk;
                put_block(mip->dev, mip->INODE.i_block[12], ibuf);
            }
        }
        else // double indirect blocks
        {
            if (mip->INODE.i_block[13] == 0)
            {
                mip->INODE.i_block[13] = balloc(mip->dev);
            }
            lblk -= 256 + 12;
            int dibuf[256];
            get_block(mip->dev, mip->INODE.i_block[13], ibuf);

            if (ibuf[lblk / 256] == 0)
                ibuf[lblk / 256] = balloc(mip->dev);

            get_block(mip->dev, ibuf[lblk / 256], dibuf);
            blk = dibuf[lblk % 256];

            if (blk == 0)
            {
                blk = balloc(mip->dev);
                dibuf[lblk % 256] = blk;
                put_block(mip->dev, ibuf[lblk / 256], dibuf);
                put_block(mip->dev, mip->INODE.i_block[13], ibuf);
            }
        }

        // write data to disk block
        get_block(mip->dev, blk, wbuf);
        
        char* cp = wbuf + start;
        int remain = BLKSIZE - start;

        // if less than one blocks worth left to write
        if (remain > nbytes)
            remain = nbytes;

        // copy the memory
        memcpy(cp, cq, remain);
        cq += remain;

        nbytes -= remain;
        oftp->offset += remain;

        if (oftp->offset > mip->INODE.i_size)
            mip->INODE.i_size = oftp->offset;

        put_block(mip->dev, blk, wbuf);
    }

    mip->dirty = 1;
    iput(mip);
    return nbytes;
}


void my_cp(char* source, char* dest)
{
    // open source in READ
    int fd = my_open(source, 0);
    printf("fd opened\n");

    // open dest in RW|CREAT
    int gd = my_open(dest, 2);
    printf("gd opened\n");

    int n = 0;
    int i = 0;
    char buf[BLKSIZE];
    while ((n = my_read(fd, buf, BLKSIZE)))
    {
        buf[n] = 0;
        my_write(gd, buf, n);
    }

    my_close(fd);
    my_close(gd);
}