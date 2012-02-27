#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wave_signal.h"
#include "debug.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_text_storage.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_map_navigator.h"
#include "ground_area_energy_text_storage.h"
#include "event.h"
#include "earthquake_event.h"
#include "earthquake_events_text_storage.h"
#include "timeline.h"
#include "simulation.h"
#include "simulation_text_storage.h"

/*!
 * \brief Cree une instance de l'objet GroundAreaSimuStorage
 */
void simulation_text_storage_create (PtrSimulationTextStorage *simulation_text_storage)
{
	assert (*simulation_text_storage == NULL);
	
	*simulation_text_storage = (PtrSimulationTextStorage) malloc (sizeof (SimulationTextStorage));
	memset (*simulation_text_storage, 0, sizeof (SimulationTextStorage));
}

/*!
 * \brief Detruit l'instance d'un objet GroundAreaSimuStorage
 */
void simulation_text_storage_destroy (PtrSimulationTextStorage *simulation_text_storage)
{
	assert (*simulation_text_storage != NULL);
	free (*simulation_text_storage);
	*simulation_text_storage = NULL;
}

/*!
 * \brief Assesseur en ecriture de file
 */
void simulation_text_storage_set_file (PtrSimulationTextStorage simulation_text_storage, FILE *file)
{
	assert (simulation_text_storage != NULL);
	simulation_text_storage -> file = file;
}

/*!
 * \brief Assesseur en lecture de file
 */
FILE* simulation_text_storage_get_file (PtrSimulationTextStorage simulation_text_storage)
{
	assert (simulation_text_storage != NULL);
	return simulation_text_storage -> file;
}

/*!
 * \brief Assesseur en ecriture earthquake_events_text_storage
 */
void simulation_text_storage_set_earthquake_events_text_storage (PtrSimulationTextStorage simulation_text_storage, 
																																 PtrEarthquakeEventsTextStorage earthquake_events_text_storage)
{
	assert (simulation_text_storage != NULL);
	simulation_text_storage -> earthquake_events_text_storage = earthquake_events_text_storage;
}

/*!
 * \brief Assesseur en lecture earthquake_events_text_storage
 */
PtrEarthquakeEventsTextStorage simulation_text_storage_get_earthquake_events_text_storage (PtrSimulationTextStorage simulation_text_storage)
{
	assert (simulation_text_storage != NULL);
	return simulation_text_storage -> earthquake_events_text_storage;
}

/*!
 * \brief Assesseur en ecriture ground_area_text_storage
 */
void simulation_text_storage_set_ground_area_text_storage (PtrSimulationTextStorage simulation_text_storage,
																													 PtrGroundAreaTextStorage ground_area_text_storage)
{
	assert (simulation_text_storage != NULL);
	simulation_text_storage -> ground_area_text_storage = ground_area_text_storage;
}

/*!
 * \brief Assesseur en lecture ground_area_text_storage
 */
PtrGroundAreaTextStorage simulation_text_storage_get_ground_area_text_storage (PtrSimulationTextStorage simulation_text_storage)
{
	assert (simulation_text_storage != NULL);
	return simulation_text_storage -> ground_area_text_storage;
}

/*!
 * \brief Assesseur en ecriture de ground_area_energy_text_storage
 */
void simulation_text_storage_set_ground_area_energy_text_storage (PtrSimulationTextStorage simulation_text_storage, 
																																	PtrGroundAreaEnergyTextStorage ground_area_energy_text_storage)
{
	assert (simulation_text_storage != NULL);
	simulation_text_storage -> ground_area_energy_text_storage = ground_area_energy_text_storage;
}

/*!
 * \brief Assesseur en lecture de ground_area_energy_text_storage
 */
PtrGroundAreaEnergyTextStorage simulation_text_storage_get_ground_area_energy_text_storage (PtrSimulationTextStorage simulation_text_storage)
{
	assert (simulation_text_storage != NULL);
	return simulation_text_storage -> ground_area_energy_text_storage;
}

/*!
 * \brief Ecrit un fichier simulation a partir d'un objet simulation
 */
