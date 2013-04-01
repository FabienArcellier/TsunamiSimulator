#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

/* Your includes */
#include "debug.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_map_navigator.h"
#include "ground_area_to_pixbuf_factory.h"
#include "event.h"
#include "timeline.h"
#include "simulation.h"

#include "ui/simulate_ui.h"
#include "ui/simulate_ui_private.h" // Gestion des events

/*!
 * \brief Cree une instance SimulateUI
 */
void simulate_ui_create (PtrSimulateUI *simulate_ui, PtrSimulation simulation)
{
	assert (*simulate_ui == NULL);
	assert (simulation != NULL);
	
	*simulate_ui = (PtrSimulateUI) malloc ( sizeof (SimulateUI));
	if (*simulate_ui == NULL)
	{
		g_error ("SimulateUI memory allocation failed");
	}
	
	memset (*simulate_ui, 0, sizeof (SimulateUI));
	
	// Chargement de l'interface
	GError* error = NULL;
	GtkBuilder* builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, "ui/simulate.glade", &error))
	{
		g_warning ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}
	
	// Chargement des objets
	(*simulate_ui )-> window = GTK_WINDOW (gtk_builder_get_object (builder, "window"));
	(*simulate_ui )-> menu_close = GTK_MENU_ITEM (gtk_builder_get_object (builder, "menu_close"));
	(*simulate_ui )-> menu_speed_normal = GTK_MENU_ITEM (gtk_builder_get_object (builder, "menu_speed_normal"));
	(*simulate_ui )-> menu_speed_lent = GTK_MENU_ITEM (gtk_builder_get_object (builder, "menu_speed_lent"));
	(*simulate_ui )-> drawingarea = GTK_DRAWING_AREA (gtk_builder_get_object (builder, "drawingarea"));
	(*simulate_ui )-> time = GTK_HSCALE (gtk_builder_get_object (builder, "time"));
	(*simulate_ui )-> button_play = GTK_BUTTON (gtk_builder_get_object (builder, "button_play"));
	(*simulate_ui )-> button_pause = GTK_BUTTON (gtk_builder_get_object (builder, "button_pause"));
	(*simulate_ui )-> button_stop = GTK_BUTTON (gtk_builder_get_object (builder, "button_stop"));
	(*simulate_ui )-> button_previous = GTK_BUTTON (gtk_builder_get_object (builder, "button_previous"));
	(*simulate_ui )-> button_next = GTK_BUTTON (gtk_builder_get_object (builder, "button_next"));
	(*simulate_ui )-> time_adjustment = GTK_ADJUSTMENT (gtk_builder_get_object (builder, "time_adjustment"));
	
	gtk_builder_connect_signals (builder, (*simulate_ui)); 
	
	g_signal_connect ((*simulate_ui )-> drawingarea, "expose_event", G_CALLBACK (simulate_ui_expose_drawingarea), (*simulate_ui));
	
	(*simulate_ui) -> frame_speed = 2;
	(*simulate_ui) -> frame_state = frame_state_stop;
	(*simulate_ui) -> simulation = simulation;
	
	// Configurer la taille du drawing area en fonction de ground_area
	PtrGroundArea ground_area = simulation_get_ground_area (simulation);
	int width = ground_area_get_array_width (ground_area);
	int length = ground_area_get_array_length (ground_area);
	gtk_widget_set_size_request (GTK_WIDGET((*simulate_ui) -> drawingarea), width, length);
	
	// Configurer la barre time
	PtrTimeline timeline = simulation_get_timeline (simulation);
	gtk_adjustment_set_upper ((*simulate_ui )-> time_adjustment, (double) (timeline_get_final_time (timeline) - 1));
	simulate_ui_refresh_time (*simulate_ui );
	
	// Afficher la premiere image
	simulate_ui_refresh_current_ground_area (*simulate_ui);
	
	(*simulate_ui) -> tick_timeout = g_timeout_add (500, simulate_ui_tick_timeout, (*simulate_ui));
	simulate_ui_refresh_ihm_states ((*simulate_ui ));
	
	assert ((*simulate_ui )-> window != NULL);
}

/*!
 * \brief Detruit une instance SimulateUI
 */
void simulate_ui_destroy (PtrSimulateUI *simulate_ui)
{
	assert (*simulate_ui != NULL );
	
	GSource *timeout = g_main_context_find_source_by_id (NULL, (*simulate_ui) -> tick_timeout);
	g_source_destroy (timeout);
	free (*simulate_ui);
	*simulate_ui = NULL;
}

/*!
 * \brief Affiche la fenetre de l'IHM
 */
void simulate_ui_show (PtrSimulateUI simulate_ui)
{
	assert (simulate_ui != NULL);
	assert (simulate_ui -> window != NULL);
	
	gtk_widget_show_all (GTK_WIDGET (simulate_ui -> window));
}

/*!
 * \brief Cache la fenetre de l'IHM
 */
