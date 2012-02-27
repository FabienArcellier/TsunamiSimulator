#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "debug.h"

#include "file.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_map_navigator.h"
#include "event.h"
#include "earthquake_event.h"
#include "timeline.h"
#include "simulation.h"

#include "ground_area_text_storage.h"
#include "earthquake_events_text_storage.h"
#include "ground_area_energy_text_storage.h"
#include "simulation_text_storage.h"
#include "calculate_worker.h"

#include <gtk/gtk.h>
#include "ui/calculate_ui.h"
#include "ui/simulate_ui.h"
#include "ui/main_ui.h"

#include "ui/main_ui_private.h" // Gestion des events

/*!
 * \brief Cree une instance MainUI
 */
void main_ui_create (PtrMainUI *main_ui)
{
  assert (*main_ui == NULL);
  
  *main_ui = (PtrMainUI) malloc ( sizeof (MainUI));
  if (*main_ui == NULL)
  {
    g_error ("MainUI memory allocation failed");
  }
  
  memset (*main_ui, 0, sizeof (MainUI));
  
  // Chargement de l'interface
  GError* error = NULL;
  GtkBuilder* builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, "ui/main.glade", &error))
	{
		g_warning ("Couldn't load builder file: %s", error->message);
    g_error_free (error);
	}
	
	// Chargement des objets
	(*main_ui )-> window = GTK_WINDOW (gtk_builder_get_object (builder, "window"));
	(*main_ui )-> configure_button = GTK_BUTTON (gtk_builder_get_object (builder, "configure_button"));
	(*main_ui )-> calculate_button = GTK_BUTTON (gtk_builder_get_object (builder, "calculate_button"));
	(*main_ui )-> simulate_button = GTK_BUTTON (gtk_builder_get_object (builder, "simulate_button"));
	(*main_ui )-> new_menu = GTK_MENU_ITEM (gtk_builder_get_object (builder, "new_menu"));
	(*main_ui )-> open_menu = GTK_MENU_ITEM (gtk_builder_get_object (builder, "open_menu"));
	(*main_ui )-> save_menu = GTK_MENU_ITEM (gtk_builder_get_object (builder, "save_menu"));
	(*main_ui )-> quit_menu = GTK_MENU_ITEM (gtk_builder_get_object (builder, "quit_menu"));
	
	(*main_ui ) -> ihm_active = 1;
	
	gtk_builder_connect_signals (builder, (*main_ui)); 
	main_ui_refresh_ihm_states ((*main_ui ));
	
	assert ((*main_ui )-> window != NULL);
}

/*!
 * \brief Detruit une instance MainUI
 */
void main_ui_destroy (PtrMainUI *main_ui)
{
  assert (*main_ui != NULL );
  
  free (*main_ui);
  *main_ui = NULL;
}

/*!
 * \brief Affiche la fenetre de l'IHM
 */
void main_ui_show (PtrMainUI main_ui)
{
	assert (main_ui != NULL);
	assert (main_ui -> window != NULL);
	
	gtk_widget_show_all (GTK_WIDGET (main_ui -> window));
}

/*!
 * \brief Cache la fenetre de l'IHM
 */
void main_ui_hide (PtrMainUI main_ui)
{
	assert (main_ui != NULL);
	assert (main_ui -> window != NULL);
	
	gtk_widget_hide (GTK_WIDGET (main_ui -> window));
}

/*!
 * \brief Affecte à chaque widget les attributs qu'il doit avoir selon les etats de l'objet
 */
void main_ui_refresh_ihm_states (PtrMainUI main_ui)
{
	assert (main_ui != NULL);
	
	PtrSimulation simulation = main_ui_get_simulation (main_ui);
	int simulation_calculated = 0;
	
	if (simulation != NULL)
	{
		simulation_calculated = simulation_get_simulation_calculated (simulation);
	}

	// gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> configure_button), main_ui -> ihm_active && main_ui -> simulation_loaded);
	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> configure_button), 0);
	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> calculate_button), main_ui -> ihm_active && main_ui -> simulation_loaded);
	
	int simulate_button_activated = main_ui -> ihm_active && 
																		main_ui -> simulation_loaded && 
																		simulation_calculated;

	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> simulate_button), simulate_button_activated);
	
	// gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> new_menu), main_ui -> ihm_active);
	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> new_menu), 0);
	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> open_menu), main_ui -> ihm_active);
	// gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> save_menu), main_ui -> ihm_active);
	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> save_menu), 0);
	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> quit_menu), main_ui -> ihm_active);
}

/*!
 * \brief Assesseur en lecture de l'attribut window
 */
