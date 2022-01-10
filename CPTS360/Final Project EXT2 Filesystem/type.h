#ifndef _TYPE_H_
#define _TYPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ext2fs/ext2_fs.h>
#include <string.h>
#include <strings.h>
#include <libgen.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


/*************** type.h file for LEVEL-1 ****************/
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct ext2_super_block SUPER;
typedef struct ext2_group_desc  GD;
typedef struct ext2_inode       INODE;
typedef struct ext2_dir_entry_2 DIR;

SUPER *sp;
GD    *gp;
INODE *ip;
DIR   *dp;   

#define BLKSIZE 1024

// Block number of EXT2 FS on FD
#define SUPERBLOCK 1
#define GDBLOCK    2
#define ROOT_INODE 2

// Default dir and regular file modes
#define DIR_MODE        0x41ED
#define FILE_MODE       0x81A4
#define SUPER_MAGIC     0xEF53
#define SUPER_USER      0


// Proc status
#define FREE        0
#define READY       1

// File system table sizes
#define NMINODE     100
#define NMTABLE     10
#define NPROC       2
#define NFD         10
#define NOFT        40

typedef struct minode{
  INODE INODE;           // INODE structure on disk
  int dev, ino;          // (dev, ino) of INODE
  int refCount;          // in use count
  int dirty;             // 0 for clean, 1 for modified
  int mounted;           // for level-3
  struct mtable *mntPtr; // for level-3
}MINODE;

// Open file Table      // opened file instance
typedef struct oft {
  int mode;             // mode of opened file      0|1|2|3 == R|W|RW|APPEND
  int refCount;         // number of PROCs sharing this instance
  MINODE *minodePtr;    // pointers to minode of file
  int offset;           // byte offset for R|W
} OFT;

typedef struct proc{
  struct proc *next;
  int          pid;      // process ID  
  int          uid;      // user ID
  int          gid;
  int         ppid;
  int       status;
  struct minode      *cwd;      // CWD directory pointer
  OFT     *fd[NFD];  
}PROC;

// Mount Table structure
typedef struct mtable {
  int dev;                // device number; 0 for FREE
  int ninodes;            // from superblock
  int nblocks;
  int free_blocks;        // from superblock and GD
  int free_inodes;
  int bmap;               // from GD
  int imap;
  int iblock;             // inodes start block
  MINODE *mntDirPtr;      // mount point DIR pointer
  char devName[64];       // device name
  char mntName[64];       // mount point DIR name
} MOUNT;



#endif