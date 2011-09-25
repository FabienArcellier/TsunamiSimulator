#include <stdio.h>
#include "test.h"
#include "debug.h"
#include "event.h"
#include "wave_signal.h"
#include "ground.h"
#include "earthquake_event.h"
#include "timeline.h"
#include "ground_area.h"
#include "propagation_timeline_processings.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_text_storage.h"

int main (void)
{
	
	FILE *report = fopen ("test.txt", "w+");
	PtrTimeline timeline = NULL;
	timeline_create (&timeline);
	timeline_set_final_time (timeline, 20);
	
	PtrGroundArea ground_area = NULL;
	ground_area_create (&ground_area, 1000, 1000);
	PtrGround epicentre_ground = ground_area_get_ground (ground_area, 5, 5);
	
	PtrEarthquakeEvent earthquake = NULL;
	earthquake_event_create (&earthquake);
	earthquake_event_set_ground (earthquake, epicentre_ground);
	earthquake_event_set_energy (earthquake, 100000.0);
	event_set_time (EVENT (earthquake), 1);
	
	PtrEarthquakeEvent earthquake2 = NULL;
	earthquake_event_create (&earthquake2);
	earthquake_event_set_ground (earthquake2, epicentre_ground);
	earthquake_event_set_energy (earthquake2, 100000.0);
	event_set_time (EVENT (earthquake2), 3);
	
	PtrGroundAreaEnergyTextStorage ground_area_energy_report = NULL;
	ground_area_energy_text_storage_create (&ground_area_energy_report);
	ground_area_energy_text_storage_set_file (ground_area_energy_report, report);
	
	fclose (report);
	
	timeline_insert_event (timeline, EVENT (earthquake));
	timeline_insert_event (timeline, EVENT (earthquake2));
	
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		report = fopen ("test.txt", "a+");
		ground_area_energy_text_storage_set_file (ground_area_energy_report, report);
		register_events_for_propagation_on_timeline_from_ground_area (timeline, ground_area);
		timeline_execute_events (timeline);
		simplify_wave_signals_after_propagation_on_ground_area (ground_area);
		
		PtrGroundAreaEnergyMap ground_area_energy_map = NULL;
		ground_area_energy_map_create (&ground_area_energy_map, ground_area);
		
		fprintf (report, "Time : %.2d \n", timeline_get_current_time (timeline));
		ground_area_energy_text_storage_write_file (ground_area_energy_report, ground_area_energy_map);
		ground_area_energy_map_destroy (&ground_area_energy_map);
		timeline_move_current_time (timeline, 1);
		fclose (report);
	}

	return 0;
}