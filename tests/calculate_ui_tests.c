
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
	PtrCalculateUI calculate_ui = NULL;
	calculate_ui_create (&calculate_ui);
	calculate_ui_show (calculate_ui);
	GtkWindow* window = calculate_ui_get_window (calculate_ui);
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (calculate_ui_std_destroy), calculate_ui);
	
	gtk_main();
}

void calculate_ui_std_destroy (GtkWidget* widget, gpointer data)
{
	gtk_main_quit();
}