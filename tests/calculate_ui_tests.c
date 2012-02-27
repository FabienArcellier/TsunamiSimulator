
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "debug.h"

#include <pthread.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_map_navigator.h"
#include "event.h"
#include "earthquake_event.h"
#include "earthquake_events_text_storage.h"
#include "timeline.h"
#include "propagation_timeline_processings.h"
#include "simulation.h"
#include "calculate_worker.h"
#include "ui/calculate_ui.h"

/* Prototype des fonctions de test */
void calculate_ui_create_show_tests ();
void calculate_ui_std_destroy (GtkWidget*, gpointer);

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	calculate_ui_create_show_tests ();
	
	return 0;
}

void calculate_ui_create_show_tests ()
{
	DEBUG_IF (1, "%d", g_module_supported ());
	
	PtrTimeline timeline = NULL;
	timeline_create (&timeline);
	timeline_set_final_time (timeline, 1000);
	
	PtrGroundArea ground_area = NULL;
	ground_area_create (&ground_area, 10000, 10000);
	
	PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator = NULL;
	ground_area_energy_map_navigator_create (&ground_area_energy_map_navigator);
	
	PtrSimulation simulation = NULL;
	simulation_create (&simulation);
	simulation_set_timeline (simulation, timeline);
	simulation_set_ground_area (simulation, ground_area);
	simulation_set_energy_map_navigator (simulation, ground_area_energy_map_navigator);
	
	PtrCalculateUI calculate_ui = NULL;
	puts ("a");
	calculate_ui_create (&calculate_ui, simulation);
	puts ("b");
	calculate_ui_show (calculate_ui);
	puts ("c");
	
	GtkWindow* window = calculate_ui_get_window (calculate_ui);
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (calculate_ui_std_destroy), calculate_ui);
	
	puts ("d");
	calculate_ui_start_worker (calculate_ui);
	puts ("e");

	gtk_main();
}

void calculate_ui_std_destroy (GtkWidget* widget, gpointer data)
{
	gtk_main_quit();
}