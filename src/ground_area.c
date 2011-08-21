#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ground.h"
#include "ground_area.h"

/*!
 * \brief Cree un objet Ground Area qui contient un terrain (width en m, length en m)
 */
void ground_area_create (PtrGroundArea *ground_area , int width, int length)
{
  assert (*ground_area == NULL);
  assert (width > GROUND_WIDTH);
  assert (length > GROUND_LENGTH);
  
  int array_width = (int) (width / GROUND_WIDTH);
  int array_length = (int) (length / GROUND_LENGTH);
  int size = array_length * array_width;
  
  *ground_area = (PtrGroundArea) malloc (sizeof (GroundArea));
  if (*ground_area == NULL)
  {
    abort();
  }
  
  memset (*ground_area, 0, sizeof (GroundArea));
  (*ground_area) -> width = width;
  (*ground_area) -> length = length;
  (*ground_area) -> array_width = array_width;
  (*ground_area) -> array_length = array_length;
  
  (*ground_area) -> area = (PtrGround) malloc (sizeof (Ground) * size);
  if ((*ground_area) -> area == NULL)
  {
    abort();
  }
  
  memset ((*ground_area) -> area, 0, sizeof (Ground) * size);
  int i = 0;
  for (i = 0; i < size; i++)
  {
    PtrGround ground = &((*ground_area) -> area[i]);
    ground_init (ground);
  }
}

/*!
 * \brief Destruit un objet Ground Area
 */
void ground_area_destroy (PtrGroundArea *ground_area)
{
  assert (*ground_area != NULL);
  
  free (*ground_area);
  *ground_area = NULL;
}

/*!
 * \brief Retourne l'objet PtrGround pour les coordonnées données (indice)
 */
PtrGround ground_area_get_ground (PtrGroundArea ground_area, int x, int y)
{
  assert (ground_area != NULL);
  assert (x >= 0);
  assert (y >= 0);
  assert (x < ground_area -> array_width);
  assert (y < ground_area -> array_length);
  
  int array_position = y * ground_area -> array_width + x;
  
  return &(ground_area -> area[array_position]);
}

