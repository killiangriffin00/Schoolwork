#include <stdio.h>

typedef unsigned int u32;

char *tab = "0123456789ABCDEF";
//int  BASE = 10; 

int rpu(u32 x, int b)
{  
    char c;
    if (x){
       c = tab[x % b];
       rpu(x / b, b);
       putchar(c);
    }
}

int printu(u32 x)
{
    (x==0)? putchar('0') : rpu(abs(x), 10);
    putchar(' ');
}

int prints(char* s)
{
    char* c = s;
    while(*c != '\0')
    {
        putchar(*c);
        ++c;
    }
}

int printd(int x)
{
    if(x < 0)
    {
        putchar('-');
    }

    (x==0)? putchar('0') : rpu(abs(x), 10);
    putchar(' ');
}

int printx(int x)
{
    if(x < 0)
    {
        putchar('-');
    }
    putchar('0');
    putchar('x');

    (x==0)? putchar('0') : rpu(abs(x), 16);
    putchar(' ');
}

int printo(int x)
{
    if(x < 0)
    {
        putchar('-');
    }
    putchar('0');

    (x==0)? putchar('0') : rpu(abs(x), 8);
    putchar(' ');
}

int abs(int x)
{
    if(x < 0)
    {
        return x*-1;
    }
    return x;
}

int myprintf(char *fmt, ...)
{
    char* s = fmt;
    int* arg = ((int*)&fmt) + 1;

    while(*s != '\0')
    {
        if(*s == '\n')
        {
            putchar('\r');
        }

        if(*s == '%')
        {
            switch(*(s + 1))
            {
                case 'c':
                    putchar(*arg);
                    break;

                case 's':
                    prints(*arg);
                    break;

                case 'u':
                    printu(*arg);
                    break;

                case 'd':
                    printd(*arg);
                    break;

                case 'o':
                    printo(*arg);
                    break;

                case 'x':
                    printx(*arg);
                    break;
            }
            ++arg;
            ++s;
        }
        else 
        putchar(*s);
        ++s;
    }
    return;
}

int main(int argc, char *argv[ ], char *env[ ])
{
    myprintf("argv=");
    for(int i = 1; i < argc; ++i)
    {
        myprintf("%s ", argv[i]);
    }
    myprintf("\n");
    
    myprintf("cha=%c string=%s dec=%d hex=%x oct=%o neg=%d\n", 'A', "this is a test", 100,    100,   100,  -100);

    return; 
}