#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"

/*!
 * \brief Cree une instance de type GroundAreaEnergyMap
 */
void ground_area_energy_map_create (PtrGroundAreaEnergyMap *ground_area_energy_map, PtrGroundArea ground_area)
{
	assert (*ground_area_energy_map == NULL);
	assert (ground_area != NULL);
	
	*ground_area_energy_map = (PtrGroundAreaEnergyMap) malloc (sizeof (GroundAreaEnergyMap));
	memset (*ground_area_energy_map, 0, sizeof (GroundAreaEnergyMap));
	
	int size =  ground_area -> array_width * ground_area -> array_length;
	
	(*ground_area_energy_map) -> array_width = ground_area -> array_width;
	(*ground_area_energy_map) -> array_length = ground_area -> array_length;
	
	(*ground_area_energy_map) -> map = (double*) malloc (sizeof (double) * size);
	memset ((*ground_area_energy_map) -> map, 0, sizeof (double) * size);
	
	ground_area_energy_map_calculate (*ground_area_energy_map, ground_area);
}

/*!
 * \brief Detruit une instance de type GroundAreaEnergyMap et tous ces enfants
 */
void ground_area_energy_map_destroy (PtrGroundAreaEnergyMap *ground_area_energy_map)
{
	assert ((*ground_area_energy_map) != NULL);
	assert ((*ground_area_energy_map) -> map != NULL);
	
	if ((*ground_area_energy_map) -> next != NULL)
	{
		ground_area_energy_map_destroy (&((*ground_area_energy_map) -> next));
	}
	
	free ((*ground_area_energy_map) -> map);
	free (*ground_area_energy_map);
	*ground_area_energy_map = NULL;
}

/*!
 * \brief Calcule la carte d'energie d'une ground area
 * 
 * Attention, vous devez utiliser une instance de ground_area ayant la meme array_width et
 * array_length qu'à la création de PtrGroundAreaEnergyMap
 */
void ground_area_energy_map_calculate (PtrGroundAreaEnergyMap ground_area_energy_map, PtrGroundArea ground_area)
{
	assert (ground_area_energy_map != NULL);
	assert (ground_area != NULL);
	assert (ground_area_energy_map -> array_width == ground_area -> array_width);
	assert (ground_area_energy_map -> array_length == ground_area -> array_length);
	
	int array_width = ground_area -> array_width;
	int array_length = ground_area -> array_length;
	
	int i = 0, j = 0;
	for (i = 0; i < array_width; i++)
	{
		for (j = 0; j < array_length; j++)
		{
			PtrGround ground = ground_area_get_ground (ground_area, i, j);
			PtrWaveSignal list_wave_signal = ground_get_wave_signals (ground);
			double energy = 0;
			while (list_wave_signal != NULL)
			{
				energy += wave_signal_get_energy (list_wave_signal);
				list_wave_signal = wave_signal_get_next_wave_signal (list_wave_signal);
			}
			
			int indice = i + array_width * j;
			ground_area_energy_map -> map [indice] = energy;
		}
	}
}

/*!
 * \brief Empile une instance de type PtrGroundAreaEnergyMap
 */
void ground_area_energy_map_push (PtrGroundAreaEnergyMap *ground_area_energy_map, PtrGroundAreaEnergyMap ground_area_energy_map_to_push)
{
	assert (ground_area_energy_map_to_push != NULL);
	assert (ground_area_energy_map_to_push -> next == NULL);
	PtrGroundAreaEnergyMap previous = NULL;
	PtrGroundAreaEnergyMap current = NULL;
	
	if (*ground_area_energy_map == NULL)
	{
		*ground_area_energy_map = ground_area_energy_map_to_push;
	}
	else
	{
		previous = *ground_area_energy_map;
		current = (*ground_area_energy_map) -> next;
		while (current != NULL)
		{
			previous = current;
			current = current -> next;
		} 
		
		previous -> next = ground_area_energy_map_to_push;
	}
}

/*!
 * \brief Depile une instance de type PtrGroundAreaEnergyMap
 */
PtrGroundAreaEnergyMap ground_area_energy_map_pop (PtrGroundAreaEnergyMap *ground_area_energy_map)
{
	assert (*ground_area_energy_map != NULL);
	
	PtrGroundAreaEnergyMap energy_map_unstacked = *ground_area_energy_map;
	*ground_area_energy_map = (*ground_area_energy_map) -> next;
	energy_map_unstacked -> next = NULL;
	
	return energy_map_unstacked;
}

/*!
 * \brief Retourne 1 si il n y a aucune energie map
 */
int ground_area_energy_map_empty (PtrGroundAreaEnergyMap ground_area_energy_map)
{
	return ground_area_energy_map == NULL;
}

/*!
 * \brief Assesseur en lecture de array_width
 */
int ground_area_energy_map_get_array_width (PtrGroundAreaEnergyMap ground_area_energy_map)
{
	assert (ground_area_energy_map != NULL);
	
	return ground_area_energy_map -> array_width;
}

/*!
 * \brief Assesseur en lecture de array_length
 */
int ground_area_energy_map_get_array_length (PtrGroundAreaEnergyMap ground_area_energy_map)
{
	assert (ground_area_energy_map != NULL);
	
	return ground_area_energy_map -> array_length;
}

/*!
 * \brief Renvoie la quantite d'energie presente sur une case
 */
double ground_area_energy_map_get_energy (PtrGroundAreaEnergyMap ground_area_energy_map, int positionX, int positionY)
{
	assert (ground_area_energy_map != NULL);
	assert (positionX < ground_area_energy_map -> array_width);
	assert (positionY < ground_area_energy_map -> array_length);
	
	int indice = positionX + positionY * ground_area_energy_map -> array_width;
	return ground_area_energy_map -> map[indice];
}