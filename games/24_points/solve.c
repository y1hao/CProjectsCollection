#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "solve.h"
#include "eval.h"
#define CRIT 1.0/10000
#define get(n,x) ((n>>(x))&1U)
static char *templates[] = 
{
//         *       *       *
//     *      *      *      *
//             1111111111222222222
//   01234567890123456789012345678
    "(((-a)+  (-b))+ (-c)) +(-d)  \n",
    " ((-a)+  (-b))+((-c)  +(-d)) \n",
    " ((-a)+ ((-b) + (-c)))+(-d)  \n",
    "  (-a)+(((-b) + (-c)) +(-d)) \n",
    "  (-a)+ ((-b) +((-c)  +(-d)))\n",
};
static int begs[] = {2, 9, 16, 23};
static int opps[] = {6, 14, 22};
static int len = 31;
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
bool solve(int a, int b, int c, int d, char* buf, int size)
{
    char cur[len];
    int i = 0;
    int n = 0;
    *buf = '\0';
    int temp = 0;
    for (int it = 0; it < sizeof templates / sizeof *templates; ++it)
    {
        memcpy(cur, templates[it], len);
        for (int ip = 0; ip < sizeof perms / sizeof *perms; ++ip)
        {
            for (unsigned neg = 1; neg <= 1U << 4; ++neg)
            {
                for (int i = 0; i < 4; ++i)
                {
                    int beg = begs[i];
                    if (!get(neg, i))
                    {
                        cur[beg++] = '(';
                        cur[beg++] = '-';
                        cur[beg++] = perms[ip][i];
                        cur[beg] = ')';
                    }
                    else
                    {
                        cur[beg++] = ' ';
                        cur[beg++] = ' ';
                        cur[beg++] = perms[ip][i];
                        cur[beg] = ' ';
                    }
                }
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
                                    return true;
                            }
                        }
            }
        }
    }
    return n > 0;
}