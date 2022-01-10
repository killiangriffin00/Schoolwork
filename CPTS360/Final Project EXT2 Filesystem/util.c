/*********** util.c file ****************/
#include "functions.h"
#include "globals.h"

// allocate a FREE minode for use
MINODE* mialloc()
{
   int i;
   for (i = 0; i < NMINODE; ++i)
   {
      MINODE *mp = &minode[i];
      if (mp->refCount == 0)
      {
         mp->refCount = 1;
         return mp;
      }
   }
   printf("FS panic: out of minodes\n");
   return 0;
}

void midalloc(MINODE *mip)
{
   mip->refCount = 0;
}


void get_block(int dev, int blk, char *buf)
{
   lseek(dev, (long)blk*BLKSIZE, 0);
   read(dev, buf, BLKSIZE);
}   

void put_block(int dev, int blk, char *buf)
{
   lseek(dev, (long)blk*BLKSIZE, 0);
   write(dev, buf, BLKSIZE);
}   

void tokenize(char *pathname)
{
  int i;
  char *s;
  printf("tokenize %s\n", pathname);

  strcpy(gpath, pathname);   // tokens are in global gpath[ ]
  n = 0;

  s = strtok(gpath, "/");
  while(s){
    name[n] = s;
    n++;
    s = strtok(0, "/");
  }
  name[n] = 0;
  
  for (i= 0; i<n; i++)
    printf("%s  ", name[i]);
  printf("\n");
}

// return minode pointer to loaded INODE
MINODE *iget(int dev, int ino)
{
  int i;
  MINODE *mip;
  char buf[BLKSIZE];
  int blk, offset;
  INODE *ip;

  for (i=0; i<NMINODE; i++){
    mip = &minode[i];
    if (mip->refCount && mip->dev == dev && mip->ino == ino){
       mip->refCount++;
       //printf("found [%d %d] as minode[%d] in core\n", dev, ino, i);
       return mip;
    }
  }
    
  for (i=0; i<NMINODE; i++){
    mip = &minode[i];
    if (mip->refCount == 0){
       //printf("allocating NEW minode[%d] for [%d %d]\n", i, dev, ino);
       mip->refCount = 1;
       mip->dev = dev;
       mip->ino = ino;

       // get INODE of ino to buf    
       blk    = (ino-1)/8 + getmptr(dev)->iblock;
       offset = (ino-1) % 8;

       //printf("iget: ino=%d blk=%d offset=%d\n", ino, blk, offset);

       get_block(dev, blk, buf);
       ip = (INODE *)buf + offset;
       // copy INODE to mp->INODE
       mip->INODE = *ip;
       return mip;
    }
  }   
  printf("PANIC: no more free minodes\n");
  return 0;
}

void iput(MINODE *mip)
{
 //int i;
 int block, offset;
 char buf[BLKSIZE];
 INODE *ip;

 if (mip==0) 
     return;

 mip->refCount--;
 
 if (mip->refCount > 0) return;
 if (!mip->dirty)       return;
 
 // Write inode back to disk
 block = (mip->ino - 1) / 8 + getmptr(dev)->iblock;
 offset = (mip->ino - 1) % 8;

 // get block containing this node
 get_block(mip->dev, block, buf);
 ip = (INODE *)buf + offset;        // ip points at INODE
 *ip = mip->INODE;                  // copy INODE to inode in block
 put_block(mip->dev, block, buf);   // write back to disk
 midalloc(mip);                     // mip->refCount = 0
} 

int search(MINODE *mip, char *sName)
{
   int i = 0; 
   char *cp, sbuf[BLKSIZE], temp[256];
   DIR *dp;
   INODE *ip;

   printf("search for %s in MINODE = [%d, %d]\n", sName,mip->dev,mip->ino);
   
   ip = &(mip->INODE);

   /*** search for name in mip's data blocks: ASSUME i_block[0] ONLY ***/

   get_block(mip->dev, ip->i_block[0], sbuf);
   dp = (DIR *)sbuf;
   cp = sbuf;

   while (cp < sbuf + BLKSIZE){
      strncpy(temp, dp->name, dp->name_len);
      temp[dp->name_len] = 0;
      if (strcmp(temp, sName)==0){
         printf("found %s : ino = %d\n", temp, dp->inode);
         return dp->inode;
      }
     cp += dp->rec_len;
     dp = (DIR *)cp;
     i++;
   }
   return 0;
}

