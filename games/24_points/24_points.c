#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "eval.h"
#define MAX 100
#define MIN 0
static int range[5] = {20, 40, 60, 80, 100};
static char info[] = 
"\n"
"**** 24 Points ****\n"
"\n"
"Usage:\n"
"\n"
"$> ./24p.exe -e\n"
"\tOpen in exploration mode,\n"
"\tin which you give the computer 4 numbers and see possible solutions\n"
"$> ./24.exe -c\n"
"\tOpen in challenge mode,\n"
"\tin which you are given 4 numbers and you must input a valid expression to make 24 points\n"
;
static char exploration_info[] = 
"\n"
"**** 24 Points ****\n"
"\n"
"Welcome to 24 Points, you are in exploration mode\n"
;
static char challenge_info[] = 
"\n"
"**** 24 Points ****\n"
"\n"
"Welcome to 24 Points, you are in challenge mode\n"
;
static char goodbye_info[] = 
"\n"
"**** 24 Points ****\n"
"\n"
"Thank you for playing!\n"
"Author: Yihao Wang, 11/12/2019\n"
;
void clear()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
void exploration()
{
    printf("%s\n", exploration_info);
    while(1)
    {
        int a, b, c, d;
        char s[100];
        char buf[20000];
        printf("Please input 4 integers between %d and %d:\n", MIN, MAX);
        while (scanf_s("%d %d %d %d", &a, &b, &c, &d) != 4
            || a < MIN || a > MAX
            || b < MIN || b > MAX
            || c < MIN || c > MAX
            || d < MIN || d > MAX)
        {
            printf("Invalid inputs, please try again!\n");
            clear();
        }
        clear();
        solve(a, b, c, d, buf);
        printf("%s\n", buf);
        char q;
        printf("Enter 'q' to quit game, or any other key to continue:\n");
        if (scanf_s("%c", &q) == 1 && q == 'q')
            return;
        else
            clear();
    }
}
void challenge()
{
    printf("%s\n", challenge_info);
    printf("Please choose a level from 1 - 5 where 1 = easiest and 5 = hardest:\n");
    int level;
    while (scanf_s("%d", &level) != 1 || level < 1 || level > 5)
    {
        printf("Invalid input, try again!\n");
        clear();
    }
    clear();
    int max = range[level];
    int a, b, c, d;
    do
    {
        srand((unsigned)time((time_t *)NULL));
        a = rand() % max;
        b = rand() % max;
        c = rand() % max;
        d = rand() % max;
    } while (!solve(a, b, c, d, NULL));
    printf("Make 24 using the following numbers\n");
    printf("%d %d %d %d\n", a, b, c, d);
    char solution[256];
    int answer;
    while (1)
    {
        printf("Please input your solution, which may only use +-*/ and () and must use all 4 numbers:\n");
        while (scanf_s("%s", &solution) != 1 || !eval(solution, a, b, c, d, &answer))
        {
            printf("Invalid input, please try again!\n");
            clear();
        }
        clear();
        if (answer == 24)
        {
            printf("Yes! Congratulations!\n");
            break;
        }
        else
        {
            printf("Sorry, wrong answer\n");
        }
    }
}
int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1][0] != '-' || (argv[1][1] != 'e' && argv[1][1] != 'c'))
    {
        printf("%s\n", info);
        return -1;
    }
    argv[1][1] == 'e' ? exploration() : challenge();
    printf("%s\n", goodbye_info);
    return 0;
}