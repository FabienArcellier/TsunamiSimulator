#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_map_navigator.h"

/*!
 * \brief Instancie un navigateur pour des energy maps
 */
void ground_area_energy_map_navigator_create (PtrGroundAreaEnergyMapNavigator *ground_area_energy_map_navigator)
{
	assert (*ground_area_energy_map_navigator == NULL);
	
	*ground_area_energy_map_navigator = (PtrGroundAreaEnergyMapNavigator) malloc (sizeof (GroundAreaEnergyMapNavigator));
	memset (*ground_area_energy_map_navigator, 0, sizeof (GroundAreaEnergyMapNavigator));
}

/*!
 * \brief Detruit un navigateur d'energy map
 */
void ground_area_energy_map_navigator_destroy (PtrGroundAreaEnergyMapNavigator *ground_area_energy_map_navigator)
{
	assert (*ground_area_energy_map_navigator != NULL);
	
	if ((*ground_area_energy_map_navigator) -> first != NULL)
	{
		PtrGroundAreaEnergyMap first = (*ground_area_energy_map_navigator) -> first;
		ground_area_energy_map_destroy (&first);
	}
	
	free (*ground_area_energy_map_navigator);
	*ground_area_energy_map_navigator = NULL;
}

/*!
 * \brief Ajoute une energy map a la fin de la liste existante
 */
void ground_area_energy_map_navigator_add (PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator, 
																					 PtrGroundAreaEnergyMap ground_area_energy_map)
{
	assert (ground_area_energy_map_navigator != NULL);
	assert (ground_area_energy_map != NULL);
	
	int count = ground_area_energy_map_navigator -> count;
	
	if (ground_area_energy_map_navigator -> first == NULL)
	{
		ground_area_energy_map_navigator -> current = ground_area_energy_map;
		ground_area_energy_map_navigator -> first = ground_area_energy_map;
		ground_area_energy_map_navigator -> count = count + 1;
	}
	else
	{
		PtrGroundAreaEnergyMap current = ground_area_energy_map_navigator -> first;
		PtrGroundAreaEnergyMap next = ground_area_energy_map_get_next (current);
		while (next != NULL)
		{
			current = next;
			next = ground_area_energy_map_get_next (next);
		}
		
		ground_area_energy_map_set_next (current, ground_area_energy_map);
		ground_area_energy_map_set_previous (ground_area_energy_map, current);
		ground_area_energy_map_navigator -> count = count + 1;
	}
}

/*!
 * \brief Supprime une energy map de la liste existante
 */
void ground_area_energy_map_navigator_delete (PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator,
																							PtrGroundAreaEnergyMap ground_area_energy_map)
{
	assert (ground_area_energy_map_navigator != NULL);
	assert (ground_area_energy_map != NULL);
	
	int count = ground_area_energy_map_navigator -> count;
	
	if (ground_area_energy_map_navigator -> first == NULL)
	{
		fprintf (stderr, "You try to delete an element ground_area_energy map that does not exist");
		return;
	}
	else
	{
		PtrGroundAreaEnergyMap current = ground_area_energy_map_navigator -> first;
		PtrGroundAreaEnergyMap next = ground_area_energy_map_get_next (current);
		while (current != ground_area_energy_map && next != NULL)
		{
			current = next;
			next = ground_area_energy_map_get_next (next);
		}
		
		if (current == ground_area_energy_map)
		{
			PtrGroundAreaEnergyMap previous = ground_area_energy_map_get_previous (current);
			if (previous == NULL)
			{
				if (next != NULL)
				{
					ground_area_energy_map_set_previous (next, NULL);
				}
				ground_area_energy_map_navigator -> first = next;
				ground_area_energy_map_navigator -> current = next;
				ground_area_energy_map_navigator -> count = count - 1;
			}
			else
			{
				ground_area_energy_map_set_next (previous, next);
				ground_area_energy_map_navigator -> count = count - 1;
			}
			
			ground_area_energy_map_set_next (current, NULL);
		}
		else
		{
			fprintf (stderr, "You try to delete an element ground_area_energy map that does not exist\n");
			return;
		}
	}
	
}

/*!
 * \brief Deplace le curseur courant a l'energy map d'apres
 * 
 * retourne 1 si le deplacement est un succes, 0 autrement
 */
int ground_area_energy_map_navigator_move_next (PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator)
{
	assert (ground_area_energy_map_navigator != NULL);
	
	PtrGroundAreaEnergyMap next = ground_area_energy_map_get_next (ground_area_energy_map_navigator -> current);
	
	if (next != NULL)
	{
		ground_area_energy_map_navigator -> current = next;
		ground_area_energy_map_navigator -> current_position = ground_area_energy_map_navigator -> current_position + 1;
		return 1;
	}
	else
	{
		return 0;
	}
	
}

/*!
 * \brief Deplace le curseur courant a l'energy map d'avant
 * 
 *  retourne 1 si le deplacement est un succes, 0 autrement
 */
int ground_area_energy_map_navigator_move_previous (PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator)
{
	assert (ground_area_energy_map_navigator != NULL);
	
	PtrGroundAreaEnergyMap previous = ground_area_energy_map_get_previous (ground_area_energy_map_navigator -> current);
	
	if (previous != NULL)
	{
		ground_area_energy_map_navigator -> current = previous;
		ground_area_energy_map_navigator -> current_position = ground_area_energy_map_navigator -> current_position - 1;
		return 1;
	}
	else
	{
		return 0;
	}
}

/*!
 * \brief Deplace le curseur courant a une position donnee
 * 
 *  retourne 1 si le deplacement est un succes, 0 autrement
 */
int ground_area_energy_map_navigator_move_position (PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator,
																										int position)
{
	assert (ground_area_energy_map_navigator != NULL);
	PtrGroundAreaEnergyMap current = ground_area_energy_map_navigator -> first;
	int i = 0;
	
	for (i = 0; i < position; i++)
	{
		if (current == NULL)
		{
			return 0;
		}
		
		current = ground_area_energy_map_get_next (current);
	}
	
	ground_area_energy_map_navigator -> current = current;
	return 1;
}

/*!
 * \brief Retourne le nombre total d'energy map
 */
int ground_area_energy_map_navigator_get_count (PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator)
{
	assert (ground_area_energy_map_navigator != NULL);
	int result = -1;
	
	result = ground_area_energy_map_navigator -> count;
	
	assert (result >= 0);
	return result;
}

/*!
 * \brief Retourne l'energy map courante
 */
PtrGroundAreaEnergyMap ground_area_energy_map_navigator_get_current (PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator)
{
	assert (ground_area_energy_map_navigator != NULL);
	
	return ground_area_energy_map_navigator -> current;
}