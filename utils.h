#ifndef BOOLGEN_UTILS_H
#define BOOLGEN_UTILS_H
#include <stdbool.h>

char *xorfilter (char *syntax);
int n_of_chars_inbetween_parentheses (char *entrypoint, char direction);
bool f (char syntax[], bool values[]);
int varcount (char syntax[]);

#endif