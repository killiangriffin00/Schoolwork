#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <libgen.h>
#include <time.h>
#include <errno.h>

#define MAX 256
#define PORT 1234



char *commands[] = {"get", "put", "ls", "cd", "pwd", "mkdir", "rmdir", "rm", 0};

int n;
char ans[MAX];
char line[MAX];

char **tab = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
//int  BASE = 10; 
/*
int rpu(int x, char** r)
{  
    char* c;
    if (x){
       c = tab[x % 10];
       rpu(x / 10, r);
       strcat(r[0], c);
    }
}

char* stringd(int x)
{
    char** r = {""};
    if(x < 0)
    {
        strcat(*r, "-");
    }

    if(x==0)
    {
        strcat(r[0], "0");
    }
    else
    rpu(abs(x), r);

    printf("%s\n", *r);
    strcat(*r, " ");
    return *r;
}
*/

int findCmd(char *command)
{
    int i = 0;
    while (commands[i])
    {
        if (strcmp(command, commands[i]) == 0)
            return i;
        i++;
    }
    return -1;
}

char* myls(char* path)
{
    DIR* dir;
    char* r = malloc(MAX), *t1 = "xwrxwrxwr-------", *t2 = "----------------", h[MAX*30];
    strcpy(r, "");
    /*
    if(strcmp(path, "") != 0)
    {
        dir = opendir(path);
    }
    */
    getcwd(h, MAX*30);
    dir = opendir(h);

    struct dirent* file = readdir(dir);
    while(file)
    {
        int e;
        struct stat fstat;
        struct stat* fp = &fstat;
        /*
        if((e = lstat(*path, &fstat)) < 0)
        {
            return NULL;
        }
        */
        if((fp->st_mode & 0xF000) == 0x8000)
        {
            printf("-");
        }
        if((fp->st_mode & 0xF000) == 0x4000)
        {
            printf("d");
        }
        if((fp->st_mode & 0xF000) == 0xA000)
        {
            printf("l");
        }
        for(int i = 8; i >= 0; --i)
        {
            if(fp->st_mode & (1<<i))
            {
                printf("%c", t1[i]);
            }
            else
            {
                printf("%c", t2[i]);
            }
        }

        printf("%d ", fp->st_nlink);

        printf("%d ", fp->st_gid);

        printf("%d ", fp->st_uid);

        printf("%d ", fp->st_size);

        char time[64];
        strcpy(time, ctime(&fp->st_ctime));
        time[strlen(time) - 1] = 0;
        printf("%s ", time);
        printf("%s\n", file->d_name);
        strcat(r, file->d_name);
        strcat(r, "  ");
        file = readdir(dir);
    }
    return r;
}


int main()
{
    int sfd, cfd, len;
    struct sockaddr_in saddr, caddr;
    int i, length;

    // set virtual root
    char root[MAX];
    getcwd(root, MAX);
    chroot(root);

    // get hostname
    char name[64];
    gethostname(name, 64);
    struct hostent* hp = gethostbyname(name);
    if (hp == 0)
    {
        printf("unknown host %s\n", name);
        exit(1);
    }

    // advertize server hostname and port number
    printf("hostname=%s  IP=%s  port=%d\n", hp->h_name, "127.0.0.1", PORT);


    printf("1. create a socket\n");
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        printf("socket creation failed\n");
        exit(0);
    }

    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        printf("setsockopt(SO_REUSEADDR) failed\n");
        exit(1);
    }
 

    printf("2. fill in server IP and port number\n");
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    // saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(PORT);

    printf("3. bind socket to server\n");
    if ((bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr))) != 0)
    {
        printf("socket bind failed\n");
        exit(0);
    }

    // Now server is ready to listen and verify
    if ((listen(sfd, 5)) != 0)
    {
        printf("Listen failed\n");
        exit(0);
    }

    while (1)
    {
        
        // Try to accept a client connection as descriptor newsock
        length = sizeof(caddr);
        cfd = accept(sfd, (struct sockaddr *)&caddr, &length);
        if (cfd < 0)
        {
            printf("server: accept error\n");
            exit(1);
        }

        printf("server: accepted a client connection from\n");
        printf("-------------------------------------------\n");
        printf("    IP=%s   port=%d\n", "127.0.0.1", ntohs(caddr.sin_port));
        printf("-------------------------------------------\n");

        // Processing loop
        while (1)
        {
            printf("server ready for next request ...\n");
            n = read(cfd, line, MAX);
            if (n==0)
            {
                printf("client died, server loops\n");
                close(cfd);
                break;
            }

            // Show the line string
            printf("server: read n=%d bytes; line=[%s]\n", n, line);
            strcat(line, " ECHO");


            // grab cmd
            char* cpy = strdup(line);
            char* token = strtok(cpy, " ");
            char* cmd = malloc(128);
            strcpy(cmd, token);
            token = strtok(NULL, " ");
            char* path = malloc(128);
            strcpy(path, token);

            printf("cmd = %s\n", cmd);
            int index = findCmd(cmd);
            int err, status;
            char buff[MAX];
            switch(index)
            {
                case 0: // get
                    printf("%s\n", path);
                    FILE* output = fopen(path, "r"); 
                    if(!output)
                    {
                        printf("Failed to open file\n");
                        continue;
                    }
                    fgets(buff, MAX, output);

                    if(write(cfd, buff, MAX) == -1)
                    {
                        printf("Error sending file\n");
                        break;
                    }
                    bzero(buff, MAX);
                    break;
                case 1: // put
                    printf("%s\n", path);
                    FILE* input = fopen(path, "w");
                        
                    int n = read(cfd, buff, MAX);
                    
                    fprintf(input, "%s", buff);
                    fclose(input);
                    bzero(buff, MAX);
                    break;
                case 2: // ls
                    strcpy(line, myls(path));
                    break;
                case 3: // cd
                    err = chdir(path);
                    if (err)
                        strcpy(line, "chdir failed");
                    else
                        strcpy(line, "chdir successful");
                    break;
                case 4: // pwd
                    getcwd(line, MAX);
                    break;
                case 5: // mkdir
                    err = mkdir(path, 0766);
                    if (err)
                        strcpy(line, "mkdir failed");
                    else
                        strcpy(line, "mkdir successful");
                    break;
                case 6: // rmdir
                    err = rmdir(path);
                    if (err)
                        strcpy(line, "rmdir unsuccessful");
                    else
                        strcpy(line, "rmdir successful");
                    break;
                case 7: // rm
                    err = unlink(path);
                    if (err)
                        strcpy(line, "rm failed");
                    else
                        strcpy(line, "rm successful");
                    break;
                default:
                    strcpy(line, "cmd entered not a valid command\n");
                    break;
            }

            // send the echo line to client
            n = write(cfd, line, MAX);
            printf("server: wrote n=%d bytes; ECHO=[%s]\n", n, line);
            printf("server: ready for next request\n");

           // free(cmd);
        }

    }

    free(root);
}