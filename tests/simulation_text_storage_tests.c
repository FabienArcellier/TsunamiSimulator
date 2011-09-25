#include "test.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_text_storage.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_text_storage.h"
#include "event.h"
#include "earthquake_event.h"
#include "earthquake_events_text_storage.h"
#include "timeline.h"
#include "simulation.h"
#include "simulation_text_storage.h"

/* Prototypes de fonctions */
void simulation_text_storage_read_tests ();

int main (int argc, char *argv[])
{
	simulation_text_storage_read_tests ();
}

void simulation_text_storage_read_tests ()
{
	FILE* file = fopen ("simu1.simu", "r");
	FILE* file1 = fopen ("simu_test1.simu", "w");
	assert (file != NULL);
	
	PtrSimulationTextStorage simulation_text_storage = NULL;
	simulation_text_storage_create (&simulation_text_storage);
	TEST (simulation_text_storage != NULL);
	
	simulation_text_storage_set_file (simulation_text_storage, file);
	PtrSimulation simulation = simulation_text_storage_read_file (simulation_text_storage);
	
	simulation_text_storage_set_file (simulation_text_storage, file1);
	simulation_text_storage_write_file (simulation_text_storage, simulation);
	
	TEST (simulation != NULL);
	TEST (simulation_get_ground_area (simulation) != NULL);
	TEST (simulation_get_timeline (simulation) != NULL);
	TEST (timeline_get_events (simulation_get_timeline (simulation)) != NULL);
	
	fclose (file);
	fclose (file1);
}