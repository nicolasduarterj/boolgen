#include "boolgen.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_truth_table(char *expression)
{
    int vc = varcount(expression);
    bool values[] = {false, false, false, false, false};

    // Have to do the first run here; division by zero problem.
    //--------------------[START OF FIRST RUN]--------------------------//
    bool first_time_values[] = {false, false, false, false, false};
    printf("| ");
    for (int i = 5 - vc, j = 0; i < 5; i++, j++)
    {
        printf("%d ", values[i]);
        first_time_values[j] = values[i];
    }
    printf("| %d |\n", f(expression, first_time_values));
    //--------------------[END OF FIRST RUN]----------------------------//

    for (int i = 1; i < pow(2.0, (double)vc); i++)
    {
        printf("| ");
        // Alternates each variable to simulate the permutations.
        values[0] = i % 16 == 0 ? !values[0] : values[0];
        values[1] = i % 8 == 0 ? !values[1] : values[1];
        values[2] = i % 4 == 0 ? !values[2] : values[2];
        values[3] = i % 2 == 0 ? !values[3] : values[3];
        values[4] = !values[4];

        /*f requires an ordered array, therefore we transfer the
          desired subarray of values[], in order, to a padded tmparray*/
        bool tmpvalues[] = {false, false, false, false, false};
        for (int j = 5 - vc, k = 0; j < 5; j++, k++)
        {
            printf("%d ", values[j]);
            tmpvalues[k] = values[j];
        }
        printf("| %d |\n", f(expression, tmpvalues));
    }
}

bool apply_expression(char syntax[], bool values[])
{
    char *filteredsyntax = calloc(strlen(syntax), sizeof(char));
    strcpy(filteredsyntax, syntax);
    while (strchr(filteredsyntax, 'x') != NULL)
    {
        char *oldsyntax = filteredsyntax;
        filteredsyntax = xorfilter(oldsyntax);
        free(oldsyntax);
    }
    return f(filteredsyntax, values);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("***\nusage: %s syntax\n\n"
               "AND is implied by juxtaposition\n"
               "OR is +\n"
               "XOR is x\n"
               "NOT is !\n\n"
               "Please use parentheses around xor and not arguments\n"
               "Please name variables alphabetically."
               " (e.g. syntax should be B+AC not B+AD, skipping C.)\n***\n",
               argv[0]);
        return 1;
    }
    char *filteredsyntax = calloc(strlen(argv[1]), sizeof(char));
    strcpy(filteredsyntax, argv[1]);
    while (strchr(filteredsyntax, 'x') != NULL)
    {
        char *oldsyntax = filteredsyntax;
        filteredsyntax = xorfilter(oldsyntax);
        free(oldsyntax);
    }
    printf("normalized: %s\n", filteredsyntax);
    print_truth_table(filteredsyntax);
    free(filteredsyntax);
    return 0;
}
