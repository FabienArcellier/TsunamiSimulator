#include "debug.h"
#include "test.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*TODO : Includes to complete */
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_text_storage.h"

/* Prototypes des fonctions de tests */
void ground_area_energy_text_storage_create_destroy_test ();
void ground_area_energy_text_storage_write_read_test ();

int main (void)
{
	ground_area_energy_text_storage_create_destroy_test ();
	ground_area_energy_text_storage_write_read_test ();
	return 0;
}

/*!
 * \brief Teste la creation et la destruction d'une instance de type GroundAreaEnergyTextStorage
 */
void ground_area_energy_text_storage_create_destroy_test ()
{
	TEST_TITLE ("ground_area_energy_text_storage_create_destroy_test");
	PtrGroundAreaEnergyTextStorage ground_area_energy_text_storage = NULL;
	
	ground_area_energy_text_storage_create (&ground_area_energy_text_storage);
	TEST (ground_area_energy_text_storage != NULL);
	
	ground_area_energy_text_storage_destroy (&ground_area_energy_text_storage);
	TEST (ground_area_energy_text_storage == NULL);
}

void ground_area_energy_text_storage_write_read_test ()
{
	TEST_TITLE ("ground_area_energy_text_storage_write_read_test");
	
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
	
	PtrGroundAreaEnergyMap energy_map = NULL, energy_map_readed = NULL;
	ground_area_energy_map_create (&energy_map, ground_area);
	
	FILE *file = fopen ("ground_area_energy_text_storage_write_test.txt", "w+");
	
	PtrGroundAreaEnergyTextStorage ground_area_energy_text_storage = NULL;
	ground_area_energy_text_storage_create (&ground_area_energy_text_storage);
	
	ground_area_energy_text_storage_set_file (ground_area_energy_text_storage, file);
	ground_area_energy_text_storage_write_file (ground_area_energy_text_storage, energy_map);
	fseek (file, 0, SEEK_SET);
	energy_map_readed = ground_area_energy_text_storage_read_file (ground_area_energy_text_storage, ground_area);
	
	double energy = ground_area_energy_map_get_energy (energy_map_readed, 5, 5);
	TEST (energy_map != energy_map_readed);
	TEST (energy == 300.0);
	
	ground_area_energy_text_storage_destroy (&ground_area_energy_text_storage);
	ground_area_energy_map_destroy (&energy_map);
	ground_area_energy_map_destroy (&energy_map_readed);
	ground_area_destroy (&ground_area);
}