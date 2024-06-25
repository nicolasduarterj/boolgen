#ifndef BOOLGEN_H
#define BOOLGEN_H
#include "boolgen_utils.h"
#include <stdbool.h>
void print_truth_table(char *expression);
bool apply_expression(char syntax[], bool values[]);
#endif