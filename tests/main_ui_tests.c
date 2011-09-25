#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "event.h"
#include "timeline.h"
#include "simulation.h"
#include <gtk/gtk.h>
#include "ui/main_ui.h"

/* Prototype des fonctions de test */
void main_ui_create_show_tests ();
void main_ui_std_destroy (GtkWidget*, gpointer);

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	main_ui_create_show_tests ();
	
}

void main_ui_create_show_tests ()
{
	DEBUG_IF (1, "%d", g_module_supported ());
	PtrMainUI main_ui = NULL;
	main_ui_create (&main_ui);
	main_ui_show (main_ui);
	GtkWindow* window = main_ui_get_window (main_ui);
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (main_ui_std_destroy), main_ui);
	
	
	gtk_main();
}

void main_ui_std_destroy (GtkWidget* widget, gpointer data)
{
	gtk_main_quit();
}