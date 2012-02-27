#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

/* Your includes */
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
#include "ui/calculate_ui_private.h" // Gestion des events

/*!
 * \brief Cree une instance CalculateUI
 */
void calculate_ui_create (PtrCalculateUI *calculate_ui, PtrSimulation simulation)
{
	assert (*calculate_ui == NULL);
	assert (simulation != NULL);
	
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
	(*calculate_ui) -> window = GTK_WINDOW (gtk_builder_get_object (builder, "window"));
	(*calculate_ui) -> progress_bar = GTK_PROGRESS_BAR (gtk_builder_get_object (builder, "progress_bar"));
	(*calculate_ui) -> cancel_button = GTK_BUTTON (gtk_builder_get_object (builder, "cancel_button"));
	(*calculate_ui) -> progression_label = GTK_LABEL (gtk_builder_get_object (builder, "progression_label"));
	(*calculate_ui) -> spinner = GTK_SPINNER (gtk_builder_get_object (builder, "spinner"));
	gtk_label_set_text ((*calculate_ui) -> progression_label, "");
	gtk_spinner_start ((*calculate_ui) -> spinner);
	
	(*calculate_ui) -> simulation = simulation;
	
	// Creation de calculate worker
	PtrCalculateWorker calculate_worker = NULL;
	calculate_worker_create (&calculate_worker, simulation);
	(*calculate_ui) -> calculate_worker = calculate_worker;
	
	gtk_builder_connect_signals (builder, (*calculate_ui)); 
	calculate_ui_refresh_ihm_states ((*calculate_ui ));
	
	// Instanciation de la fonction timeout pour rafraichir l'IHM pendant le traitement
	(*calculate_ui) -> timeout_refresh_id = g_timeout_add (500, calculate_ui_timeout, (*calculate_ui ));
	
	assert ((*calculate_ui )-> window != NULL);
}

/*!
 * \brief Detruit une instance CalculateUI
 */
void calculate_ui_destroy (PtrCalculateUI *calculate_ui)
{
	assert (*calculate_ui != NULL );
	
	GSource *timeout = g_main_context_find_source_by_id (NULL, (*calculate_ui) -> timeout_refresh_id);
	g_source_destroy (timeout);
	calculate_worker_destroy (&((*calculate_ui) -> calculate_worker));
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
	assert (calculate_ui -> progress_bar != NULL);
	assert (calculate_ui -> progression_label != NULL);
	
	PtrSimulation simulation = calculate_ui_get_simulation (calculate_ui);
	PtrTimeline timeline = simulation_get_timeline (simulation);
	int nb_cartes = timeline_get_final_time (timeline);
	
	PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator = simulation_get_energy_map_navigator (simulation);
	int nb_cartes_calculated = ground_area_energy_map_navigator_get_count (ground_area_energy_map_navigator);
	
	double progression = ((double) nb_cartes_calculated) / ((double) nb_cartes);
	
	char progression_text[255];
	sprintf (progression_text, "%d / %d s", nb_cartes_calculated, nb_cartes);
	gtk_label_set_text (calculate_ui -> progression_label, progression_text);
	
	gtk_progress_bar_set_fraction (calculate_ui -> progress_bar, progression);
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

/*!
 * \brief Demarre le worker de calcul
 */
void calculate_ui_start_worker (PtrCalculateUI calculate_ui)
{
	assert (calculate_ui != NULL);
	assert (calculate_ui -> simulation != NULL);
	assert (calculate_ui -> calculate_worker != NULL);
	
	calculate_worker_start (calculate_ui -> calculate_worker);
}

/*!
 * \brief Assesseur en lecture de l'attribut simulation
 */
PtrSimulation calculate_ui_get_simulation (PtrCalculateUI calculate_ui)
{
	assert (calculate_ui != NULL);
	return calculate_ui -> simulation;
}

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
	
	assert (calculate_ui -> calculate_worker != NULL);
	
	g_debug ("calculate_ui_on_cancel_button_click");
	
	calculate_worker_cancel (calculate_ui -> calculate_worker);
}

/*!
 * \brief Mis a jour de l'IHM a intervalle regulier
 */
gint calculate_ui_timeout (gpointer data)
{
	PtrCalculateUI calculate_ui = (PtrCalculateUI) data;
	assert (calculate_ui != NULL);
	assert (calculate_ui -> calculate_worker != NULL);
	
	PtrCalculateWorker calculate_worker = calculate_ui -> calculate_worker;
	PtrSimulation simulation = calculate_ui_get_simulation (calculate_ui);
	
	if (calculate_worker_get_state (calculate_worker) == calculate_worker_state_done
		|| calculate_worker_get_state (calculate_worker) == calculate_worker_state_canceled)
	{
		gtk_widget_destroy (GTK_WIDGET (calculate_ui_get_window (calculate_ui)));
		return FALSE;
	}
	else
	{
		calculate_ui_refresh_ihm_states (calculate_ui);
		return TRUE;
	}
}