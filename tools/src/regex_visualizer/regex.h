#ifndef REGEX_VISUALIZER_H
#define REGEX_VISUALIZER_H
#include <stdbool.h>
typedef struct regex regex;
extern regex *re_new();
extern void *re_free();
extern void re_append(regex *,regex *);
extern void re_setmult(regex *);
extern void re_setcompulsory(regex *);
extern void re_setnongreedy(regex *);
#endif