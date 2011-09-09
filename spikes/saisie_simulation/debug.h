
/* Macro qui affiche la valeur d'une variable si une expression == 1
 * FORMAT : %lld : entier long long
 *          %d : entier int
 *          %f: flottant
 *          %s: chaine de caracteres
 * */

#include <string.h>
#include <stdio.h>

#ifndef NDEBUG

#define DEBUG_IF(EXPRESSION, FORMAT, VARIABLE) \
if (EXPRESSION)\
{\
  char format[20];\
  strcpy(format, "D: %s = ");\
  strcat(format, FORMAT);\
  printf(format,#VARIABLE, VARIABLE);\
  puts("");\
}

#endif

#ifdef NDEBUG

#define DEBUG_IF(EXPRESSION, FORMAT, VARIABLE)

#endif