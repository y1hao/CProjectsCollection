#include <stdlib.h>
#include <stdbool.h>
#include "regex.h"
struct regex {
    struct regex *next;
    char *content;
    struct regex *or;
    struct regex *prefix;
    struct regex *suffix;
    bool compulsory;
    bool multi;
    bool greedy;
};