#include <stdio.h>
#include "regex.h"
#include "parser.h"
#include "writer.h"

char info[] = "";

int main(int argc, char *argv[]) 
{
    if (argc != 2)
        fprintf(stderr, info);
    else 
    {
        struct regex *re = NULL;
        if (parse(argv[1], re))
            write(re);
        else
            fprintf(stder, "The input is not a valid regular expression");
    }
}