#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool
f (char syntax[], bool values[])
{
  bool sum_acc = false;    // Identity element of the monoid (Bool, ||)
  bool product_acc = true; // Identity element of the monoid (Bool, &&)
  bool not = false;
  for (int i = 0; i < strlen (syntax); i++)
    {
      if (syntax[i] >= 'A' && syntax[i] <= 'E')
        product_acc = product_acc && values[syntax[i] - 'A'];
      else if (syntax[i] == '+')
        {
          sum_acc = sum_acc || product_acc;
          product_acc = true; // Reverts to the identity element
        }
      else if (syntax[i] == '(')
        {
          int size = n_of_chars_inbetween_parentheses (syntax + i, 'r');
          char *subsyntax = calloc (strlen (syntax), sizeof (char));
          // Copies the content in between parentheses
          strncpy (subsyntax, syntax + i + 1, size);
          bool result = f (subsyntax, values);
          if (not )
            result = !result;
          product_acc = product_acc && result;
          i = i + 1 + size;
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
      a[0] = *begginingofa;
      a[1] = '\0';
    }
  else if (*(pointertox - 1) == ')')
    {
      int size = n_of_chars_inbetween_parentheses (pointertox - 1, 'l');
      // pointer to the first char after the opening parentheses of a
      begginingofa = pointertox - 1 - size;
      strncpy (a, begginingofa, size);
      a[size] = '\0';
      printf ("%s\n", a);
    }
  if (*(pointertox + 1) >= 'A' && *(pointertox + 1) <= 'E')
    {
      endofb = pointertox + 1;
      b[0] = *(pointertox + 1);
      b[1] = '\0';
    }
  else if (*(pointertox + 1) == '(')
    {
      int size = n_of_chars_inbetween_parentheses (pointertox + 1, 'r');
      b[size] = '\0';
      strncpy (b, pointertox + 2, size);
      printf ("Size:%d b:%s\n", size, b);
      // pointer to the last char before the closing parentheses of b
      endofb = pointertox + 1 + size;
    }

  char *newstring = calloc (strlen (syntax) * 3, sizeof (char));
  strncpy (newstring, syntax, begginingofa - 1 - syntax);
  strcat (newstring, "((");
  strcat (newstring, a);
  strcat (newstring, ")!(");
  strcat (newstring, b);
  strcat (newstring, ")+!(");
  strcat (newstring, a);
  strcat (newstring, ")(");
  strcat (newstring, b);
  strcat (newstring, "))");
  strcat (newstring, endofb + 2);
  return newstring;
}

int
n_of_chars_inbetween_parentheses (char *entrypoint, char direction)
{
  char signtoincrease = direction == 'r' ? '(' : ')';
  char signtodecrease = direction == 'r' ? ')' : '(';
  int parentheses_count = 1;
  char *end = NULL;
  int counter = 0;
  char *current = direction == 'r' ? entrypoint + 1 : entrypoint - 1;
  while (parentheses_count != 0)
    {
      if (*current == signtoincrease)
        parentheses_count++;
      else if (*current == signtodecrease)
        parentheses_count--;
      counter++;
      current = direction == 'r' ? current + 1 : current - 1;
    }
  return counter - 1;
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