#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "file.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "event.h"
#include "earthquake_event.h"
#include "earthquake_events_text_storage.h"

/*!
 * \brief Cree une instance de EarthquakeEventsTextStorage
 */
void earthquake_events_text_storage_create (PtrEarthquakeEventsTextStorage *earthquake_events_text_storage)
{
	assert (*earthquake_events_text_storage == NULL);
	
	*earthquake_events_text_storage = (PtrEarthquakeEventsTextStorage) malloc (sizeof (EarthquakeEventsTextStorage));
	memset (*earthquake_events_text_storage, 0, sizeof (EarthquakeEventsTextStorage));
	
	strcpy((*earthquake_events_text_storage) -> datatype, EARTHQUAKE_EVENTS_TEXT_STORAGE_DATATYPE); 
	strcpy((*earthquake_events_text_storage) -> version, EARTHQUAKE_EVENTS_TEXT_STORAGE_VERSION); 
}

/*!
 * \brief Detruit une instance de EarthquakeEventsTextStorage
 */
void earthquake_events_text_storage_destroy (PtrEarthquakeEventsTextStorage *earthquake_events_text_storage)
{
	assert (*earthquake_events_text_storage != NULL);
	
	free (*earthquake_events_text_storage);
	*earthquake_events_text_storage = NULL;
}

/*!
 * \brief Assesseur en ecriture de l'attribut file
 */
void earthquake_events_text_storage_set_file (PtrEarthquakeEventsTextStorage earthquake_events_text_storage,
																							FILE* file)
{
	assert (earthquake_events_text_storage != NULL);
	earthquake_events_text_storage -> file = file;
}

/*!
 * \brief Assesseur en lecture de l'attribut file
 */
FILE* earthquake_events_text_storage_get_file (PtrEarthquakeEventsTextStorage earthquake_events_text_storage)
{
	assert (earthquake_events_text_storage != NULL);
	return earthquake_events_text_storage -> file;
}

/*!
 * \brief Lance l'ecriture du fichier
 */
void earthquake_events_text_storage_write_file (PtrEarthquakeEventsTextStorage earthquake_events_text_storage, 
																								PtrEvent earthquake_event_cast)
{
	assert (earthquake_events_text_storage != NULL);
	assert (earthquake_events_text_storage -> file != NULL);
	assert (earthquake_event_cast != NULL);
	
	PtrEarthquakeEvent earthquake_event = (PtrEarthquakeEvent) earthquake_event_cast; 
	
	FILE* file = earthquake_events_text_storage_get_file (earthquake_events_text_storage);
	fprintf (file, "#temps\ttype\tpositionX\tpositionY\tEnergie\n");
	
	while (earthquake_event != NULL)
	{
		int time = event_get_time (EVENT (earthquake_event));
		PtrGround ground = earthquake_event_get_ground (earthquake_event);
		int positionX = ground_get_position_X (ground);
		int positionY = ground_get_position_Y (ground);
		double energy = earthquake_event_get_energy (earthquake_event);
		
		fprintf (file,
						 "%d\t%d\t%d\t%f\n",
						 time,
						 positionX,
						 positionY,
						 energy);
		
		earthquake_event = (PtrEarthquakeEvent) event_get_next_event (EVENT (earthquake_event));
	}
	
	printf ("\n");
}

/*!
 * \brief Lance la lecture du fichier
 */
PtrEvent earthquake_events_text_storage_read_file (PtrEarthquakeEventsTextStorage earthquake_events_text_storage, 
																														 PtrGroundArea ground_area)
{
	assert (earthquake_events_text_storage != NULL);
	assert (earthquake_events_text_storage -> file != NULL);
	assert (ground_area != NULL);
	
	char datatype[32] = "";
	char version[32] = "";
	int operation_done = 0;
	FILE *file = earthquake_events_text_storage_get_file (earthquake_events_text_storage);
	long file_initial_position = ftell (file);
	
	jump_over_commentary_sharp (file);
	operation_done = fscanf (
		file,
		"datatype\t%s\tversion\t%s\n",
		datatype,
		version
	);
	
	if (operation_done != 2
		|| strcmp(earthquake_events_text_storage -> datatype, datatype) != 0
		|| strcmp(earthquake_events_text_storage -> version, version) != 0
	)
	{
		DEBUG_IF (1, "%s", "Erreur earthquake_events_text_storage_read_file");
		DEBUG_IF (1, "%d", operation_done);
		DEBUG_IF (1, "%s", datatype);
		DEBUG_IF (1, "%s", version);
		fseek (file, file_initial_position, SEEK_SET);
		return NULL;
	}
	
	PtrEvent events = NULL;
	
	do
	{
		jump_over_commentary_sharp (file);
		
		PtrEarthquakeEvent element = NULL;
		int time = 0;
		int positionX = 0;
		int positionY = 0;
		double energy = 0.0;
		operation_done = fscanf (file,
						"%d\t%d\t%d\t%lf\n",
						&time,
						&positionX,
						&positionY,
						&energy);
		
// 		DEBUG_IF (1, "%d", operation_done);
// 		DEBUG_IF (1, "%d", time);
// 		DEBUG_IF (1, "%d", positionX);
// 		DEBUG_IF (1, "%d", positionY);
// 		DEBUG_IF (1, "%f", energy);
		
		if (operation_done == 4)
		{
			PtrGround ground = ground_area_get_ground (ground_area, positionX / 100, positionY / 100);
			earthquake_event_create (&element);
			event_set_time (EVENT (element), time);
			earthquake_event_set_energy (element, energy);
			earthquake_event_set_ground (element, ground);
			
			events = event_insert_sort_by_time_asc (events, EVENT (element));
		}
	} while (operation_done == 4);
	
	return events;
}