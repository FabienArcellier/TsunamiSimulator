#include <stdio.h>
#include <gtk/gtk.h>
#include "test.h"
#include "debug.h"
#include "event.h"
#include "wave_signal.h"
#include "ground.h"
#include "earthquake_event.h"
#include "timeline.h"
#include "ground_area.h"
#include "ground_area_text_storage.h"
#include "propagation_timeline_processings.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_text_storage.h"
#include "ground_area_to_pixbuf_factory.h"

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	PtrTimeline timeline = NULL;
	timeline_create (&timeline);
	timeline_set_final_time (timeline, 150);
	
	puts ("Chargement du terrain");
	
	FILE *ground_file = fopen ("ground.txt", "r");
	fscanf (ground_file, "[Terrain]\n");
	PtrGroundAreaTextStorage ground_area_text_storage = NULL;
	ground_area_text_storage_create (&ground_area_text_storage);
	ground_area_text_storage_set_file (ground_area_text_storage, ground_file);
	
	PtrGroundArea ground_area = NULL;
	ground_area = ground_area_text_storage_read_file (ground_area_text_storage);
	ground_area_text_storage_destroy (&ground_area_text_storage);
	fclose (ground_file);
	
	puts("Definition des tremblements de terre");  
	
	PtrGround epicentre_ground = ground_area_get_ground (ground_area, 700, 60);
	
	PtrEarthquakeEvent earthquake = NULL;
	earthquake_event_create (&earthquake);
	earthquake_event_set_ground (earthquake, epicentre_ground);
	earthquake_event_set_energy (earthquake, 100000000000.0);
	event_set_time (EVENT (earthquake), 1);
	
	PtrEarthquakeEvent earthquake2 = NULL;
	earthquake_event_create (&earthquake2);
	earthquake_event_set_ground (earthquake2, epicentre_ground);
	earthquake_event_set_energy (earthquake2, 1000000000000.0);
	event_set_time (EVENT (earthquake2), 3);
	
	PtrGroundAreaEnergyTextStorage ground_area_energy_report = NULL;
	ground_area_energy_text_storage_create (&ground_area_energy_report);
	
	FILE *report = fopen ("report.txt", "w");
	ground_area_energy_text_storage_set_file (ground_area_energy_report, report);
	
	timeline_insert_event (timeline, EVENT (earthquake));
	timeline_insert_event (timeline, EVENT (earthquake2));
	
	PtrGroundAreaEnergyMap list_energy_map = NULL;
	
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		printf ("Iteration %d\n", i);
 		char file_name[32];
		register_events_for_propagation_on_timeline_from_ground_area (timeline, ground_area);
		timeline_execute_events (timeline);
		simplify_wave_signals_after_propagation_on_ground_area (ground_area);
		
		PtrGroundAreaEnergyMap ground_area_energy_map = NULL;
		ground_area_energy_map_create (&ground_area_energy_map, ground_area);
		
// 		fprintf (report, "Time : %.2d \n", timeline_get_current_time (timeline));
// 		ground_area_energy_text_storage_write_file (ground_area_energy_report, ground_area_energy_map);
		
		GdkPixbuf* picture = ground_area_to_pixbuf (ground_area);
		picture = ground_area_energy_map_to_pixbuf (picture, ground_area_energy_map);
		sprintf (file_name, "picture_%d.png", i);
		gdk_pixbuf_save (picture, file_name, "png", NULL, NULL);
		g_object_unref (G_OBJECT (picture));
		
		timeline_move_current_time (timeline, 1);
		ground_area_energy_map_push (&list_energy_map, ground_area_energy_map);

	}
	
	ground_area_energy_text_storage_write_file (ground_area_energy_report, list_energy_map);
	ground_area_energy_map_destroy (&list_energy_map);
	fclose (report);

	return 0;
}