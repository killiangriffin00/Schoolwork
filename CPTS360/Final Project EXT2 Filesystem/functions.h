#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "type.h"

// util.c
MINODE* mialloc();
void midalloc(MINODE *);
void get_block(int, int, char *);
void put_block(int, int, char *);
void tokenize(char *);
MINODE *iget(int, int);
void iput(MINODE *);
int search(MINODE *, char *);
int getino(char *);
int findmyname(MINODE *, u32 , char[ ]);
int findino(MINODE *, u32 *);
int my_access(char*, char);

// cd_ls_pwd.c
void cd(char *);
void ls(char *);
void pwd(MINODE *);

// mkdir_creat.c
void enter_name(MINODE*, int, char*);
int my_mkdir(char*);
int my_creat(char*);
int tst_bit(char *, int);
int get_bit(u16, int);
void set_bit(char *, int);
void clr_bit(char *, int);
int ialloc(int);
int balloc(int);


//link_unlink.c
int my_link(char*, char*);
int my_unlink(char*);
int my_symlink(char*, char*);
int my_readlink(char*, char*);

//rmdir.c
int idalloc(int, int);
void incFreeInodes(int);
int bdalloc(int, int);
void incFreeBlocks(int);
void rm_child(MINODE*, char*);
void my_rmdir(char*);

// stat_chmod.c
void my_stat(char*);

// open_close_lseek.c
int my_open(char*, int);
int my_truncate(MINODE*);
int my_lseek(int, u32);
int my_close(int);
int pfd();
int validatefd(int);


// write_cp.c
int my_write(int, char*, int);
int write_file(int, char*, int);
void my_cp(char*, char*);


// read_cat.c
int my_read(int, char*, int);
int my_cat(char*);

// mount_umount.c
int my_mount(char*, char*);
int my_umount(char*);
MOUNT* getmptr(int);

#endif