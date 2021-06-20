#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "solve.h"
#include "eval.h"
#define BUFSIZE 1000
#define CRIT 1.0/10000
#define MIN 1
#define MAX 50
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
void getline(char *s, int size)
{
    int c;
    int count = 0;
    while ((c = getchar()) != '\n' && c != EOF && count < size - 1)
        s[count++] = (char)c;
    if (c != '\n' && c != EOF)
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    s[count] = '\0';
}
void exploration()
{
    printf("%s\n", exploration_info);
    while(true)
    {
        int a, b, c, d;
        char s[100];
        char buf[BUFSIZE];
        printf("Please input 4 integers a, b, c and d between %d and %d:\n", MIN, MAX);
        while (scanf_s("%d %d %d %d", &a, &b, &c, &d, sizeof buf) != 4
            || a < MIN || a > MAX
            || b < MIN || b > MAX
            || c < MIN || c > MAX
            || d < MIN || d > MAX)
        {
            printf("Invalid inputs, please try again!\n");
            clear();
        }
        clear();
        if (!solve(a, b, c, d, buf, sizeof buf))
            printf("\nNo possible solutions\n");
        else
            printf("\nSolutions are (only 10 of them are displayed if there are too many):\n%s\n", buf);
        char q;
        printf("Enter 'q' to quit game, or any other key to continue:\n");
        if (scanf_s("%c", &q, sizeof q) == 1 && q == 'q')
            return;
        else
            clear();
    }
}
void challenge()
{
    printf("%s\n", challenge_info);
    while (true)
    {
        printf("Please choose the upper limit of number (at most %d)\n", MAX);
        int max;
        while (scanf_s("%d", &max, sizeof max) != 1 || max < MIN || max > MAX)
        {
            printf("Invalid input, try again!\n");
            clear();
        }
        clear();
        char buf[BUFSIZE];
        int a, b, c, d;
        do
        {
            srand((unsigned)time((time_t *)NULL));
            a = rand() % max + 1;
            b = rand() % max + 1;
            c = rand() % max + 1;
            d = rand() % max + 1;
        } while (!solve(a, b, c, d, buf, sizeof buf));
        printf("Make 24 using the following numbers\n");
        printf("a = %d\tb = %d\tc = %d\td = %d\n", a, b, c, d);
        char solution[256];
        double answer;
        while (true)
        {
            printf("Please input your solution, which may only use +-*/ and () and must use all 4 numbers\n");
            printf("(Use letters a, b, c and d instead of actual numbers):\n");
            getline(solution, sizeof solution / sizeof *solution);
            while (!eval(solution, a, b, c, d, &answer))
            {
                printf("Invalid input, please try again!\n");
                getline(solution, sizeof solution / sizeof *solution);
            }
            if ((answer < 24 ? 24 - answer : answer - 24) < CRIT)
            {
                printf("Yes! Congratulations!\n");
                printf("Enter 'n' to see solutions and start a new round,"
                    "\nor any other key to see solutions and end game\n");
                char cond;
                if (scanf_s("%c", &cond, sizeof cond) == 1 && cond == 'n')
                {
                    printf("\nSolutions are (only 10 of them are displayed if there are too many):\n%s\n", buf);
                    clear();
                    break;
                }
                else
                {
                    printf("\nSolutions are (only 10 of them are displayed if there are too many):\n%s\n", buf);
                    return;
                }
            }
            else
            {
                printf("Sorry, wrong answer\n");
                printf("Enter 'n' to see solutions and start a new round"
                    "\nor 'q' to see solutions and quit"
                    "\nor any other key to try again\n");
                char cond;
                if (scanf_s("%c", &cond, sizeof cond) != 1 || (cond != 'n' && cond != 'q'))
                    clear();
                else
                {
                    printf("\nSolutions are (only 10 of them are displayed if there are too many):\n%s\n", buf);
                    if (cond == 'q')
                        return;
                    clear();
                    break;
                }
            }
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