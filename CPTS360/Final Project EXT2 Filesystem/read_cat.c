#include "globals.h"
#include "functions.h"


int my_read(int fd, char* buf, int nbytes)
{
    // * Validation
    if(!validatefd(fd))
    {
        printf("my_read: Invalid file descriptor %d. read failed\n", fd);
        return 0;
    }
    if(running->fd[fd]->mode == 1 || running->fd[fd]->mode == 3)
    {
        printf("my_read: File %d is not open for read. read failed\n", fd);
        return 0;
    }

    int count = 0, blk = 0;
    OFT* oftp = running->fd[fd];
    int left = oftp->minodePtr->INODE.i_size - oftp->offset; // amount of data left to read
    char* cq = buf, readbuf[BLKSIZE];
    int ibuf[256];
    MINODE* mip = oftp->minodePtr;
    int start = 0;

    while (nbytes > 0 && left > 0)
    {
        int lblk = oftp->offset / BLKSIZE;
        int start = oftp->offset % BLKSIZE;

        if (lblk < 12)
        {
            blk = mip->INODE.i_block[lblk];
        }
        else if (lblk >= 12 && lblk < 256 + 12) // indirect block
        {
            get_block(mip->dev, mip->INODE.i_block[12], ibuf);
            blk = ibuf[lblk - 12];
        }
        else // double indirect block
        {
            // zero out - account for all blocks before
            lblk -= 256 + 12; // LA

            get_block(mip->dev, mip->INODE.i_block[13], ibuf);
            get_block(mip->dev, ibuf[lblk / 256], ibuf); // LA / N
            blk = ibuf[lblk % 256]; // LA % N
        }

        // get the data block info readbuf
        get_block(mip->dev, blk, readbuf);

        // copy from startByte to buf[], at most remain bytes in this block
        char* cp = readbuf + start;
        int just_read = BLKSIZE - start;

        // if less than one blocks worth left to write
        if(just_read > left)
            just_read = left;

        memcpy(cq, cp, just_read);
        cq += just_read;

        // iterate how much we have written
        count += just_read;
        
        // left is how much there exists left to read
        left -= just_read;

        // nbytes is the max size of buf / how much we CAN read
        nbytes -= just_read;

        // iterate the offset of the fd by the amount read
        oftp->offset += just_read;
    }
    //printf("my_read: read %d char from file descriptor %d\n", count, fd);
    return count;
}


int my_cat(char* filename)
{
    char buf[BLKSIZE];
    int n, fd = my_open(filename, 0);
    printf("\n\n========= %s CONTENTS =========\n\n", filename);
    while((n = my_read(fd, buf, BLKSIZE)))
    {
        buf[n] = 0;
        printf("%s", buf);
        bzero(buf, BLKSIZE);
    }
    printf("\nEND READ LOOP\n");
    my_close(fd);
    return 0;
}