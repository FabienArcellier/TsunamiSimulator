
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "debug.h"

#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_map_navigator.h"
#include "event.h"
#include "timeline.h"
#include "simulation.h"
#include "ui/simulate_ui.h"

/* Prototype des fonctions de test */
void simulate_ui_create_show_tests ();
void simulate_ui_std_destroy (GtkWidget*, gpointer);

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	simulate_ui_create_show_tests ();
	
	return 0;
}

void simulate_ui_create_show_tests ()
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
	
	PtrSimulateUI simulate_ui = NULL;
	simulate_ui_create (&simulate_ui, simulation);
	simulate_ui_show (simulate_ui);
	GtkWindow* window = simulate_ui_get_window (simulate_ui);
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (simulate_ui_std_destroy), simulate_ui);
	
	gtk_main();
}

void simulate_ui_std_destroy (GtkWidget* widget, gpointer data)
{
	gtk_main_quit();
}