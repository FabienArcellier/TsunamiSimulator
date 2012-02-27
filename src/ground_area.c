#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"

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
	ground_area_init_area (*ground_area);
  
}

/*!
 * \brief Initialise l'objet avec des valeurs par defaut
 */
void ground_area_init_area (PtrGroundArea ground_area)
{
	assert (ground_area != NULL);
	
	int i = 0, j = 0, k = 0;
	int array_width = ground_area -> array_width;
  int array_length = ground_area -> array_length;
	int size = ground_area -> array_length * ground_area -> array_width;
	
  for (i = 0; i < size; i++)
  {
    PtrGround ground = &((ground_area -> area)[i]);
    ground_init (ground);
		ground_set_position_X (ground, (i % array_width) * GROUND_WIDTH);
		ground_set_position_Y (ground, (i / array_width) * GROUND_LENGTH);
		ground_set_width (ground, GROUND_WIDTH);
		ground_set_length (ground, GROUND_LENGTH);
  }
  
  for (i = 0; i < array_width; i++)
	{
		for (j = 0; j < array_length; j++)
		{
			// Parcours les 10 cases autour d'une zone
			// Pour chacune, sauf la centrale (k = 4), on recupere le
			// voisin.
			for (k = 0; k < 9; k++)
			{
				PtrGround ground = ground_area_get_ground (ground_area, i, j);
				int array_position_x = (i - 1) + k % 3;
				int array_position_y = (j - 1) + (int) k / 3;
				
				if (k != 4 &&
					array_position_x >= 0 &&
					array_position_y >= 0 &&
					array_position_x < array_width &&
					array_position_y < array_length)
				{
					PtrGround ground_neighbour = ground_area_get_ground (ground_area, array_position_x, array_position_y);
					ground_insert_ground_neighbour (ground, ground_neighbour);
				}
			}
		}
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

/*!
 * \brief Assesseur en lecture de l'attribut array_width
 */
int ground_area_get_array_width (PtrGroundArea ground_area)
{
	assert (ground_area != NULL);
	return ground_area -> array_width;
}

/*!
 * \brief Assesseur en lecture de l'attribut 
 */
int ground_area_get_array_length (PtrGroundArea ground_area)
{
	assert (ground_area != NULL);
	return ground_area -> array_length;
}