void simulation_text_storage_write_file (PtrSimulationTextStorage simulation_text_storage, 
																				 PtrSimulation simulation)
{
	assert (simulation_text_storage != NULL);
	assert (simulation_text_storage_get_file (simulation_text_storage) != NULL);
// 	assert (simulation_text_storage -> earthquake_events_text_storage != NULL);
// 	assert (simulation_text_storage -> ground_area_text_storage != NULL);
// 	assert (simulation_text_storage -> ground_area_energy_text_storage != NULL);
	assert (simulation != NULL);
	
	FILE* file = simulation_text_storage_get_file (simulation_text_storage);
	
	
	PtrGroundAreaTextStorage ground_area_text_storage = simulation_text_storage -> ground_area_text_storage;
	if (ground_area_text_storage != NULL)
	{
		fprintf (file, "[Terrain]\n");
		ground_area_text_storage_set_file (ground_area_text_storage, file);
		PtrGroundArea ground_area = simulation_get_ground_area (simulation);
		ground_area_text_storage_write_file (ground_area_text_storage, ground_area);
		fprintf (file, "\n");
	}
	
	PtrEarthquakeEventsTextStorage earthquake_events_text_storage = simulation_text_storage -> earthquake_events_text_storage;
	if (earthquake_events_text_storage != NULL)
	{
		PtrTimeline timeline = simulation_get_timeline (simulation);
		PtrEvent events = timeline_get_events (timeline);
		fprintf (file, "[Evenements]\n");
		earthquake_events_text_storage_set_file (earthquake_events_text_storage, file);
		if (events != NULL)
		{
			earthquake_events_text_storage_write_file (earthquake_events_text_storage, events);
		}
		
		fprintf (file, "\n");
	}
	
	/* TODO Implement the write file pour energy map navigator */
	PtrGroundAreaEnergyTextStorage ground_area_energy_text_storage = simulation_text_storage -> ground_area_energy_text_storage;
	if (ground_area_energy_text_storage != NULL)
	{
		fprintf (file, "[Energies]\n");
		ground_area_energy_text_storage_set_file (ground_area_energy_text_storage, file);
		PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator = simulation_get_energy_map_navigator (simulation);
		PtrGroundAreaEnergyMap ground_area_energy_map = ground_area_energy_map_navigator -> first;
		ground_area_energy_text_storage_write_file (ground_area_energy_text_storage, ground_area_energy_map);
	}
}

/*!
 * \brief Lit le fichier et renvoie un objet Simulation
 */
PtrSimulation simulation_text_storage_read_file (PtrSimulationTextStorage simulation_text_storage)
{
	assert (simulation_text_storage != NULL);
	assert (simulation_text_storage_get_file (simulation_text_storage) != NULL);
	
	PtrSimulation simulation = NULL;
	simulation_create (&simulation);
	
	FILE* file = simulation_text_storage_get_file (simulation_text_storage);
	
	char configuration_text[32];
	fgets (configuration_text, 32, file);
	if (strcmp (configuration_text, "[Configuration]\n") != 0)
	{
		fprintf (stderr, "Erreur lecture partie Configuration simulation_text_storage_read_file\n");
		return NULL;
	}
	
	int time_final = 0;
	fscanf (file, "Duree = %d s\n", &time_final);
	DEBUG_IF (0, "%d", time_final);
// 	fgets (poubelle, 255, file);
	fscanf (file, "\n");
	
	PtrTimeline timeline = NULL;
	timeline_create (&timeline);
	timeline_set_final_time (timeline, time_final);
	
	PtrGroundAreaTextStorage ground_area_text_storage = NULL;
	ground_area_text_storage_create (&ground_area_text_storage);
	simulation_text_storage_set_ground_area_text_storage (simulation_text_storage, ground_area_text_storage);
	ground_area_text_storage_set_file (ground_area_text_storage, file);
	
	char terrain_text[32];
	fgets (terrain_text, 32, file);
	if (strcmp (terrain_text, "[Terrain]\n") != 0)
	{
		fprintf (stderr, "Erreur lecture partie Terrain simulation_text_storage_read_file\n");
		return NULL;
	}
	
	PtrGroundArea ground_area = ground_area_text_storage_read_file (ground_area_text_storage);
	simulation_set_ground_area (simulation, ground_area);
	
	fscanf (file, "\n");
	
	PtrEarthquakeEventsTextStorage earthquake_events_text_storage = NULL;
	earthquake_events_text_storage_create (&earthquake_events_text_storage);
	simulation_text_storage_set_earthquake_events_text_storage (simulation_text_storage, earthquake_events_text_storage);
	earthquake_events_text_storage_set_file (earthquake_events_text_storage, file);
	
	char evenements_text[32];
	fgets (evenements_text, 32, file);
	if (strcmp (evenements_text, "[Evenements]\n") != 0)
	{
		fprintf (stderr, "Erreur lecture partie Evenements simulation_text_storage_read_file\n");
		return NULL;
	}
	
	PtrEvent event = earthquake_events_text_storage_read_file (earthquake_events_text_storage, ground_area);
	timeline_set_events (timeline, event);
	simulation_set_timeline (simulation, timeline);
	
	// Partie Optionnel
	PtrGroundAreaEnergyMapNavigator energy_map_navigator = NULL;
	
	char energies_text[32];
	fgets (energies_text, 32, file);
	if (strcmp (energies_text, "[Energies]\n") == 0)
	{
		PtrGroundAreaEnergyTextStorage ground_area_energy_text_storage = NULL;
		PtrGroundAreaEnergyMap ground_area_energy_map = NULL;
		ground_area_energy_text_storage_create (&ground_area_energy_text_storage);
		ground_area_energy_text_storage_set_file (ground_area_energy_text_storage, file);
		ground_area_energy_text_storage_read_file (ground_area_energy_text_storage, ground_area);
	}
	else
	{
		ground_area_energy_map_navigator_create (&energy_map_navigator);
	}
	
	simulation_set_energy_map_navigator (simulation, energy_map_navigator);
	
	return simulation;
}
