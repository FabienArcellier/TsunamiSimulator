#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
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
	assert (energy_map != NULL);
	
	FILE* file = ground_area_energy_text_storage_get_file (ground_area_energy_text_storage); 
	
	fprintf (file,
						"datatype\t%s\tversion\t%s\n", 
						ground_area_energy_text_storage -> datatype, 
						ground_area_energy_text_storage -> version);
	
	int array_width = energy_map -> array_width;
	int array_length = energy_map -> array_length;
	
	int i = 0, j = 0;
	
	for (i = 0; i < array_width; i++)
	{
		for (j = 0; j < array_length; j++)
		{
			double energy = ground_area_energy_map_get_energy (energy_map, i, j);
			fprintf (file, "%.1f\t", energy);
		}
		fprintf (file, "\n");
	} 
}

/*!
 * \brief Lit le fichier ground_area_energy_text_storage
 */
PtrGroundAreaEnergyMap ground_area_energy_text_storage_read_file (PtrGroundAreaEnergyTextStorage ground_area_energy_text_storage,
																																	PtrGroundArea ground_area)
{
	assert (ground_area_energy_text_storage != NULL);
	assert (ground_area != NULL);
	
	char datatype[32] = "";
	char version[32] = "";
	int operation_done = 0;
	FILE *file = ground_area_energy_text_storage_get_file (ground_area_energy_text_storage);
	long file_initial_position = ftell (file);
	
	jump_over_commentary_sharp (file);
	operation_done = fscanf (
		file,
		"datatype\t%s\tversion\t%s\n",
		datatype,
		version
	);
	
	if (operation_done != 2
		|| strcmp(ground_area_energy_text_storage -> datatype, datatype) != 0
		|| strcmp(ground_area_energy_text_storage -> version, version) != 0
	)
	{
		fseek (file, file_initial_position, SEEK_SET);
		return NULL;
	}
	
	PtrGroundAreaEnergyMap ground_area_energy_map = NULL;
	ground_area_energy_map_create (&ground_area_energy_map, ground_area);
	
	int array_width = ground_area_energy_map -> array_width;
	int array_length = ground_area_energy_map -> array_length;
	
	int i = 0, j = 0;
	
	for (i = 0; i < array_width; i++)
	{
		for (j = 0; j < array_length; j++)
		{
			double energy = 0.0;
			
			jump_over_commentary_sharp (file);
			operation_done = fscanf (file, "%lf\t", &energy);
			
			if (operation_done != 1)
			{
				fseek (file, file_initial_position, SEEK_SET);
				return NULL;
			}
			
			ground_area_energy_map_set_energy (ground_area_energy_map, i, j, energy);
		}
		
		fscanf (file, "\n");
	} 
	
	return ground_area_energy_map;
}