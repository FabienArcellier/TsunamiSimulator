#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Inclusion des fichiers h du projet */
#include <pthread.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_map_navigator.h"
#include "event.h"
#include "earthquake_event.h"
#include "earthquake_events_text_storage.h"
#include "timeline.h"
#include "propagation_timeline_processings.h"
#include "simulation.h"
#include "calculate_worker.h"
#include "calculate_worker_private.h"

/* Methodes du composant */

/*!
 * \brief Cree une instance de type CalculateWorker
 */
void calculate_worker_create (PtrCalculateWorker *calculate_worker, PtrSimulation simulation)
{
	assert (*calculate_worker == NULL);
	assert (simulation != NULL);
	
	*calculate_worker = (PtrCalculateWorker) malloc (sizeof (CalculateWorker));
	memset (*calculate_worker, 0, sizeof (CalculateWorker));
	
	(*calculate_worker) -> simulation = simulation;
}

/*!
 * \brief Destruit une instance d'objet CalculateWorker
 */
void calculate_worker_destroy (PtrCalculateWorker *calculate_worker)
{
	assert (*calculate_worker != NULL);
	
	/* Specification programmeur */
	
	free (*calculate_worker);
	*calculate_worker = NULL;
}

/*!
 * \brief Démarre la fonction de calcul
 */
void calculate_worker_start (PtrCalculateWorker calculate_worker)
{
	assert (calculate_worker != NULL);
	assert (calculate_worker -> simulation != NULL);
	
	int result = pthread_create (&(calculate_worker -> pid), NULL, calculate_energy_map, calculate_worker);
	if (result != 0)
	{
		fprintf (stderr, "Instanciation of calculate_worker thread fails\n");
		exit (EXIT_FAILURE);
	}
	
	result = pthread_detach (calculate_worker -> pid);
	if (result != 0)
	{
		fprintf (stderr, "Instanciation of calculate_worker thread fails\n");
		exit (EXIT_FAILURE);
	}
	
	calculate_worker -> state = calculate_worker_state_in_progress;
}

/*!
 * \brief Demande au worker d'interrompre son fonctionnement
 */
void calculate_worker_cancel (PtrCalculateWorker calculate_worker)
{
	assert (calculate_worker != NULL);
	calculate_worker -> cancel_requested = 1;
}

/*!
 * \brief Methode dynamique qui realise le travail
 */
void *calculate_energy_map (void *data)
{
	PtrCalculateWorker calculate_worker = (PtrCalculateWorker) data;
	
	assert (calculate_worker != NULL);
	assert (calculate_worker -> simulation != NULL);
	
	PtrSimulation simulation = calculate_worker -> simulation;
	
	PtrTimeline timeline = simulation_get_timeline (simulation);
	PtrGroundArea ground_area = simulation_get_ground_area (simulation);
	PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator = simulation_get_energy_map_navigator (simulation);
	
	int final_time = timeline_get_final_time (timeline);
	int i = 0;
	
	while (timeline_get_current_time (timeline) <= final_time && calculate_worker -> cancel_requested != 1)
	{
		register_events_for_propagation_on_timeline_from_ground_area (timeline,
																																	ground_area);
		timeline_execute_events (timeline);
		simplify_wave_signals_after_propagation_on_ground_area (ground_area);
		
		PtrGroundAreaEnergyMap ground_area_energy_map = NULL;
		ground_area_energy_map_create (&ground_area_energy_map, ground_area);
		ground_area_energy_map_navigator_add (ground_area_energy_map_navigator, ground_area_energy_map);
		i++;
		
		if (timeline_get_current_time (timeline) < final_time)
		{
			timeline_move_current_time (timeline, 1);
		}
		else
		{
			break;
		}
	}
	
	if (calculate_worker -> cancel_requested)
	{
		int count = ground_area_energy_map_navigator_get_count (ground_area_energy_map_navigator);
		int i = 0;
		for (i = 0; i < count; i++)
		{
			PtrGroundAreaEnergyMap energy_map_to_destroy = ground_area_energy_map_navigator_get_current (ground_area_energy_map_navigator);
			ground_area_energy_map_navigator_delete (ground_area_energy_map_navigator, energy_map_to_destroy);
			ground_area_energy_map_destroy (&energy_map_to_destroy);
		}
		
		calculate_worker -> state = calculate_worker_state_canceled;
		simulation_set_simulation_calculated (simulation, 0);
	}
	else
	{
		calculate_worker -> state = calculate_worker_state_done;
		simulation_set_simulation_calculated (simulation, 1);
	}
	
	return NULL;
}

/*!
 * \brief Assesseur en ecriture de l'attribut simulation
 */
void calculate_worker_set_simulation (PtrCalculateWorker calculate_worker, PtrSimulation simulation)
{
	assert (calculate_worker != NULL);
	calculate_worker -> simulation = simulation;
}

/*!
 * \brief Assesseur en lecture de l'attribut simulation
 */
PtrSimulation calculate_worker_get_simulation (PtrCalculateWorker calculate_worker)
{
	assert (calculate_worker != NULL);
	return calculate_worker -> simulation;
}

/*!
 * \brief Assesseur en ecriture de l'attribut state
 */
void calculate_worker_set_state (PtrCalculateWorker calculate_worker, enum CalculateWorkerState state)
{
	assert (calculate_worker != NULL);
	calculate_worker -> state = state;
}

/*!
 * \brief Assesseur en lecture de l'attribut state
 */
enum CalculateWorkerState calculate_worker_get_state (PtrCalculateWorker calculate_worker)
{
	assert (calculate_worker != NULL);
	return calculate_worker -> state;
}