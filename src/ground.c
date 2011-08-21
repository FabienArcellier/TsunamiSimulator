#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ground.h"

/*!
 * \brief Cree un terrain de 100m par 100m
 */
void ground_create (PtrGround *ground)
{
  assert (*ground == NULL);
  *ground = (PtrGround) malloc (sizeof (Ground));
  memset (*ground, 0, sizeof (Ground));
  
  *ground = ground_init (*ground);
}

/*!
 * \brief Initialise un espace memoire deja reserve
 */
PtrGround ground_init (PtrGround ground)
{
  assert (ground != NULL);
  
  ground -> type = ground_type_water;
  ground -> width = 100;
  ground -> length = 100;
  ground -> height = 0.0;
  ground -> dawning = 0.99;
  
  return ground;
}

/*!
 * \brief Detruit une instance de terrain
 */
void ground_destroy (PtrGround *ground)
{
  assert (*ground != NULL);
  
  free (*ground);
  *ground = NULL;
}

/*!
 * \brief Configure le type d'un terrain
 */
void ground_set_type (PtrGround ground, enum GROUND_TYPE ground_type)
{
  assert (ground != NULL);
  
  ground -> type = ground_type; 
}

/*!
 * \brief Obtient le type d'un terrain
 */
enum GROUND_TYPE ground_get_type (PtrGround ground)
{
  assert (ground != NULL);
  
  return ground -> type;
}

/*!
 * \brief Fixe la hauteur d'un terrain
 */
void ground_set_height (PtrGround ground, double height)
{
  assert (ground != NULL);
  ground -> height = height;
  
}

/*!
 * \brief Retourne la hauteur d'un terrain
 */
double ground_get_height (PtrGround ground)
{
  return ground -> height;
}

/*!
 * \brief Fixe l'absorbtion energétique du terrain (entre 0 et 1)
 */
void ground_set_dawning (PtrGround ground, double dawning)
{
  assert (ground != NULL);
  assert (dawning >= 0.0 && dawning <= 1.0);
  
  ground -> dawning = dawning;
}

/*!
 * \brief Retourne le coefficient d'absorbtion du terrain
 */
double ground_get_dawning (PtrGround ground)
{
  return ground -> dawning;
}


