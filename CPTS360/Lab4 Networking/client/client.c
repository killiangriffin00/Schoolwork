#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <libgen.h>
#include <time.h>

#define MAX 256
#define PORT 1234

char line[MAX], ans[MAX];
int n;

struct sockaddr_in saddr;
int sfd;

char *lcommands[] = {"lcat", "lls", "lcd", "lpwd", "lmkdir", "lrmdir", "lrm", 0};

int findCmd(char *command)
{
    int i = 0;
    while (lcommands[i])
    {
        if (strcmp(command, lcommands[i]) == 0)
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
    getcwd(h, MAX*30);
    dir = opendir(h);

    struct dirent* file = readdir(dir);
    while(file)
    {
        int e;
        struct stat fstat;
        struct stat* fp = &fstat;

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

int main(int argc, char* argv[], char* env[])
{
    int n; char how[64];
    int i, err;

    printf("1. create a socket\n");
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        printf("socket creation failed\n");
        exit(0);
    }

    printf("2. fill in server IP and port number\n");
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(PORT);

    printf("3. connect to server\n");
    if (connect(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) != 0)
    {
        printf("connection with the server failed\n");
        exit(0);
    }

    printf("************ processing loop ************\n");
    while (1)
    {
        // get cmd pathname from user
        printf("input a command : ");
        bzero(line, MAX);
        fgets(line, MAX, stdin);

        line[strlen(line) - 1] = 0;
        if (line[0] == 0)
        {
            write(sfd, "exit", MAX);
            exit(0);
        }


       
        char* t = strtok(line, " "), *l = strtok(NULL, " "), k[MAX];
        FILE* input = fopen(l, "r");
        switch(findCmd(t))
        {
            case 0: // lcat
                    while(1)
                    {
                        if(!fgets(k, MAX, input))
                        {
                            break;
                        }
                        
                        fprintf(stdout, "%s\n", k);
                    }
                    fclose(input);
                    continue;
                case 1: // lls
                    strcpy(line, myls(l));
                    continue;
                case 2: // lcd
                    err = chdir(l);
                    if (err)
                        strcpy(line, "chdir failed");
                    else
                        strcpy(line, "chdir successful");
                    continue;
                case 3: // lpwd
                    getcwd(line, MAX);
                    printf("%s\n", line);
                    continue;
                case 4: // lmkdir
                    err = mkdir(l, 0766);
                    if (err)
                        strcpy(line, "mkdir failed");
                    else
                        strcpy(line, "mkdir successful");
                    continue;
                case 5: // lrmdir
                    err = rmdir(l);
                    if (err)
                        strcpy(line, "rmdir unsuccessful");
                    else
                        strcpy(line, "rmdir successful");
                    continue;
                case 6: // lrm
                    err = unlink(l);
                    if (err)
                        strcpy(line, "rm failed");
                    else
                        strcpy(line, "rm successful");
                    continue;
                default:
                    break;
        }

        // Send ENTIRE line to server
        n = write(sfd, line, MAX);
        printf("client: wrote n=%d bytes; line=(%s)\n", n, line);

        // Read a line from sock and show it
        if(strcmp(t, "get") == 0)
        {
            FILE* input = fopen(l, "w");
            char buff[MAX];
                
            int n = read(sfd, buff, MAX);
            
            fprintf(input, "%s", buff);
            fclose(input);
            printf("client: read n = %d bytes; echo(%s)\n", n, ans);
            continue;
        }

        if(strcmp(t, "put") == 0)
        {
            FILE* output = fopen(l, "r");
            char buff[MAX];
                
            fgets(buff, MAX, output);
            
            if(write(sfd, buff, MAX) == -1)
            {
                printf("Error sending file\n");
            }
            continue;
        }

        n = read(sfd, ans, MAX);
        printf("client: read n = %d bytes; echo(%s)\n", n, ans);
    }
}