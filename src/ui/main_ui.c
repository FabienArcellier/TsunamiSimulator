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

	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> configure_button), main_ui -> ihm_active && main_ui -> simulation_loaded);
	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> calculate_button), main_ui -> ihm_active && main_ui -> simulation_loaded);
	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> simulate_button), main_ui -> ihm_active && main_ui -> simulation_loaded);
	
	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> new_menu), main_ui -> ihm_active);
	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> open_menu), main_ui -> ihm_active);
	gtk_widget_set_sensitive (GTK_WIDGET (main_ui -> save_menu), main_ui -> ihm_active);
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
}

void on_simulate_button_clicked (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	PtrMainUI main_ui = (PtrMainUI) data;
	
	g_debug ("on_simulate_button_clicked");
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
	
	g_debug ("on_open_menu_activate");
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
