#include <stdio.h>             // for I/O
#include <stdlib.h>            // for I/O
#include <libgen.h>            // for dirname()/basename()
#include <string.h>

typedef struct node{
         char  name[64];       // node's name string
         char  type;           // 'D' for DIR; 'F' for file
   struct node *child, *sibling, *parent;
}NODE;


NODE *root, *cwd, *start;
char line[128];
char command[16], pathname[64];

//               0       1      2      3      4       5        6      7      8
char *cmd[] = {"mkdir", "ls", "quit", "cd", "pwd", "creat", "rmdir", "rm", "menu", 0};

int fileindex = 0;

int findCmd(char *command)
{
   int i = 0;
   while(cmd[i]){
     if (strcmp(command, cmd[i])==0)
         return i;
     i++;
   }
   return -1;
}

NODE *search_child(NODE *parent, char *name)
{
  NODE *p;
  printf("search for %s in parent DIR\n", name);
  p = parent->child;
  if (p==0)
    return 0;
  while(p){
    if (strcmp(p->name, name)==0)
      return p;
    p = p->sibling;
  }
  return 0;
}

int insert_child(NODE *parent, NODE *q)
{
  NODE *p;
  printf("insert NODE %s into END of parent child list\n", q->name);
  p = parent->child;
  if (p==0)
    parent->child = q;
  else{
    while(p->sibling)
      p = p->sibling;
    p->sibling = q;
  }
  q->parent = parent;
  q->child = 0;
  q->sibling = 0;
}

/***************************************************************
 This mkdir(char *name) makes a DIR in the current directory
 You MUST improve it to mkdir(char *pathname) for ANY pathname
****************************************************************/

NODE* pathToNode(char* path)
{
    NODE* t;
    if(path[0] == '/')
    {
        t = root;
    }
    else
    t = cwd;
    char* cpPath = path, *file = strtok(cpPath, "/");
    while(file)
    {
        if(!strcmp(file, ".."))
        {
          t = t->parent;
        }
        else
        {
          t = search_child(t, file);
        
          if(!t)
          {
            printf("Invalid filepath\n");
            return NULL;
          }
        }
        file = strtok(NULL, "/");
    }
    return t;
}

int mkdir(char* name)
{
  NODE *p, *q, *s;
  char path[64], dirName[64];
  printf("mkdir: name=%s\n", name);

  if (!strcmp(name, "/") || !strcmp(name, ".") || !strcmp(name, "..")){
    printf("can't mkdir with %s\n", name);
    return -1;
  }
  int n = 0;

  for(int i = 0; name[i] != '\0'; ++i)
  {
      if(name[i] == '/')
      {
          n = i;
      }
  }

  strncpy(path, name, n);
  strcat(path, "");
  strcpy(dirName, name + n);

  if(n)
  {
    strcpy(dirName, dirName + 1);
    s = pathToNode(path);
  }
  else s = cwd;

  if(!s)
  {
      return -1;
  }

  if(s->type == 'F')
  {
    printf("cannot mkdir inside of file\n");
    return -1;
  }

  printf("check whether %s already exists\n", dirName);
  p = search_child(s, dirName);
  if (p){
    printf("name %s already exists, mkdir FAILED\n", dirName);
    return -1;
  }
  printf("--------------------------------------\n");
  printf("ready to mkdir %s\n", dirName);
  q = (NODE *)malloc(sizeof(NODE));
  q->type = 'D';
  strcpy(q->name, dirName);
  insert_child(s, q);
  printf("mkdir %s OK\n", dirName);
  printf("--------------------------------------\n");
    
  return 0;
}

