#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "solve.h"
#include "eval.h"
#define CRIT 1.0/10000
#define get(n,x) ((n>>(x))&1U)
static char *templates[] = 
{
//      *    *    *
//     *   *   *   *
//             111111111
//   0123456789012345678
    "((a+  b)+ c) +d  \n",
    " (a+  b)+(c  +d) \n",
    " (a+ (b + c))+d  \n",
    "  a+((b + c) +d) \n",
    "  a+ (b +(c  +d))\n",
};
static int begs[] = {2, 6, 10, 14};
static int opps[] = {3, 8, 13};
static int len = 19;
static char *perms[] = 
{
    "abcd", "abdc", "acbd", "acdb", "adbc", "adcb",
    "bacd", "badc", "bcad", "bcda", "bdac", "bdca",
    "cabd", "cadb", "cbad", "cbda", "cdab", "cdba",
    "dabc", "dacb", "dbac", "dbca", "dcab", "dcba",
};
static char ops[] = "+-*/";
bool is24(double n)
{
    return (n - 24 > 0 ? n - 24 : 24 - n) < CRIT;
}
void condense(char *buf, int size)
{
    char newbuf[size];
    int i = 0, j = 0;
    char c;
    while ((c = buf[i++]) != '\0' && i < size)
        if (c != ' ')
            newbuf[j++] = c;
    newbuf[j] = '\0';
    for (i = 0; i <= j; ++i)
        buf[i] = newbuf[i];
}
bool solve(int a, int b, int c, int d, char* buf, int size)
{
    char cur[len];
    int i = 0;
    int n = 0;
    *buf = '\0';
    for (int it = 0; it < sizeof templates / sizeof *templates; ++it)
    {
        memcpy(cur, templates[it], len);
        for (int ip = 0; ip < sizeof perms / sizeof *perms; ++ip)
        {
            for (int i = 0; i < 4; ++i)
                cur[begs[i]] = perms[ip][i];
            for (int i1 = 0; i1 < 4; ++i1)
                for (int i2 = 0; i2 < 4; ++i2)
                    for (int i3 = 0; i3 < 4; ++i3)
                    {
                        cur[opps[0]] = ops[i1];
                        cur[opps[1]] = ops[i2];
                        cur[opps[2]] = ops[i3];
                        double ans;
                        eval(cur, a, b, c, d, &ans);
                        if (is24(ans))
                        {
                            strcat_s(buf, size, cur);
                            ++n;
                            if (n == 10)
                            {
                                condense(buf, size);
                                return true;
                            }   
                        }
                    }
        }
    }
    condense(buf, size);
    return n > 0;
}