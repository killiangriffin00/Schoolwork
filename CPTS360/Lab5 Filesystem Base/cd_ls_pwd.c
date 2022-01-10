/************* cd_ls_pwd.c file **************/

char *t1 = "xwrxwrxwr-------";
char *t2 = "----------------";


int cd(char *path)
{
  int ino;
  if (path[0] == 0) 
    ino = running->cwd->ino;
  else
    ino = getino(path);

  if (!ino)
  {
    printf("path %s not found\n", path);
    return -1;
  }

  MINODE *mip = iget(dev, ino);

  if (!S_ISDIR(mip->INODE.i_mode))
  {
    printf("node with ino %d is not a DIR\n", ino);
    return -1;
  }

  iput(running->cwd);
  running->cwd = mip;

  return 0;
}

int ls_file(MINODE *mip, char *name)
{
  struct stat i_stat, *sp;
  sp = &i_stat;
  fstat(mip->ino, &i_stat);
  


  if (S_ISDIR(mip->INODE.i_mode))
  {
    putchar('d');
  }
  else if (S_ISREG(mip->INODE.i_mode))
  {
    putchar('-');
  }
  else if (S_ISLNK(mip->INODE.i_mode))
  {
    putchar('l');
  }

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


  // TIME PRINTING NOT WORKING
  // time
  char ftime[64];
  strcpy(ftime, ctime(&sp->st_ctime));
  ftime[strlen(ftime) - 1] = 0;
  printf("%s ", ftime);

  // name
  printf("%s\n", name);
  
  iput(mip);
}

int ls_dir(MINODE *mip, char* path)
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
    mip = iget(dev, ino);
    printf("\n\n");
  }

  get_block(dev, mip->INODE.i_block[0], buf);
  dp = (DIR *)buf;
  cp = buf;

  while (cp < buf + BLKSIZE)
  {
    strncpy(temp, dp->name, dp->name_len);
    temp[dp->name_len] = 0;
    ino = dp->inode;
    mip = iget(dev, ino);
    ls_file(mip, temp);

    cp += dp->rec_len;
    dp = (DIR *)cp;
  }
  printf("\n");


  return 0;
}

int ls(char* pathname)
{
  ls_dir(running->cwd, pathname);
}

void rpwd(MINODE *wd)
{
  if (wd == root)
    return;
  char name[256];
  u32 my_ino, parent_ino;

  my_ino = wd->ino;

  parent_ino = findino(wd, &my_ino);

  wd = iget(wd->dev, parent_ino);
  rpwd(wd);

  findmyname(wd, my_ino, &name);
  printf("/%s", name);
}

char *pwd(MINODE *wd)
{
  if (wd == root){
    printf("/\n");
    return;
  }
  else
    rpwd(wd);
    printf("\n");
}



