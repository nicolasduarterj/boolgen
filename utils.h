#ifndef BOOLGEN_UTILS_H
#define BOOLGEN_UTILS_H
#include <stdbool.h>

char *xorfilter (char *syntax);
int distance_to_end_of_block (char syntax[], int start_index);
bool f (char syntax[], bool values[]);
int varcount (char syntax[]);

#endif