#include "boolgen_utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool f(char syntax[], bool values[])
{
    bool sum_acc = false;    // Identity element of the monoid (Bool, ||)
    bool product_acc = true; // Identity element of the monoid (Bool, &&)
    bool notflag = false;
    for (char *i = syntax; i != syntax + strlen(syntax) + 1; i++)
    {
        if (*i >= 'A' && *i <= 'E')
            product_acc = product_acc && values[*i - 'A'];
        else if (*i == '+')
        {
            sum_acc = sum_acc || product_acc;
            product_acc = true; // Reverts to the identity element
        }
        else if (*i == '(')
        {
            int size = n_of_chars_inbetween_parentheses(i, 'r');
            char *subsyntax = calloc(strlen(syntax), sizeof(char));
            // Copies the content in between parentheses
            strncpy(subsyntax, i + 1, size);
            bool result = f(subsyntax, values);
            if (notflag)
                result = !result;
            product_acc = product_acc && result;
            i = i + 1 + size;
            notflag = false;
            free(subsyntax);
        }
        else if (*i == '!')
            notflag = true;
    }
    sum_acc = sum_acc || product_acc;
    return sum_acc;
}

char *xorfilter(char *syntax)
{
    char a[strlen(syntax)];
    char b[strlen(syntax)];
    char *pointertox = strchr(syntax, 'x');
    char *newstring = calloc(256, sizeof(char));
    char *begginingofa = NULL;
    char *endofb = NULL;
    char *wheretowrite;
    int diff;

    if (*(pointertox - 1) >= 'A' && *(pointertox - 1) <= 'E')
    {
        begginingofa = pointertox - 1;
        a[0] = *begginingofa;
        a[1] = '\0';
    }
    else if (*(pointertox - 1) == ')')
    {
        int size = n_of_chars_inbetween_parentheses(pointertox - 1, 'l');
        // * pointer to the opening parentheses of a
        begginingofa = pointertox - 1 - size - 1;
        strncpy(a, begginingofa + 1, size);
        a[size] = '\0';
    }
    if (*(pointertox + 1) >= 'A' && *(pointertox + 1) <= 'E')
    {
        endofb = pointertox + 1;
        b[0] = *(pointertox + 1);
        b[1] = '\0';
    }
    else if (*(pointertox + 1) == '(')
    {
        int size = n_of_chars_inbetween_parentheses(pointertox + 1, 'r');
        // * pointer to the closing parentheses of b
        endofb = pointertox + 1 + size + 1;
        strncpy(b, pointertox + 2, size);
        b[size] = '\0';
    }

    diff = begginingofa - syntax;
    // Copy string until the point in which we will substitute a
    strncpy(newstring, syntax, diff);
    wheretowrite = newstring + diff;
    snprintf(wheretowrite, (255 - diff), "((%s)!(%s)+!(%s)(%s))%s", a, b, a, b, endofb + 1);
    return newstring;
}

int n_of_chars_inbetween_parentheses(char *entrypoint, char direction)
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

int varcount(char syntax[])
{
    long acc = 1;
    int counter = 0;

    for (int i = 0; i < strlen(syntax); i++)
    {
        if (syntax[i] >= 'A' && syntax[i] <= 'E' && acc % syntax[i] != 0)
        {
            acc = acc * syntax[i];
            counter++;
        }
    }

    return counter;
}