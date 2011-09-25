#include "debug.h"
#include "test.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_map_navigator.h"
#include "event.h"
#include "timeline.h"
#include "simulation.h"
#include "calculate_worker.h"

/* Prototypes des fonctions de tests */
void calculate_worker_create_destroy_test ();
void calculate_worker_start_cancel_test ();

int main (void)
{
	calculate_worker_create_destroy_test ();
	calculate_worker_start_cancel_test ();
	return 0;
}

/*!
 * \brief Teste la creation et la destruction d'une instance de type CalculateWorker
 */
void calculate_worker_create_destroy_test ()
{
	TEST_TITLE ("calculate_worker_create_destroy_test");
	PtrCalculateWorker calculate_worker = NULL;
	
	PtrSimulation simulation = NULL;
	simulation_create (&simulation);
	
	calculate_worker_create (&calculate_worker, simulation);
	TEST (calculate_worker != NULL);
	
	calculate_worker_destroy (&calculate_worker);
	TEST (calculate_worker == NULL);
	
	simulation_destroy (&simulation);
}

void calculate_worker_start_cancel_test ()
{
	TEST_TITLE ("calculate_worker_start_cancel_test");
	PtrCalculateWorker calculate_worker = NULL;
	
	PtrTimeline timeline = NULL;
	timeline_create (&timeline);
	timeline_set_final_time (timeline, 60);
	
	PtrGroundArea ground_area = NULL;
	ground_area_create (&ground_area, 10000, 10000);
	
	PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator = NULL;
	ground_area_energy_map_navigator_create (&ground_area_energy_map_navigator);
	
	PtrSimulation simulation = NULL;
	simulation_create (&simulation);
	simulation_set_timeline (simulation, timeline);
	simulation_set_ground_area (simulation, ground_area);
	simulation_set_energy_map_navigator (simulation, ground_area_energy_map_navigator);
	
	calculate_worker_create (&calculate_worker, simulation);
	
	TEST (calculate_worker -> state == calculate_worker_state_inactive);
	calculate_worker_start (calculate_worker);
	long i = 0;
	for (i = 0; i < 500000; i++)
	{
	}
	
	TEST (calculate_worker -> state == calculate_worker_state_in_progress);
	while (calculate_worker -> state == calculate_worker_state_in_progress)
	{
	}
	
	TEST (calculate_worker -> state == calculate_worker_state_done);
	TEST (ground_area_energy_map_navigator_get_count (ground_area_energy_map_navigator) == 60);
	calculate_worker_destroy (&calculate_worker);
	simulation_destroy (&simulation);
	timeline_destroy (&timeline);
}