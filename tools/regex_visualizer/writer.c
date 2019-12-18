#include <stdio.h>
#include "writer.h"
void fwrite(regex *re, FILE *f)
{
    
    
    re_free(re);
}
void write(regex *re)
{
    fwrite(re, stdout);
}