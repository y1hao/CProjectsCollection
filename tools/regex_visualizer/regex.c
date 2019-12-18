#include <stdlib.h>
#include <stdbool.h>
#include "regex.h"
struct regex {
    char *content;
    struct regex *next;
    struct regex *or;
    struct regex *prefix;
    struct regex *suffix;
    int len;
    int depth;
    bool is_charset;
    bool is_fix;
    bool is_group;
    bool is_group_sym;
    bool is_compulsory;
    bool is_multi;
    bool is_greedy;
};