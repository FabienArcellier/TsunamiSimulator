#include "test.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "event.h"
#include "timeline.h"
#include "simulation.h"

/* Prototypes des fonctions de tests */
void simulation_create_destroy_tests ();

int main (void)
{
	simulation_create_destroy_tests ();
}

void simulation_create_destroy_tests ()
{
	TEST_TITLE ("simulation_create_destroy_tests");
	PtrSimulation simulation = NULL;
	
	simulation_create (&simulation);
	TEST (simulation != NULL);
	
	simulation_destroy (&simulation);
	TEST (simulation == NULL);
}