void simulate_ui_hide (PtrSimulateUI simulate_ui)
{
	assert (simulate_ui != NULL);
	assert (simulate_ui -> window != NULL);
	
	gtk_widget_hide (GTK_WIDGET (simulate_ui -> window));
}

/*!
 * \brief Affecte à chaque widget les attributs qu'il doit avoir selon les etats de l'objet
 */
void simulate_ui_refresh_ihm_states (PtrSimulateUI simulate_ui)
{
	assert (simulate_ui != NULL);
	
	PtrSimulation simulation = simulate_ui_get_simulation (simulate_ui);
	PtrTimeline timeline = simulation_get_timeline (simulation);
	int time_total = timeline_get_final_time (timeline);
	
	int play_state = simulate_ui -> frame_state != frame_state_play &&
		simulate_ui -> frame_position <= time_total;
	gtk_widget_set_sensitive (GTK_WIDGET(simulate_ui -> button_play), play_state);
		
	int pause_state = simulate_ui -> frame_state == frame_state_play &&
		simulate_ui -> frame_position <= time_total;
	gtk_widget_set_sensitive (GTK_WIDGET(simulate_ui -> button_pause), pause_state);
	
	int stop_state =  simulate_ui -> frame_state != frame_state_stop;
	gtk_widget_set_sensitive (GTK_WIDGET(simulate_ui -> button_stop), stop_state);
	
	gtk_widget_set_sensitive (GTK_WIDGET(simulate_ui -> button_previous), simulate_ui -> frame_position > 0);
	gtk_widget_set_sensitive (GTK_WIDGET(simulate_ui -> button_next), simulate_ui -> frame_position < time_total - 1);
}

/*!
 * \brief Assesseur en lecture de l'attribut window
 */
GtkWindow* simulate_ui_get_window (PtrSimulateUI simulate_ui)
{
	assert (simulate_ui != NULL);
	
	return (simulate_ui -> window);
}

/* Your methods */

void simulate_ui_refresh_current_ground_area (PtrSimulateUI simulate_ui)
{
	assert (simulate_ui != NULL);
	if (simulate_ui -> pixbuf_result != NULL)
	{
		g_object_unref (simulate_ui -> pixbuf_result);
	}
	
	
	PtrSimulation simulation = simulate_ui_get_simulation (simulate_ui);
	PtrGroundArea ground_area = simulation_get_ground_area (simulation);
	GdkPixbuf* pixbuf = ground_area_to_pixbuf (ground_area);
	PtrGroundAreaEnergyMapNavigator energy_map_navigator = simulation_get_energy_map_navigator (simulation);
	PtrGroundAreaEnergyMap energy_map = ground_area_energy_map_navigator_get_current (energy_map_navigator);
	pixbuf = ground_area_energy_map_to_pixbuf (pixbuf, energy_map);
	
	simulate_ui -> pixbuf_result = pixbuf;
	
	GDK_THREADS_ENTER ();
	gtk_widget_queue_draw (GTK_WIDGET(simulate_ui -> drawingarea));
	GDK_THREADS_LEAVE ();
}

void simulate_ui_refresh_time (PtrSimulateUI simulate_ui)
{
	gtk_adjustment_set_value (simulate_ui -> time_adjustment, (double) (simulate_ui -> frame_position));
	PtrSimulation simulation = simulate_ui_get_simulation (simulate_ui);
	PtrGroundAreaEnergyMapNavigator map_navigator = simulation_get_energy_map_navigator (simulation);
	
	int result = ground_area_energy_map_navigator_move_position (map_navigator, simulate_ui -> frame_position);
	DEBUG_IF (!(result == 1), "%d", result);
	DEBUG_IF (!(result == 1), "%d", simulate_ui -> frame_position);
	assert (result == 1);
}

/*!
 * \brief Expose callback for the drawing area
 */
gint simulate_ui_expose_drawingarea (GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	assert (data != NULL);
	PtrSimulateUI simulate_ui = (PtrSimulateUI) data;
	
	cairo_t *cr = NULL;
  
  cr = gdk_cairo_create (event->window);
  
  gdk_cairo_set_source_pixbuf (cr, simulate_ui -> pixbuf_result, 0, 0);
  gdk_cairo_rectangle (cr, &event->area);
  cairo_fill (cr);
  cairo_destroy (cr);
  
  return TRUE;
}



/* Events */

void simulate_ui_on_window_destroy (GtkWidget* widget, gpointer data)
{
	assert (data != NULL);
	PtrSimulateUI simulate_ui = (PtrSimulateUI) data;
	
	g_debug ("on_window_destroy");
}

void simulate_ui_on_menu_close_activate (GtkWidget *widget, gpointer data)
{
	assert (data != NULL);
	PtrSimulateUI simulate_ui = (PtrSimulateUI) data;
	
	g_debug ("simulate_ui_on_menu_close_activate");
}

void simulate_ui_on_menu_speed_normal_activate (GtkWidget *widget, gpointer data)
{
	assert (data != NULL);
	PtrSimulateUI simulate_ui = (PtrSimulateUI) data;
	
	simulate_ui -> frame_speed = 2;
	g_debug ("simulate_ui_on_menu_speed_normal_activate");
}

