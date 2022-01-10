/***** LAB3 base code *****/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

char gpath[128];    // hold token strings 
char *arg[64];      // token string pointers
int  n;             // number of token strings

char dpath[128];    // hold dir strings in PATH
char *dir[64];      // dir string pointers
int  ndir = 0;          // number of dirs   

int tokenize(char *pathname) // YOU have done this in LAB2
{                            // YOU better know how to apply it from now on
  char *s;
  strcpy(gpath, pathname);   // copy into global gpath[]
  s = strtok(gpath, " ");    
  n = 0;
  while(s){
    arg[n++] = s;           // token string pointers   
    s = strtok(0, " ");
  }
  arg[n] =0;                // arg[n] = NULL pointer 
}

void operate(char* line, char** a, char** env)
{
  for(int i = 0; a[i]; ++i)
       {
           if(strcmp(a[i], ">") == 0)
           {
              close(1);
              open(a[i + 1], O_WRONLY | O_CREAT, 0644);
              a[i] = NULL;
           }
           else if(strcmp(a[i], "<") == 0)
           {
              close(0);
              open(a[i + 1], O_RDONLY);
              a[i] = NULL;
           }
           else if(strcmp(a[i], ">>") == 0)
           {
             close(1);
             open(a[i + 1], O_APPEND | O_WRONLY, 0644);
             a[i] = NULL;
           }
           else if(strcmp(a[i], "|") == 0)
           {
             int pd[2];
             pipe(pd);
             int ppid = fork();
             if(ppid)
             {
               close(pd[0]);
               close(1);
               dup(pd[1]);
               close(pd[1]);
               a[i] = NULL;
               break;
             }
             else
             {
               close(pd[1]);
               close(0);
               dup(pd[0]);
               close(pd[0]);
               operate(line, a + i + 1, env);
             }
           }
       }
  int r = execve(line, a, env);

  printf("execve failed on path %s, r = %d\n", line, r);
}

int main(int argc, char *argv[ ], char *env[ ])
{
  int i;
  int pid, status;
  char *cmd;
  char line[28];

  // The base code assume only ONE dir[0] -> "/bin"
  // YOU do the general case of many dirs from PATH !!!!
  char* path = getenv("PATH");
  char* var = strtok(path, ":");
  while(var)
  {
    dir[ndir] = var;
    printf("dir[%d]: %s\n", ndir, dir[ndir]);
    ++ndir;
    var = strtok(NULL, ":");
  }

  // show dirs
  for(i=0; i<ndir; i++)
    printf("dir[%d] = %s\n", i, dir[i]);
  
  while(1){
    printf("sh %d running\n", getpid());
    printf("enter a command line : ");
    fgets(line, 128, stdin);
    line[strlen(line) - 1] = 0; 
    if (line[0]==0)
      continue;
    
    tokenize(line);

    for (i=0; i<n; i++){  // show token strings   
        printf("arg[%d] = %s\n", i, arg[i]);
    }
    // getchar();
    
    cmd = arg[0];         // line = arg0 arg1 arg2 ... 

    if (strcmp(cmd, "cd")==0){
      chdir(arg[1]);
      continue;
    }
    if (strcmp(cmd, "exit")==0)
      exit(0); 
    
     pid = fork();
     
     if (pid){
       printf("sh %d forked a child sh %d\n", getpid(), pid);
       printf("sh %d wait for child sh %d to terminate\n", getpid(), pid);
       pid = wait(&status);
       printf("ZOMBIE child=%d exitStatus=%x\n", pid, status); 
       printf("main sh %d repeat loop\n", getpid());
     }
     else{
       printf("child sh %d running\n", getpid());
       
       // make a cmd line = dir[0]/cmd for execve()
       for(i = 0; i < ndir; ++i)
       {
        strcpy(line, dir[i]); strcat(line, "/"); strcat(line, cmd);
        printf("line = %s\n", line);
        operate(line, arg, env);
       }
       printf("execve %s failed on all paths\n", cmd);
       exit(0);
     }
  }
}

/********************* YOU DO ***********************
1. I/O redirections:

Example: line = arg0 arg1 ... > argn-1

  check each arg[i]:
  if arg[i] = ">" {
     arg[i] = 0; // null terminated arg[ ] array 
     // do output redirection to arg[i+1] as in Page 131 of BOOK
  }
  Then execve() to change image


2. Pipes:

Single pipe   : cmd1 | cmd2 :  Chapter 3.10.3, 3.11.2

Multiple pipes: Chapter 3.11.2
****************************************************/