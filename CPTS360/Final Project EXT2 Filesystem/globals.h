#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "type.h"

MINODE minode[NMINODE], *root;      // in memory INODEs
MOUNT mtable[NMTABLE];             // mount tables
OFT oft[NOFT];                      // Opened file instance
PROC proc[NPROC];                   // PROC structures
PROC *running;                      // current executing PROC

char gpath[128], *name[64], line[128], cmd[32], pathname[128];
int n, fd, dev, rootdev, nblocks, ninodes, bmap, imap, iblk;


// mount_root
int ninodes, iblock;
char gline[25];
int nname;


#endif