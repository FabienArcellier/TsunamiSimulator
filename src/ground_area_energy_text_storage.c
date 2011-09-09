#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_text_storage.h"

/*!
 * \brief Cree un rapport d'energie pour ground area.
 */
void ground_area_energy_text_storage_create (PtrGroundAreaEnergyTextStorage *ground_area_energy_text_storage)
{
	assert (*ground_area_energy_text_storage == NULL);
	*ground_area_energy_text_storage = (PtrGroundAreaEnergyTextStorage) malloc (sizeof (GroundAreaEnergyTextStorage));
	memset (*ground_area_energy_text_storage, 0, sizeof (GroundAreaEnergyTextStorage));
	
	strcpy ((*ground_area_energy_text_storage) -> datatype, GROUND_AREA_ENERGY_TEXT_STORAGE_DATATYPE);
	strcpy ((*ground_area_energy_text_storage) -> version, GROUND_AREA_ENERGY_TEXT_STORAGE_VERSION);
}

/*!
 * \brief Detruit une instance de l'objet ground_area_energy_text_storage
 */
void ground_area_energy_text_storage_destroy (PtrGroundAreaEnergyTextStorage *ground_area_energy_text_storage)
{
	assert (*ground_area_energy_text_storage != NULL);
	free (*ground_area_energy_text_storage);
	*ground_area_energy_text_storage = NULL;
}

/*!
 * \brief Assesseur de l'attribut file en ecriture
 */
void ground_area_energy_text_storage_set_file (PtrGroundAreaEnergyTextStorage ground_area_energy_text_storage, FILE *file)
{
	assert (ground_area_energy_text_storage != NULL);
	ground_area_energy_text_storage -> file = file;
}

/*!
 * \brief Assesseur de l'attribut file en lecture
 */
FILE* ground_area_energy_text_storage_get_file (PtrGroundAreaEnergyTextStorage ground_area_energy_text_storage)
{
	assert (ground_area_energy_text_storage != NULL);
	return ground_area_energy_text_storage -> file;
}

/*!
 * \brief Ecrire le fichier ground_area_energy_text_storage
 */
void ground_area_energy_text_storage_write_file (PtrGroundAreaEnergyTextStorage ground_area_energy_text_storage, PtrGroundAreaEnergyMap ground_area_energy_map)
{
	assert (ground_area_energy_text_storage != NULL);
	assert (ground_area_energy_text_storage_get_file (ground_area_energy_text_storage) != NULL);
	
	PtrGroundAreaEnergyMap energy_map = ground_area_energy_map;
	PtrGroundAreaEnergyMap energy_map_recomposed = NULL;
	
	FILE* file = ground_area_energy_text_storage_get_file (ground_area_energy_text_storage); 
	
	fprintf (file,
						"datatype\t%s\tversion\t%s\n", 
						ground_area_energy_text_storage -> datatype, 
						ground_area_energy_text_storage -> version);
	
	int time = 0;
	while (ground_area_energy_map_empty (energy_map) == 0)
	{
		PtrGroundAreaEnergyMap energy_map_to_serialize = ground_area_energy_map_pop (&energy_map);
		fprintf (file, "Time\t%d\n", time);
		int array_width = energy_map_to_serialize -> array_width;
		int array_length = energy_map_to_serialize -> array_length;
		
		int i = 0, j = 0;
		
		for (i = 0; i < array_width; i++)
		{
			for (j = 0; j < array_length; j++)
			{
				double energy = ground_area_energy_map_get_energy (energy_map_to_serialize, i, j);
				fprintf (file, "%.1f\t", energy);
			}
			fprintf (file, "\n");
		}
		fprintf (file, "\n");
		
		time++;
		ground_area_energy_map_push (&energy_map_recomposed, energy_map_to_serialize);
	} 
}