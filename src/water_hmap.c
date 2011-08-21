#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "water_hmap.h"

/*!
 * \brief retourne l'indice d'un element du tableau a partir des coordonnees cartesiennes
 */ 
static int water_hmap_get_map_index (PtrWaterHmap, int x, int y);

/*!
 * \brief cree une instance PtrWaterHmap
 */
void water_hmap_create (PtrWaterHmap* water_hmap, int width, int height)
{
  assert (*water_hmap == NULL);
  
  int map_size = width * height;
  
  *water_hmap = (PtrWaterHmap) malloc (sizeof (WaterHmap));
  if (*water_hmap == NULL)
  {
    abort();
  }
  
  memset(*water_hmap, 0, sizeof (WaterHmap));
  
  (*water_hmap) -> width = width;
  (*water_hmap) -> height = height;  
  (*water_hmap) -> map = (int*) malloc (map_size * sizeof (int));
  memset ((*water_hmap) -> map, 0, map_size * sizeof (int));
  
  assert (*water_hmap != NULL);
  assert ((*water_hmap) -> map != NULL);
}

/*!
 * \brief desalloue la memoire
 */
void water_hmap_destroy (PtrWaterHmap* water_hmap)
{
  assert (*water_hmap != NULL);
  assert ((*water_hmap) -> map != NULL);
  
  free ((*water_hmap) -> map);
  free (*water_hmap);
  *water_hmap = NULL;
  
  assert (*water_hmap == NULL);
}

/*!
 * \brief retourne la valeur d'un element selon ses coordonnes x et y
 */ 
int water_hmap_get_water_height (PtrWaterHmap water_hmap, int x, int y)
{
  
  assert (water_hmap != NULL);
  assert (water_hmap -> map != NULL);
  assert (x < water_hmap -> width && x >= 0);
  assert (y < water_hmap -> height && y >= 0);
  
  int water_hmap_index = water_hmap_get_map_index (water_hmap, x, y);
  int water_height = water_hmap -> map[water_hmap_index];
  
  return water_height;
}

/*!
 * \brief modifie la valeur d'un element selon ses coordonnes x et y
 */ 
void water_hmap_set_water_height (PtrWaterHmap water_hmap, int x, int y, int water_height)
{
  assert (water_hmap != NULL);
  assert (water_hmap -> map != NULL);
  assert (x < water_hmap -> width && x >= 0);
  assert (y < water_hmap -> height && y >= 0);
  
  int water_hmap_index = water_hmap_get_map_index (water_hmap, x, y);
  water_hmap -> map[water_hmap_index] = water_height;
}

/*!
 * \brief retourne l'indice d'un element du tableau a partir des coordonnees cartesiennes
 */ 
static int water_hmap_get_map_index (PtrWaterHmap water_hmap, int x, int y)
{
  assert (water_hmap != NULL);
  assert (x < water_hmap -> width && x >= 0);
  assert (y < water_hmap -> height && y >= 0);
  
  int water_hmap_index = y * water_hmap -> width + x;

  return water_hmap_index;
}