#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "solve.h"
#define BUFSIZE 1000
static char buf[BUFSIZE];
void test(int a, int b, int c, int d)
{
    printf("\nTesting: a = %d\tb = %d\tc = %d\td = %d:\n", a, b, c, d);
    if (!solve(a, b, c, d, buf, sizeof buf))
    {
        printf("No solutions\n");
    }   
    else
    {
        printf("%s\n", buf);
    }      
}
int main()
{
    int n = 100;
    srand((unsigned)time(NULL));
    while (--n >= 0)
        test(rand() % 50, rand() % 50, rand() % 50, rand() % 50);
}