int getino(char *pathname)
{
  int i, ino;
  MINODE *mip;

  printf("getino: pathname=%s\n", pathname);
  if (strcmp(pathname, "/")==0)
      return 2;
  
  // starting mip = root OR CWD
  if (pathname[0]=='/')
     mip = root;
  else
     mip = running->cwd;

  mip->refCount++;         // because we iput(mip) later
  
  tokenize(pathname);

  for (i=0; i<n; i++){
      printf("===========================================\n");
      printf("getino: i=%d name[%d]=%s\n", i, i, name[i]);

      if(mip->mounted)
      {
         dev = mip->mntPtr->dev;
         mip = iget(mip->mntPtr->dev, 2);
         printf("Mounted filesystem, new dev = %d\n", dev);
      }
      else if(mip->ino == 2 && dev != rootdev && strcmp(name[i], "..") == 0)
      {
         mip = getmptr(dev)->mntDirPtr;
         dev = mip->dev;
         printf("Exit mounted filesystem, new dev = %d\n", dev);
      }
      ino = search(mip, name[i]);

      if (ino==0){
         iput(mip);
         printf("name %s does not exist\n", name[i]);
         return 0;
      }
      iput(mip);
      mip = iget(dev, ino);
   }

   iput(mip);
   return ino;
}

// These 2 functions are needed for pwd()
int findmyname(MINODE *parent, u32 myino, char myname[ ]) 
{
  // WRITE YOUR code here
  // search parent's data block for myino; SAME as search() but by myino
  // copy its name STRING to myname[ ]
   char buf[BLKSIZE], *cp; //temp[256];
   get_block(parent->dev, parent->INODE.i_block[0], buf);
   DIR* dp = (DIR *)buf;
   cp = buf;

   while (cp < buf + BLKSIZE)
   {
      if (dp->inode == myino)
      {
         strncpy(myname, dp->name, dp->name_len);
         myname[dp->name_len] = 0;
         //printf("ino %d found with name - %s\n", myino, myname);
         return 0;
      }
      cp += dp->rec_len;
      dp = (DIR *)cp;
   }

   printf("node with ino %d not found\n", myino);
   return -1;
}

int findino(MINODE *mip, u32 *myino) // myino = i# of . return i# of ..
{
  // mip points at a DIR minode
  // WRITE your code here: myino = ino of .  return ino of ..
  // all in i_block[0] of this DIR INODE.
   char buf[BLKSIZE];

   get_block(mip->dev, mip->INODE.i_block[0], buf);
   DIR* dp = (DIR *)buf;
   char* cp = buf;

   *myino = dp->inode;

   cp += dp->rec_len;
   dp = (DIR *)cp;

   return dp->inode;
}

/**                        |own|grp|oth|
 * INODE.i_mode = |tttt|ugs|rwx|rwx|rwx|
 *                         |permissions|
*/

// checks whether the filename can be accessed in the desired mode (r|w|x)
int my_access(char *filename, char mode)
{
   int r, ino;
   MINODE* mip;

   // if SUPERuser: always OK
   if (running->uid == 0)
   {
      return 1;
   }
   else  // if NOT SUPERuser : get file's INODE
   {
      ino = getino(filename);
      mip = iget(dev, ino);
   }

   // if OWNER
   if (mip->INODE.i_uid == running->uid)
   {
      // (check owner's rwx with mode) by tst_bit()
      if (mode == 'r')
         r = get_bit(mip->INODE.i_mode, 8);
      if (mode == 'w')
         r = get_bit(mip->INODE.i_mode, 7);
      if (mode == 'x')
         r = get_bit(mip->INODE.i_mode, 6);
   }
   else // if not OWNER
   {
      // (check other's rwx with mode) // by tst_bit()
      if (mode == 'r')
         r = get_bit(mip->INODE.i_mode, 2);
      if (mode == 'w')
         r = get_bit(mip->INODE.i_mode, 1);
      if (mode == 'x')
         r = get_bit(mip->INODE.i_mode, 0);
   }

   iput(mip);
   return r;
}