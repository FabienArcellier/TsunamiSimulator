#include "debug.h"
#include "test.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"

/* Prototypes des fonctions de test */
void ground_area_energy_map_create_destroy_test ();
void ground_area_energy_map_get_energy_test ();
void ground_area_energy_map_push_pop_test ();

int main (void)
{
	ground_area_energy_map_create_destroy_test ();
	ground_area_energy_map_get_energy_test ();
	ground_area_energy_map_push_pop_test ();
	return 0;
}

void ground_area_energy_map_create_destroy_test ()
{
	TEST_TITLE ("ground_area_energy_map_create_destroy_test");
	PtrGroundAreaEnergyMap energy_map = NULL;
	
	PtrGroundArea ground_area = NULL;
  ground_area_create (&ground_area, 1000, 1000);
	
	ground_area_energy_map_create (&energy_map, ground_area);
	TEST (energy_map != NULL);
	TEST (energy_map -> map != NULL);
	
	ground_area_energy_map_destroy (&energy_map);
	TEST (energy_map == NULL);
}

void ground_area_energy_map_get_energy_test ()
{
	TEST_TITLE ("ground_area_energy_map_get_energy_test");
	
	PtrGroundArea ground_area = NULL;
  ground_area_create (&ground_area, 1000, 1000);
	
	PtrGround ground = ground_area_get_ground (ground_area, 5, 5);
	
	PtrWaveSignal wave_signal = NULL, wave_signal2 = NULL;
	wave_signal_create (&wave_signal);
	wave_signal_set_energy (wave_signal, 200.0);
	wave_signal_create (&wave_signal2);
	wave_signal_set_energy (wave_signal2, 100.0);
	
	ground_insert_signal (ground, wave_signal);
	ground_insert_signal (ground, wave_signal2);
	
	PtrGroundAreaEnergyMap energy_map = NULL;
	ground_area_energy_map_create (&energy_map, ground_area);
	
	double energy = ground_area_energy_map_get_energy (energy_map, 5, 5);
	DEBUG_IF ((energy == 300.0) == 0, "%f", energy); 
	TEST (energy == 300.0);
	
	ground_area_energy_map_destroy (&energy_map);
	
}

void ground_area_energy_map_push_pop_test ()
{
	TEST_TITLE ("ground_area_energy_map_stack_unstack_test");
	
	PtrGroundAreaEnergyMap energy_map = NULL;
	
	PtrGroundArea ground_area = NULL;
  ground_area_create (&ground_area, 1000, 1000);
	
	PtrGroundAreaEnergyMap energy_map1 = NULL, energy_map2 = NULL, energy_map3 = NULL;
	ground_area_energy_map_create (&energy_map1, ground_area);
	ground_area_energy_map_create (&energy_map2, ground_area);
	ground_area_energy_map_create (&energy_map3, ground_area);
	
	PtrGroundAreaEnergyMap list = NULL;
	
	ground_area_energy_map_push (&list, energy_map1);
	ground_area_energy_map_push (&list, energy_map2);
	ground_area_energy_map_push (&list, energy_map3);
	
	TEST (ground_area_energy_map_pop (&list) == energy_map1);
	TEST (ground_area_energy_map_pop (&list) == energy_map2);
	TEST (ground_area_energy_map_pop (&list) == energy_map3);
}