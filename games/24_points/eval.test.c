#include <stdio.h>
#include "eval.h"

int main()
{
    struct {
        char *description;
        int a;
        int b;
        int c;
        int d;
        char *expression;
        bool isvalid;
        double expected;
    } tests[] = 
    {
        "do basic calculation without brackets", 1, 2, 3, 4, "a+b+c+d", true, 1+2+3+4,
        "do basic calculation without brackets", 1, 2, 3, 4, "a-b+c-d", true, 1-2+3-4,
        "do basic calculation without brackets", 1, 2, 3, 4, "a*b/c*d", true, (double)1*2/3*4,
        "do basic calculation without brackets", 1, 2, 3, 4, "a/b*c/d", true, (double)1/2*3/4,
        "do basic calculation without brackets", 97, 2, 86, 65, "a*b/c*d", true, (double)97*2/86*65,
        "do basic calculation without brackets", 10, 60, 0, 66, "a/b*c/d", true, (double)10/60*0/66,
        "do * and / before + and -", 1, 2, 3, 4, "a+b*c-d", true, (double)1+2*3-4,
        "do * and / before + and -", 1, 2, 3, 4, "a+b/c-d", true, 1+(double)2/3-4,
        "interpret / as fraction division instead of integer division", 1, 2, 2, 4, "a/b*c-d", true, (double)1/2*2-4,
        "deal with unary + and -", 1, 2, 3, 4, "(-a)+b+c+d", true, (-1)+2+3+4,
        "deal with unary + and -", 1, 2, 3, 4, "a+(-b)+c+d", true, 1+(-2)+3+4,
        "deal with unary + and -", 1, 2, 3, 4, "a+b*(+c)+d", true, 1+2*(+3)+4,
        "deal with brackets", 1, 2, 3, 4, "(a+b+c+d)", true, 1+2+3+4,
        "deal with brackets", 1, 2, 3, 4, "a*(b+c)*d", true, 1*(2+3)*4,
        "deal with brackets", 1, 2, 3, 4, "a/(b+c+d)", true, 1/((double)2+3+4),
        "deal with brackets", 1, 2, 3, 4, "((((-a)+b)*c)/(-d))", true, ((((-1)+2)*3)/(-(double)4)),
        "deal with spaces", 1, 2, 3, 4, "     \t a +b + c\t + d   ", true, 1+2+3+4,
        "detect invalid brackets", 1, 2, 3, 4, "a)+b+c+d", false, 0,
        "detect invalid brackets", 1, 2, 3, 4, "(a+b))+c+d", false, 0,
        "detect invalid brackets", 1, 2, 3, 4, "(a+b+c+d", false, 0,
        "detect invalid brackets", 1, 2, 3, 4, "(a+(b+c+d)", false, 0,
        "detect invalid brackets", 1, 2, 3, 4, "(-a)+((b+c+d", false, 0,
        "detect invalid brackets", 1, 2, 3, 4, "a()+b+c+d", false, 0,
        "detect invalid brackets", 1, 2, 3, 4, "a(+b+c)+d", false, 0,
        "detect omissions of operators", 1, 2, 3, 4, "ab+c+d", false, 0,
        "detect division by zero", 1, 0, 3, 4, "a/b+c+d", false, 0,
        "detect division by zero", 1, 2, 4, 4, "a+b/(c-d)", false, 0,
        "detect division by zero", 1, 1, 100, 0, "a/(b/c-d)", true, 1/((double)1/100-0),
    };
    int total = sizeof tests / sizeof *tests, passed = 0;
    for (int i = 0; i < sizeof tests / sizeof *tests; ++i)
    {
        double answer;
        bool isvalid = eval(tests[i].expression, tests[i].a, tests[i].b, tests[i].c, tests[i].d, &answer);
        if (isvalid != tests[i].isvalid || (isvalid && answer != tests[i].expected))
        {
            printf("\nTest failed:\n");
            printf("\nIt should %s\n", tests[i].description);
            printf("a = %d\tb = %d\tc = %d\td = %d\n", tests[i].a, tests[i].b, tests[i].c, tests[i].d);
            printf("expression: \"%s\"\n", tests[i].expression);
            printf("Expected:\t");
            tests[i].isvalid ? printf("%f\n", tests[i].expected) : printf("Invalid\n");
            printf("Instead got:\t");
            isvalid ? printf("%f\n", answer) : printf("Invalid\n");
        }
        else
            ++passed;
    }
    if (passed == total)
        printf("\nAll %d tests passed\n", total);
    else
        printf("\n%d/%d tests passed, %d failed\n", passed, total, total - passed);
}