GtkWindow* main_ui_get_window (PtrMainUI main_ui)
{
	assert (main_ui != NULL);
	
	return (main_ui -> window);
}

/*!
 * \brief Assesseur en ecriture de l'attribut simulation_loaded
 */
void main_ui_set_simulation_loaded (PtrMainUI main_ui, int simulation_loaded)
{
	assert (main_ui != NULL);
	assert (simulation_loaded == 0 || simulation_loaded == 1);
	
	main_ui -> simulation_loaded = simulation_loaded;
}

/*!
 * \brief Assesseur en lecture de l'attribut simulation_loaded
 */
int main_ui_get_simulation_loaded (PtrMainUI main_ui)
{
	return main_ui -> simulation_loaded;
}

/*!
 * \brief Assesseur en ecriture de l'attribut ihm_active
 */
void main_ui_set_ihm_active (PtrMainUI main_ui, int ihm_active)
{
	assert (main_ui != NULL);
	assert (ihm_active == 0 || ihm_active == 1);
	
	main_ui -> ihm_active = ihm_active;
}

/*!
 * \brief Assesseur en lecture de l'attribut ihm_active
 */
int main_ui_get_ihm_active (PtrMainUI main_ui)
{
	assert (main_ui != NULL);
	return main_ui -> ihm_active;
}

/*!
 * \brief Assesseur en ecriture de l'attribut simulation
 */
void main_ui_set_simulation (PtrMainUI main_ui, PtrSimulation simulation)
{
	assert (main_ui != NULL);
	main_ui -> simulation = simulation;
}

/*!
 * \brief Assesseur en lecture de l'attribut simulation
 */
PtrSimulation main_ui_get_simulation (PtrMainUI main_ui)
{
	assert (main_ui != NULL);
	return main_ui -> simulation;
}

/*!
 * \brief Assesseur en ecriture de l'attribut calculate_ui
 */
void main_ui_set_calculate_ui (PtrMainUI main_ui, PtrCalculateUI calculate_ui)
{
	assert (main_ui != NULL);
	main_ui -> calculate_ui = calculate_ui;
}

/*!
 * \brief Assesseur en lecture de l'attribut calculate_ui
 */
PtrCalculateUI main_ui_get_calculate_ui (PtrMainUI main_ui)
{
	assert (main_ui != NULL);
	return main_ui -> calculate_ui;
}

void on_window_destroy_event (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	PtrMainUI main_ui = (PtrMainUI) data;
	
	g_debug ("on_window_destroy_event");
}

void on_configure_button_clicked (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	PtrMainUI main_ui = (PtrMainUI) data;
	
	g_debug ("on_configure_button_clicked");
}

void on_calculate_button_clicked (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	PtrMainUI main_ui = (PtrMainUI) data;
	g_debug ("on_calculate_button_clicked");
	
	main_ui_set_ihm_active (main_ui, 0);
	main_ui_refresh_ihm_states (main_ui);
	
	PtrCalculateUI calculate_ui = NULL;
	calculate_ui_create (&calculate_ui, main_ui_get_simulation (main_ui));
	calculate_ui_show (calculate_ui);
	main_ui_set_calculate_ui (main_ui, calculate_ui);
	
	GtkWindow *window = calculate_ui_get_window (calculate_ui);
	g_signal_connect (GTK_WIDGET (window), "destroy", G_CALLBACK (main_ui_calculate_ui_on_window_destroy), main_ui);
	
	calculate_ui_start_worker (calculate_ui);
}

void on_simulate_button_clicked (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	PtrMainUI main_ui = (PtrMainUI) data;
	g_debug ("on_simulate_button_clicked");
	
	main_ui_set_ihm_active (main_ui, 0);
	main_ui_refresh_ihm_states (main_ui);
	
	PtrSimulateUI simulate_ui = NULL;
	simulate_ui_create (&simulate_ui, main_ui_get_simulation (main_ui));
	simulate_ui_show (simulate_ui);
	main_ui_set_simulate_ui (main_ui, simulate_ui);
	
	GtkWindow *window = simulate_ui_get_window (simulate_ui);
	g_signal_connect (GTK_WIDGET (window), "destroy", G_CALLBACK (main_ui_simulate_ui_on_window_destroy), main_ui);
}

void on_new_menu_activate (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	PtrMainUI main_ui = (PtrMainUI) data;
	
	g_debug ("on_new_menu_activate");
}

