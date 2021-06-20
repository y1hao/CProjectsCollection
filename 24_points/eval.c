#include <stdio.h>
#include <stdbool.h>
#include "eval.h"
bool eval_expr(char *s, char end, int a, int b, int c, int d, 
            int *position, bool *has_a, bool *has_b, bool *has_c, bool *has_d, double *res)
{
    double vals[4] = {1, 1, 1, 1};
    char ops[4];
    int vp = 0, op = 0;
    char cur;
    while ((cur = s[(*position)++]) != end && cur != '\0' && cur != '\n')
    {
        switch (cur)
        {
            case ' ': case '\t':
                break;
            case 'a':
                if ((vp != op) || *has_a)
                    return false;
                *has_a = true;
                vals[vp++] *= a;
                break;
            case 'b':
                 if ((vp != op) || *has_b)
                    return false;
                *has_b = true;
                vals[vp++] *= b;
                break;
            case 'c':
                 if ((vp != op) || *has_c)
                    return false;
                *has_c = true;
                vals[vp++] *= c;
                break;
            case 'd':
                 if ((vp != op) || *has_d)
                    return false;
                *has_d = true;
                vals[vp++] *= d;
                break;
            case '(':
                double res;
                if (!eval_expr(s, ')', a, b, c, d, position, has_a, has_b, has_c, has_d, &res))
                    return false;
                if (vp != op)
                    return false;
                vals[vp++] *= res;
                break;
            case '*':
                if (vp - op != 1)
                    return false;
                ops[op++] = '*';
                break;
            case '/':
                if (vp - op != 1)
                    return false;
                ops[op++] = '/';
                break;
            case '+':
                if (vp != op)
                {
                    if (vp - op != 1)
                        return false;
                    ops[op++] = '+';
                }
                break;
            case '-':
                if (vp == op)
                    vals[vp] *= -1;
                else
                {
                    if (vp - op != 1)
                        return false;
                    ops[op++] = '-';
                }
                break;
            default:
                return false;
        }
        char top;
        if (vp - op == 1 && op != 0 && ((top = ops[op - 1]) == '*' || top == '/'))
        {
            char operator = ops[--op];
            double v2 = vals[--vp], v1 = vals[--vp];
            vals[vp] = vals[vp + 1] = 1;
            if (top == '/')
            {
                if (v2 == 0)
                    return false;
                vals[vp++] = v1 / v2;
            } 
            else
                vals[vp++] = v1 * v2;
        }
    }
    if (vp - op != 1)
        return false;
    int vbp = 0, obp = 0;
    while (obp < op)
    {
        double v1 = vals[vbp++], v2 = vals[vbp];
        char operand = ops[obp++];
        vals[vbp] = operand == '+' ? v1 + v2 : v1 - v2;
    }
    *res = vals[vbp];
    return true;
}
bool eval(char *s, int a, int b, int c, int d, double *answer)
{
    bool has_a = false, has_b = false, has_c = false, has_d = false;
    int position = 0;
    bool cond = eval_expr(s, '\0', a, b, c, d, &position, &has_a, &has_b, &has_c, &has_d, answer);
    return cond && has_a && has_b && has_c && has_d;
} 