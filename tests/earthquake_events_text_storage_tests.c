#include <assert.h>
#include <stdio.h>
#include "test.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "event.h"
#include "earthquake_event.h"
#include "earthquake_events_text_storage.h"



/* Prototypes des fonctions de test */
void earthquake_events_text_storage_create_destroy_test ();
void earthquake_events_text_storage_write_read_file ();

int main (void)
{
	earthquake_events_text_storage_create_destroy_test ();
	earthquake_events_text_storage_write_read_file ();
	return 0;
}

void earthquake_events_text_storage_create_destroy_test ()
{
	PtrEarthquakeEventsTextStorage earthquake_events_text_storage = NULL;
	earthquake_events_text_storage_create (&earthquake_events_text_storage);
	
	TEST (earthquake_events_text_storage != NULL);
	
	earthquake_events_text_storage_destroy (&earthquake_events_text_storage);
	TEST (earthquake_events_text_storage == NULL);
}

void earthquake_events_text_storage_write_read_file ()
{
	FILE *file = NULL;
	file = fopen ("earthquake_events_text_storage_write_read_file.txt", "w");
	assert (file != NULL);
	
	PtrGroundArea ground_area = NULL;
	ground_area_create (&ground_area, 1000, 1000);
	
	PtrGround ground = ground_area_get_ground (ground_area, 5, 5);
	
	PtrEarthquakeEvent event = NULL;
	earthquake_event_create (&event);
	earthquake_event_set_ground (event, ground);
	event_set_time (EVENT (event), 5);
	
	PtrEarthquakeEvent event2 = NULL;
	earthquake_event_create (&event2);
	earthquake_event_set_ground (event2, ground);
	event_set_time (EVENT (event2), 10);
	event_insert_sort_by_time_asc (EVENT (event), EVENT (event2));
	
	PtrEarthquakeEventsTextStorage earthquake_events_text_storage = NULL;
	earthquake_events_text_storage_create (&earthquake_events_text_storage);
	earthquake_events_text_storage_set_file (earthquake_events_text_storage, file);
	
	earthquake_events_text_storage_write_file (earthquake_events_text_storage, event); 
	
	PtrEarthquakeEvent event_read = NULL;
	event_read = (PtrEarthquakeEvent) earthquake_events_text_storage_read_file (earthquake_events_text_storage, ground_area);
	TEST (earthquake_event_get_ground (event) == ground);
}
