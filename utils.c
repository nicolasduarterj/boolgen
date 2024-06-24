#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
bool
f (char syntax[], bool values[])
{
  bool sum_acc = false;    // Elemento identidade do monóide (Bool, ||)
  bool product_acc = true; // Elemento identidade do monóide (Bool, &&)
  bool not = false;
  for (int i = 0; i < strlen (syntax); i++)
    {
      if (syntax[i] >= 'A' && syntax[i] <= 'E')
        product_acc = product_acc && values[syntax[i] - 'A'];
      else if (syntax[i] == '+')
        {
          sum_acc = sum_acc || product_acc;
          product_acc = true;
        }
      else if (syntax[i] == '(')
        {
          int distance = distance_to_end_of_block (syntax, i);
          char subsyntax[strlen (syntax)];
          for (int j = 0; j < strlen (syntax); j++)
            subsyntax[j] = 0;
          // Copia o que está entre os parênteses
          strncpy (subsyntax, syntax + i + 1, distance - 1);
          bool result = f (subsyntax, values);
          if (not )
            result = !result;
          product_acc = product_acc && result;
          i = i + distance - 1;
          not = false;
        }
      else if (syntax[i] == '!')
        not = true;
    }
  sum_acc = sum_acc || product_acc;
  return sum_acc;
}

char *
xorfilter (char *syntax)
{
  char *pointertox = strchr (syntax, 'x');
  char copy[strlen (syntax)];
  char a[strlen (syntax)];
  char b[strlen (syntax)];
  char *begginingofa = NULL;
  char *endofb = NULL;
  strncpy (copy, syntax, strlen (syntax));
  if (*(pointertox - 1) >= 'A' && *(pointertox - 1) <= 'E')
    {
      begginingofa = pointertox - 1;
      a[0] = *(pointertox - 1);
      a[1] = '\0';
    }
  else if (*(pointertox - 1) == ')')
    {
      int parentheses_count = 0;
      for (char *i = pointertox; i >= syntax; i--)
        {
          if (*i == ')')
            parentheses_count++;
          if (*i == '(' && --parentheses_count == 0)
            {
              begginingofa = i;
              break;
            }
        }
      strncpy (a, begginingofa, pointertox - begginingofa);
      a[pointertox - begginingofa] = '\0';
    }
  if (*(pointertox + 1) >= 'A' && *(pointertox + 1) <= 'E')
    {
      endofb = pointertox + 1;
      b[0] = *(pointertox + 1);
      b[1] = '\0';
    }
  else if (*(pointertox + 1) == '(')
    {
      int parentheses_count = 0;
      for (char *i = pointertox; i <= syntax + strlen (syntax); i++)
        {

          if (*i == '(')
            parentheses_count++;
          if (*i == ')' && --parentheses_count == 0)
            {
              endofb = i;
              break;
            }
        }
      strncpy (b, pointertox + 1, endofb - pointertox);
      b[endofb - pointertox] = '\0';
    }
  char *newstring = calloc (strlen (syntax) * 3, sizeof (char));
  strncpy (newstring, syntax, begginingofa - syntax);
  strcat (newstring, "(");
  strcat (newstring, a);
  strcat (newstring, "!(");
  strcat (newstring, b);
  strcat (newstring, ")+!(");
  strcat (newstring, a);
  strcat (newstring, ")");
  strcat (newstring, b);
  strcat (newstring, ")");
  strcat (newstring, endofb + 1);
  return newstring;
}

int
distance_to_end_of_block (char syntax[], int start_index)
{
  int parentheses_count = 1;
  int indexofend = -1;
  for (int i = start_index + 1; i < strlen (syntax); i++)
    {
      if (syntax[i] == '(')
        parentheses_count++;
      else if (syntax[i] == ')' && --parentheses_count == 0)
        {
          indexofend = i;
          break;
        }
    }
  return indexofend - start_index;
}

int
varcount (char syntax[])
{
  long acc = 1;
  int counter = 0;
  for (int i = 0; i < strlen (syntax); i++)
    {
      if (syntax[i] >= 'A' && syntax[i] <= 'E' && acc % syntax[i] != 0)
        {
          acc = acc * syntax[i];
          counter++;
        }
    }
  return counter;
}