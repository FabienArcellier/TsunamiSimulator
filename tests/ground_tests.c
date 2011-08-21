#include "test.h"
#include "ground.h"

/* Prototypes des fonctions de test*/
void ground_create_destroy_test ();
void ground_configure_ground ();

int main (void)
{
  ground_create_destroy_test ();
  ground_configure_ground ();
  
  return 0;
}

/*!
 * \brief teste la creation d'un objet
 */
void ground_create_destroy_test ()
{
  TEST_TITLE ("ground_create_destroy_test");
  PtrGround ground = NULL;
  ground_create (&ground);
  
  TEST (ground -> height == 0.0);
  
  ground_destroy (&ground);
  
  TEST (ground == NULL);
  
}

/*!
 * \brief Teste de la configuration d'un terrain
 */
void ground_configure_ground ()
{
  TEST_TITLE ("ground_configure_tests");
  
  PtrGround ground = NULL;
  ground_create (&ground);
  ground_set_type (ground, water);
  ground_set_height (ground, -120);
  ground_set_dawning (ground, 0.2);
  
  TEST (ground -> type == water);
  TEST (ground -> height == -120);
  TEST (ground -> dawning == 0.2);
  
  ground_destroy (&ground);
}

