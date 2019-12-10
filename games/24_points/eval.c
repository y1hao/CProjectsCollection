#include <stdio.h>
#include <stdbool.h>
#include "eval.h"
bool eval_expr(char *s, int a, int b, int c, int d, 
            int *position, bool *has_a, bool *has_b, bool *has_c, bool *has_d, int *res)
{

}

bool eval(char *s, int a, int b, int c, int d, int *answer)
{
    bool has_a = false, has_b = false, has_c = false, has_d = false;
    int position = 0;
    char c;
    while ((c = s[position++]) != '\0')
    {

    }
    return has_a && has_b && has_c && has_d;
}