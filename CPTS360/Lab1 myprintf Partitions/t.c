/************* t.c file ********************/
#include <stdio.h>
#include <stdlib.h>

int *FP;

int main(int argc, char *argv[ ], char *env[ ])
{
  int a,b,c;
  printf("enter main\n");
  
  printf("&argc=%x argv=%x env=%x\n", &argc, argv, env);
  printf("&a=%8x &b=%8x &c=%8x\n", &a, &b, &c);

// (1). Write C code to print values of argc and argv[] entries

  printf("argc=%d argv=%d\n", argc, *argv);

  a=1; b=2; c=3;
  A(a,b);
  printf("exit main\n");
}

int A(int x, int y)
{
  int d,e,f;
  printf("enter A\n");
  // write C code to PRINT ADDRESS OF d, e, f
  printf("&d=%d &e=%d &f=%d\n", &d, &e, &f);
  d=4; e=5; f=6;
  B(d,e);
  printf("exit A\n");
}

int B(int x, int y)
{
  int g,h,i;
  printf("enter B\n");
  // write C code to PRINT ADDRESS OF g,h,i
  printf("&g=%d &h=%d &i=%d\n", &g, &h, &i);
  g=7; h=8; i=9;
  C(g,h);
  printf("exit B\n");
}

int C(int x, int y)
{
  int u, v, w, i, *p;

  printf("enter C\n");
  // write C cdoe to PRINT ADDRESS OF u,v,w,i,p;
  printf("&u=%d &v=%d &w=%d &i=%d &p=%d\n", &u, &v, &w, &i, &p);
  u=10; v=11; w=12; i=13;

  FP = (int *)getebp();  // FP = stack frame pointer of the C() function
  // print FP value in HEX  
  printf("FP=%x\n", FP);

// (2). Write C code to print the stack frame link list.
  printf("C stack frame:\ny=*%d=%d | x=*%d=%d | PC=*%d | FP=*%d | u=*%d=%d | v=*%d=%d | w=*%d=%d | i=*%d=%d | p=*%d=%d\n",
   FP+3, *(FP+3), FP+2, *(FP+2), FP+1, FP, FP-13, *(FP-13), FP-12, *(FP-12), FP-11, *(FP-11), FP-10, *(FP-10), FP-9, *(FP-9));

 p = (int *)&p;

/*
(3). Print the stack contents from p to the frame of main()
     YOU MAY JUST PRINT 128 entries of the stack contents.
*/
  printf("STACK CONTENTS:\n");
  for(int index = 0; index < 50; ++index)
  {
    printf("%d : %d\n", ((FP-9)+index), *((FP-9)+index));
  }

/*
(4). On a hard copy of the print out, identify the stack contents
     as LOCAL VARIABLES, PARAMETERS, stack frame pointer of each function. 
*/
}