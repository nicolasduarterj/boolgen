#include "utils.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
print_truth_table (char *expression)
{
  int vc = varcount (expression);
  bool values[] = { false, false, false, false, false };
  // Fazer a primeira vez fora do loop porque não se pode dividir por 0
  bool first_time_values[] = { false, false, false, false, false };
  printf ("| ");
  for (int i = 5 - vc, j = 0; i < 5; i++, j++)
    {
      printf ("%d ", values[i]);
      first_time_values[j] = values[i];
    }
  printf ("| %d |\n", f (expression, first_time_values));
  //-----------------------------------------------------------------
  for (int i = 1; i < pow (2.0, (double)vc); i++)
    {
      printf ("| ");
      values[0] = i % 16 == 0 ? !values[0] : values[0];
      values[1] = i % 8 == 0 ? !values[1] : values[1];
      values[2] = i % 4 == 0 ? !values[2] : values[2];
      values[3] = i % 2 == 0 ? !values[3] : values[3];
      values[4] = !values[4];
      bool tempvalues2[] = { false, false, false, false, false };
      for (int j = 5 - vc, k = 0; j < 5; j++, k++)
        {
          printf ("%d ", values[j]);
          tempvalues2[k] = values[j];
        }
      printf ("| %d |\n", f (expression, tempvalues2));
    }
}

int
main (int argc, char *argv[])
{
  if (argc < 2)
    {
      printf ("***\nusage: %s syntax\n\n"
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
  char *filteredsyntax = calloc (strlen (argv[1]), sizeof (char));
  strcpy (filteredsyntax, argv[1]);
  while (strchr (filteredsyntax, 'x') != NULL)
    filteredsyntax = xorfilter (filteredsyntax);
  print_truth_table (filteredsyntax);
  return 0;
}