int rmdir(char* name)
{
  NODE *p, *s;
  printf("rmdir: name=%s\n", name);

  if (!strcmp(name, "/") || !strcmp(name, ".") || !strcmp(name, "..")){
    printf("can't rmdir with %s\n", name);
    return -1;
  }


  s = pathToNode(name);

  if(!s)
  {
      return -1;
  }

  if(s->type == 'F')
  {
    printf("cannot rmdir on file\n");
    return -1;
  }

  printf("check if %s exists\n", name);
  p = search_child(cwd, name);
  if (!p){
    printf("name %s doesn't exist, rmdir FAILED\n", name);
    return -1;
  }

  if(s->child)
  {
    printf("cannot rmdir on direcory with child\n");
    return -1;
  }

  printf("--------------------------------------\n");
  printf("ready to rmdir %s\n", s->name);

  if(s->parent->child == s)
  {
    if(s->sibling)
    {
      s->parent->child = s->sibling;
    }
    else s->parent->child = NULL;
  }
  else
  {
    NODE *t = s->parent->child;
    while(t->sibling != s)
    {
      t = t->sibling;
    }
    t->sibling = s->sibling;
  }
  free(s);

  printf("rmdir OK\n");
  printf("--------------------------------------\n");
    
  return 0;
}


int creat(char* name)
{
  NODE *p, *q, *s;
  char path[64], dirName[64];
  printf("creat: name=%s\n", name);

  if (!strcmp(name, "/") || !strcmp(name, ".") || !strcmp(name, "..")){
    printf("can't creat with %s\n", name);
    return -1;
  }
  int n = 0;

  for(int i = 0; name[i] != '\0'; ++i)
  {
      if(name[i] == '/')
      {
          n = i;
      }
  }

  strncpy(path, name, n);
  strcat(path, "");
  strcpy(dirName, name + n);

  if(n)
  {
    strcpy(dirName, dirName + 1);
    s = pathToNode(path);
  }
  else s = cwd;

  if(!s)
  {
      return -1;
  }

  if(s->type == 'F')
  {
    printf("cannot creat inside of file\n");
    return -1;
  }

  printf("check whether %s already exists\n", dirName);
  p = search_child(s, dirName);
  if (p){
    printf("name %s already exists, creat FAILED\n", dirName);
    return -1;
  }
  printf("--------------------------------------\n");
  printf("ready to creat %s\n", dirName);
  q = (NODE *)malloc(sizeof(NODE));
  q->type = 'F';
  strcpy(q->name, dirName);
  insert_child(s, q);
  printf("creat %s OK\n", dirName);
  printf("--------------------------------------\n");
    
  return 0;
}

int rm(char* name)
{
  NODE *p, *s;
  printf("rm: name=%s\n", name);

  if (!strcmp(name, "/") || !strcmp(name, ".") || !strcmp(name, "..")){
    printf("can't rm with %s\n", name);
    return -1;
  }


  s = pathToNode(name);

  if(!s)
  {
      return -1;
  }

  if(s->type == 'D')
  {
    printf("cannot rm on directory\n");
    return -1;
  }

  printf("check if %s exists\n", name);
  p = search_child(cwd, name);
  if (!p){
    printf("name %s doesn't exist, rm FAILED\n", name);
    return -1;
  }

  printf("--------------------------------------\n");
  printf("ready to rm %s\n", s->name);
  
  if(s->parent->child == s)
  {
    if(s->sibling)
    {
      s->parent->child = s->sibling;
    }
    else s->parent->child = NULL;
  }
  else
  {
    NODE *t = s->parent->child;
    while(t->sibling != s)
    {
      t = t->sibling;
    }
    t->sibling = s->sibling;
  }
  free(s);

  printf("rm OK\n");
  printf("--------------------------------------\n");
    
  return 0;
}

// This ls() list CWD. You MUST improve it to ls(char *pathname)
int ls(char* path)
{
  NODE *p = pathToNode(path)->child;
  
  printf("cwd contents = ");
  if(!p)
  {
      printf("\n");
      return 0;
  }
  
  while(p){
    printf("[%c %s] ", p->type, p->name);
    p = p->sibling;
  }
  printf("\n");
}

int cd(char* path)
{
    NODE* t = pathToNode(path);

    if(t)
    {
        cwd = t;
        return 1;
    }
    else
    return 0;
}

void pwd(NODE *current)
{
    if(current != root)
    {
      pwd(current->parent);
      printf("/%s", current->name);
    }
    else printf("cwd = /");
    if(current == cwd)
    {
      printf("\n");
    }
}