void on_open_menu_activate (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	PtrMainUI main_ui = (PtrMainUI) data;
	
	assert (main_ui -> window != NULL);
	
	g_debug ("on_open_menu_activate");
	
	GtkWidget *dialog = NULL;
  gchar *filename = NULL;
  
  dialog = gtk_file_chooser_dialog_new ("Open File ...",
                                        main_ui -> window,
                                        GTK_FILE_CHOOSER_ACTION_OPEN,
                                        GTK_STOCK_CANCEL,
                                        GTK_RESPONSE_CANCEL,
                                        GTK_STOCK_OPEN, 
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);
  
  gint result = gtk_dialog_run (GTK_DIALOG (dialog));
  if (result == GTK_RESPONSE_ACCEPT)
  {
    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		g_debug (filename);
		
		FILE* file = fopen (filename, "r");
		
		PtrSimulation simulation = NULL;
		PtrSimulationTextStorage simulation_text_storage = NULL;
		simulation_text_storage_create (&simulation_text_storage);
		simulation_text_storage_set_file (simulation_text_storage, file);
		simulation = simulation_text_storage_read_file (simulation_text_storage);
		simulation_text_storage_destroy (&simulation_text_storage);
		fclose (file);
		
		// Liberation de la memoire pour l'ancien composant simulation
		if (main_ui_get_simulation (main_ui) != NULL)
		{
			PtrSimulation old_simulation = main_ui_get_simulation (main_ui);
			
			PtrTimeline old_timeline = simulation_get_timeline (old_simulation);
			timeline_destroy (&old_timeline);
			
			PtrGroundArea old_ground_area = simulation_get_ground_area (old_simulation);
			ground_area_destroy (&old_ground_area);
			
			PtrGroundAreaEnergyMapNavigator old_energy_map_navigator = simulation_get_energy_map_navigator (old_simulation);
			ground_area_energy_map_navigator_destroy (&old_energy_map_navigator);
			
			simulation_destroy (&old_simulation);
		}
		
		main_ui_set_simulation (main_ui, simulation);
		
		if (simulation != NULL)
		{
			// TODO : Securiser cette chaine de caractere
			GtkWindow *window = main_ui_get_window (main_ui);
			char *filename_with_extension = get_filename_with_extension (filename);
			char title[255];
			sprintf (title, "%s - Tsunami Simulator", filename_with_extension);
			gtk_window_set_title (window, title);
			free (filename_with_extension);
			main_ui_set_simulation_loaded (main_ui, 1);
		}
		
		g_free (filename);
		main_ui_refresh_ihm_states (main_ui);
  }
  else
	{
		main_ui_refresh_ihm_states (main_ui);
	}
	
  gtk_widget_destroy (dialog);
}

void on_save_menu_activate (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	DEBUG_IF (1, "%p", data);
	PtrMainUI main_ui = (PtrMainUI) data;
	
	g_debug ("on_save_menu_activate");
}

void on_quit_menu_activate (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	g_debug ("on_quit_menu_activate");
	PtrMainUI main_ui = (PtrMainUI) data;
	
	GtkWindow* window = main_ui_get_window (main_ui);
	gtk_widget_destroy (GTK_WIDGET (main_ui -> window));
}

/*!
 * \brief Methode appellée a l'issue du processus de calcul
 */
void main_ui_calculate_ui_on_window_destroy (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	PtrMainUI main_ui = (PtrMainUI) data;
	PtrCalculateUI calculate_ui = main_ui_get_calculate_ui (main_ui);
	calculate_ui_destroy (&calculate_ui);
	main_ui_set_calculate_ui (main_ui, NULL);
	
	main_ui_set_ihm_active (main_ui, 1);
	main_ui_refresh_ihm_states (main_ui);
	
}

void main_ui_simulate_ui_on_window_destroy (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	PtrMainUI main_ui = (PtrMainUI) data;
	PtrSimulateUI simulate_ui = main_ui_get_simulate_ui (main_ui);
	simulate_ui_destroy (&simulate_ui);
	main_ui_set_simulate_ui (main_ui, NULL);
	
	main_ui_set_ihm_active (main_ui, 1);
	main_ui_refresh_ihm_states (main_ui);
}

/*!
 * \brief Assesseur en ecriture de l'attribut simulate_ui
 */
void main_ui_set_simulate_ui (PtrMainUI main_ui, PtrSimulateUI simulate_ui)
{
	assert (main_ui != NULL);
	main_ui -> simulate_ui = simulate_ui;
}

/*!
 * \brief Assesseur en lecture de l'attribut simulate_ui
 */
PtrSimulateUI main_ui_get_simulate_ui (PtrMainUI main_ui)
{
	assert (main_ui != NULL);
	return main_ui -> simulate_ui;
}