void simulate_ui_on_menu_speed_lent_activate (GtkWidget *widget, gpointer data)
{
	assert (data != NULL);
	PtrSimulateUI simulate_ui = (PtrSimulateUI) data;
	
	simulate_ui -> frame_speed = 10;
	g_debug ("simulate_ui_on_menu_speed_lent_activate");
}

void simulate_ui_on_button_play_activate (GtkWidget *widget, gpointer data)
{
	assert (data != NULL);
	PtrSimulateUI simulate_ui = (PtrSimulateUI) data;
	
	simulate_ui -> frame_state = frame_state_play;
	simulate_ui -> tick = 0;
	simulate_ui_refresh_ihm_states(simulate_ui);
	g_debug ("simulate_ui_on_button_play_activate");
}

void simulate_ui_on_button_pause_activate (GtkWidget *widget, gpointer data)
{
	assert (data != NULL);
	PtrSimulateUI simulate_ui = (PtrSimulateUI) data;
	
	simulate_ui -> frame_state = frame_state_pause;
	simulate_ui_refresh_ihm_states(simulate_ui);
	g_debug ("simulate_ui_on_button_pause_activate");
}

void simulate_ui_on_button_stop_activate (GtkWidget *widget, gpointer data)
{
	assert (data != NULL);
	PtrSimulateUI simulate_ui = (PtrSimulateUI) data;
	
	simulate_ui -> frame_state = frame_state_stop;
	simulate_ui -> frame_position = 0;
	simulate_ui_refresh_time (simulate_ui);
	simulate_ui_refresh_current_ground_area (simulate_ui);
	
	simulate_ui_refresh_ihm_states(simulate_ui);
	g_debug ("simulate_ui_on_button_stop_activate");
}

void simulate_ui_on_button_previous_activate (GtkWidget *widget, gpointer data)
{
	assert (data != NULL);
	PtrSimulateUI simulate_ui = (PtrSimulateUI) data;
	
	simulate_ui -> frame_position -= 1;
	simulate_ui_refresh_ihm_states (simulate_ui);
	simulate_ui_refresh_time (simulate_ui);
	simulate_ui_refresh_current_ground_area (simulate_ui);
	
	g_debug ("simulate_ui_on_button_previous_activate");
}

void simulate_ui_on_button_next_activate (GtkWidget *widget, gpointer data)
{
	assert (data != NULL);
	PtrSimulateUI simulate_ui = (PtrSimulateUI) data;
	simulate_ui -> frame_position += 1;
	simulate_ui_refresh_ihm_states (simulate_ui);
	simulate_ui_refresh_time (simulate_ui);
	simulate_ui_refresh_current_ground_area (simulate_ui);
	
	g_debug ("simulate_ui_on_button_next_activate");
}

void simulate_ui_on_time_value_changed (GtkWidget *widget, gpointer data)
{
	assert (data != NULL);
	PtrSimulateUI simulate_ui = (PtrSimulateUI) data;
	
	double frame_position_f = gtk_adjustment_get_value (simulate_ui -> time_adjustment);
	
	simulate_ui -> frame_position = (int) frame_position_f;
	simulate_ui_refresh_ihm_states (simulate_ui);
	simulate_ui_refresh_time (simulate_ui);
	simulate_ui_refresh_current_ground_area (simulate_ui);
	
	g_debug ("simulate_ui_on_time_value_changed");
}

gint simulate_ui_tick_timeout (gpointer data)
{
	assert (data != NULL);
	PtrSimulateUI simulate_ui = (PtrSimulateUI) data;
	PtrSimulation simulation = simulate_ui_get_simulation (simulate_ui);
	PtrTimeline timeline = simulation_get_timeline (simulation);
	
	if (simulate_ui -> frame_position == timeline_get_final_time (timeline))
	{
		simulate_ui -> frame_state = frame_state_stop;
		simulate_ui -> frame_position = 0;
		simulate_ui_refresh_time (simulate_ui);
		simulate_ui_refresh_current_ground_area (simulate_ui);
		simulate_ui_refresh_ihm_states(simulate_ui);
	}
	else if (simulate_ui -> tick % simulate_ui -> frame_speed == 0 &&
		simulate_ui -> frame_state == frame_state_play &&
		simulate_ui -> frame_position < timeline_get_final_time (timeline))
	{
		simulate_ui -> tick = 0;
		simulate_ui -> frame_position += 1;
		simulate_ui_refresh_ihm_states (simulate_ui);
		simulate_ui_refresh_time (simulate_ui);
		
		simulate_ui_refresh_current_ground_area (simulate_ui);
		
		g_debug ("simulate_ui_tick_timeout");
	}
	
	simulate_ui -> tick += 1;
	
	return TRUE;
}

/*!
 * \brief Assesseur en lecture de l'attribut simulate
 */
PtrSimulation simulate_ui_get_simulation (PtrSimulateUI simulate_ui)
{
	assert (simulate_ui != NULL);
	return simulate_ui -> simulation;
}