void save(FILE* output, NODE* current)
{
  if(!current)
  {
    return;
  }

  fprintf(output, "%c.%s", current->type, current->name);

  if(current->child)
  {
    fprintf(output, "{");
    save(output, current->child);
    fprintf(output, "}");
  }

  if(current->sibling)
  {
    fprintf(output, ",");
    save(output, current->sibling);
  }
  return;
}

NODE* reload(char* input)
{
  if(strlen(input) == fileindex || input[fileindex] == '}')
  {
    ++fileindex;
    return NULL;
  }

  char s[64] = "", *c = "";

  NODE* new = (NODE*)malloc(sizeof(NODE));
  new->type = input[fileindex];
  ++fileindex; ++fileindex;

  while(input[fileindex] != '{' && input[fileindex] != ',' && input[fileindex] != '}' && strlen(input) != fileindex)
  {
    strncat(s, &input[fileindex], 1);
    ++fileindex;
  }

  strcpy(new->name, s);

  if(input[fileindex] == '{')
  {
    ++fileindex;
    insert_child(new, reload(input));
    NODE* t = new->child->sibling;
    while(t)
    {
      t->parent = new;
      t = t->sibling;
    }
    ++fileindex;
  }
  
  if(input[fileindex] == ',')
  {
    ++fileindex;
    new->sibling = reload(input);
    ++fileindex;
  }

  return new;
}

int menu()
{
  printf("COMMANDS:\n\n");
  printf("mkdir filepath/name: Creates directory in directory specified by filepath. Default to current working\ndirecory if no filepath specified.\n\n");
  printf("rmdir filepath: Deletes empty drectory at specified filepath.\n\n");
  printf("cd filepath: Changes current working directory to directory specified by filepath.\n\n");
  printf("ls filepath: Prints contents of directory specified by filepath. Default to current working directory\nif no filepath specified.\n\n");
  printf("pwd: Prints filepath from root directory to current working directory.\n\n");
  printf("creat filepath/name: Creates file in directory specified by filepath. Default to current working\ndirecory if no filepath specified.\n\n");
  printf("rm filepath: Deletes file at specified filepath.\n\n");
  printf("quit: Ends the program.\n\n");
}

int quit()
{
  FILE *output = fopen("save", "w+");
  save(output, root->child);
  fclose(output);
  printf("Program exit\n");
  exit(0);
  // improve quit() to SAVE the current tree as a Linux file
  // for reload the file to reconstruct the original tree
}

int initialize()
{
    root = (NODE *)malloc(sizeof(NODE));
    strcpy(root->name, "/");
    root->parent = root;
    root->sibling = 0;
    root->child = 0;
    root->type = 'D';
    cwd = root;
    printf("Root initialized OK\n");
    FILE *input = fopen("save", "r+");
    char s[10000];

    fgets(s, 10000, input);
    root->child = reload(s);
    if(root->child)
    {
      root->child->parent = root;
      NODE* t = root->child->sibling;
      while(t)
      {
        t->parent = root;
        t = t->sibling;
      }
    }
    fclose(input);
    printf("Filesystem loaded\n");
}

int main()
{
  int index;

  initialize();

  printf("NOTE: commands = [mkdir|rmdir|cd|ls|pwd|creat|rm|menu|quit]\n");

  while(1){
      printf("Enter command line : ");
      fgets(line, 128, stdin);
      line[strlen(line)-1] = 0;

      command[0] = pathname[0] = 0;
      sscanf(line, "%s %s", command, pathname);
      printf("command=%s pathname=%s\n", command, pathname);
      
      if (command[0]==0) 
         continue;

      index = findCmd(command);

      switch (index){
        case 0: mkdir(pathname); break;
        case 1: ls(pathname);    break;
        case 2: quit();          break;
        case 3: cd(pathname);    break;
        case 4: pwd(cwd);        break;
        case 5: creat(pathname); break;
        case 6: rmdir(pathname); break;
        case 7: rm(pathname);    break;
        case 8: menu();          break;
      }
  }
}

