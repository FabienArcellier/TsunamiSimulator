#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "event.h"
#include "timeline.h"
#include "simulation.h"

/*!
 * \brief Cree une instance de type Simulation
 */
void simulation_create (PtrSimulation *simulation)
{
	assert (*simulation == NULL);
	
	*simulation = (PtrSimulation) malloc (sizeof (Simulation));
	if (*simulation == NULL)
	{
		fprintf (stderr, "Erreur d'allocation de simulation_create\n");
		abort ();
	}
	
	memset (*simulation, 0, sizeof (Simulation));
}

/*!
 * \brief Detruit une instance de type Simulation
 */
void simulation_destroy (PtrSimulation *simulation)
{
	assert (*simulation != NULL);
	
	if ((*simulation) -> timeline != NULL)
	{
		PtrTimeline timeline = (*simulation) -> timeline;
		timeline_destroy(&timeline);
	}
	
	if ((*simulation) -> ground_area != NULL)
	{
		PtrGroundArea ground_area = (*simulation) -> ground_area;
		ground_area_destroy (&ground_area);
	}
	
	if ((*simulation) -> file_ground_area_energy_map != NULL)
	{
		PtrGroundAreaEnergyMap file_ground_area_energy_map = (*simulation) -> file_ground_area_energy_map;
		ground_area_energy_map_destroy (&file_ground_area_energy_map);
	}
	
	free (*simulation);
	*simulation = NULL;
}

/*!
 * \brief Assesseur en ecriture de timeline
 */
void simulation_set_timeline (PtrSimulation simulation, PtrTimeline timeline)
{
	assert (simulation != NULL);
	simulation -> timeline = timeline;
}

/*!
 * \brief Assesseur en lecture de timeline
 */
PtrTimeline simulation_get_timeline (PtrSimulation simulation)
{
	assert (simulation != NULL);
	return simulation -> timeline;
}

/*!
 * \brief Assesseur en ecriture de ground_area
 */
void simulation_set_ground_area (PtrSimulation simulation, PtrGroundArea ground_area)
{
	assert (simulation != NULL);
	simulation -> ground_area = ground_area;
}

/*!
 * \brief Assesseur en lecture de ground_area
 */
PtrGroundArea simulation_get_ground_area (PtrSimulation simulation)
{
	assert (simulation != NULL);
	return simulation -> ground_area;
}

/*!
 * \brief Assesseur en ecriture de file_ground_area_energy_map
 */
void simulation_set_push_energy_map (PtrSimulation simulation, PtrGroundAreaEnergyMap ground_area_energy_map)
{
	assert (simulation != NULL);
	assert (ground_area_energy_map != NULL);
	ground_area_energy_map_push (&(simulation -> file_ground_area_energy_map), ground_area_energy_map);
}

/*!
 * \brief Assesseur en lecture de file_ground_area_energy_map
 */
PtrGroundAreaEnergyMap simulation_set_pop_energy_map (PtrSimulation simulation)
{
	assert (simulation != NULL);
	assert (simulation -> file_ground_area_energy_map != NULL);
	return ground_area_energy_map_pop (&(simulation -> file_ground_area_energy_map));
}

/*!
 * \brief Retourne 1 si l'energie map est vide
 */
int simulation_energy_map_empty (PtrSimulation simulation)
{
	assert (simulation != NULL);
	return ground_area_energy_map_empty (simulation -> file_ground_area_energy_map);
}
