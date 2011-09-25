#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_map_navigator.h"
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
 * \brief Assesseur en ecriture de ground_area_energy_map_navigator
 */
void simulation_set_energy_map_navigator (PtrSimulation simulation, 
																					PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator)
{
	assert (simulation != NULL);
	simulation -> ground_area_energy_map_navigator = ground_area_energy_map_navigator;
}

/*!
 * \brief Assesseur en lecture de ground_area_energy_map_navigator
 */
PtrGroundAreaEnergyMapNavigator simulation_get_energy_map_navigator (PtrSimulation simulation)
{
	assert (simulation != NULL);
	return simulation -> ground_area_energy_map_navigator;
}
