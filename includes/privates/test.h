/*! \file Test.h
	\author Maxime RIVIERE
  \author Fabien Arcellier
*/

#ifndef INCLUDE_TEST_H
#define INCLUDE_TEST_H

#include <stdlib.h>
#include <stdio.h>

/* Macro-Programmation : Permet de definir l'entete d'une methode de test
 */
#define TEST_TITLE(X) \
  fprintf(stdout,"\r\n");\
  fprintf(stdout, "%s - %s (%d)\r\n", X, __FILE__, __LINE__);

/*Macro-Programmation : TEST(X) sert à remplacer les ASSERT dans le code.
  Fonctionnement identique que les ASSERT sans les exit.
 */
#define TEST(X)\
  if(X)\
  {\
    fprintf(stdout,"\t%s\tSuccess\r\n", #X);\
  }\
  else\
    fprintf(stdout,"\t%s\tFailed\r\n", #X);

#endif
