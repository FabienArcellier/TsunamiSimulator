#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

/* Your includes */
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
#include "ui/calculate_ui_private.h" // Gestion des events

/*!
 * \brief Cree une instance CalculateUI
 */
void calculate_ui_create (PtrCalculateUI *calculate_ui)
{
	assert (*calculate_ui == NULL);
	
	*calculate_ui = (PtrCalculateUI) malloc ( sizeof (CalculateUI));
	if (*calculate_ui == NULL)
	{
		g_error ("CalculateUI memory allocation failed");
	}
	
	memset (*calculate_ui, 0, sizeof (CalculateUI));
	
	// Chargement de l'interface
	GError* error = NULL;
	GtkBuilder* builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, "ui/calculate.glade", &error))
	{
		g_warning ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}
	
	// Chargement des objets
	(*calculate_ui )-> window = GTK_WINDOW (gtk_builder_get_object (builder, "window"));
	
	gtk_builder_connect_signals (builder, (*calculate_ui)); 
	calculate_ui_refresh_ihm_states ((*calculate_ui ));
	
	assert ((*calculate_ui )-> window != NULL);
}

/*!
 * \brief Detruit une instance CalculateUI
 */
void calculate_ui_destroy (PtrCalculateUI *calculate_ui)
{
	assert (*calculate_ui != NULL );
	
	free (*calculate_ui);
	*calculate_ui = NULL;
}

/*!
 * \brief Affiche la fenetre de l'IHM
 */
void calculate_ui_show (PtrCalculateUI calculate_ui)
{
	assert (calculate_ui != NULL);
	assert (calculate_ui -> window != NULL);
	
	gtk_widget_show_all (GTK_WIDGET (calculate_ui -> window));
}

/*!
 * \brief Cache la fenetre de l'IHM
 */
void calculate_ui_hide (PtrCalculateUI calculate_ui)
{
	assert (calculate_ui != NULL);
	assert (calculate_ui -> window != NULL);
	
	gtk_widget_hide (GTK_WIDGET (calculate_ui -> window));
}

/*!
 * \brief Affecte à chaque widget les attributs qu'il doit avoir selon les etats de l'objet
 */
void calculate_ui_refresh_ihm_states (PtrCalculateUI calculate_ui)
{
	assert (calculate_ui != NULL);
}

/*!
 * \brief Assesseur en lecture de l'attribut window
 */
GtkWindow* calculate_ui_get_window (PtrCalculateUI calculate_ui)
{
	assert (calculate_ui != NULL);
	
	return (calculate_ui -> window);
}

/* Your methods */




/* Events */

void calculate_ui_on_window_destroy (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	PtrCalculateUI calculate_ui = (PtrCalculateUI) data;
	
	g_debug ("on_window_destroy_event");
}

void calculate_ui_on_cancel_button_clicked (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	PtrCalculateUI calculate_ui = (PtrCalculateUI) data;
	
	g_debug ("calculate_ui_on_cancel_button_click");
}