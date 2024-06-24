#ifndef BOOLGEN_UTILS_H
#define BOOLGEN_UTILS_H
#include <stdbool.h>

char *xorfilter(char *syntax);
// entrypoint = pointer to the opening parentheses; direction = 'l' or 'r'
int n_of_chars_inbetween_parentheses(char *entrypoint, char direction);
bool f(char syntax[], bool values[]);
int varcount(char syntax[]);

#endif