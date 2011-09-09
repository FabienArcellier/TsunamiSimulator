#include <assert.h>
#include <string.h>
#include <gtk/gtk.h>
#include "wave_signal.h"
#include "debug.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_text_storage.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_text_storage.h"
#include "event.h"
#include "earthquake_event.h"
#include "earthquake_events_text_storage.h"
#include "timeline.h"
#include "propagation_timeline_processings.h"
#include "simulation.h"
#include "simulation_text_storage.h"

#define FRAME_DELAY 50
#define UI_GLADE "ui"

static PtrSimulation simulation = NULL;

typedef struct calculate_window
{
	GtkWindow *window;
	GtkButton *cancel_button;
	GtkProgressBar *progressbar;
	int cancel_operation;
} CalculateWindow;

static CalculateWindow calculate_window;

typedef struct simulate_window
{
	GtkWindow *window;
	GtkDrawingArea *drawingarea;
	GtkButton *play_button;
	GtkButton *pause_button;
	GtkButton *stop_button;
} SimulateWindow;

static SimulateWindow simulate_window;

typedef struct main_window
{
	GtkWindow *window;
	GtkMenuItem *open_menu;
	GtkMenuItem *save_menu;
	GtkMenuItem *quit;
	GtkButton *calculate_button;
	GtkButton *simulate_button;
	int file_open;
	int interface_locked;
	char filename[255];
} MainWindow;

static MainWindow main_window;

void init_main_window ();

static void main_window_destroy (GtkWidget *window, gpointer data);
static void calculate_window_destroy (GtkWidget *window, gpointer data);
static void simulate_window_destroy (GtkWidget *window, gpointer data);

void refresh_main_window (MainWindow* main_window);
void refresh_calculate_window (CalculateWindow* calculate_window);
void refresh_simulate_window (SimulateWindow* simulate_window);

void on_menu_file_action_quit_activate (GtkWidget*, MainWindow*);
void on_calculate_button_clicked (GtkWidget*, MainWindow*);
void on_simulate_button_clicked (GtkWidget*, MainWindow*);
void on_cancel_button_clicked (GtkWidget*, CalculateWindow*);

void on_open_menu_activate (GtkWidget*, MainWindow*);
void on_save_menu_activate (GtkWidget*, MainWindow*);

void on_main_show (GtkWidget*, MainWindow*);
void *calculate_simulation ();

int main (int argc, char *argv[])
{
  gtk_init (&argc, &argv);
	init_main_window ();
  
	gtk_widget_show_all (GTK_WIDGET(main_window.window));
  
  gtk_main();
  return 0;
}

void init_main_window ()
{
	GtkBuilder *builder = NULL;
  GError *error = NULL;
  char main_path[255];
  memset(main_path, 0, sizeof (char) * 255);
  sprintf(main_path, "%s/main.glade", UI_GLADE);
	
	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, main_path, &error))
  {
    g_warning ("Couldn't load builder file: %s", error -> message);
    g_error_free (error);
  }
  
  main_window.window = GTK_WINDOW (gtk_builder_get_object (builder, "main"));
	main_window.quit = GTK_MENU_ITEM (gtk_builder_get_object (builder, "menu_file_action_quit"));
	main_window.open_menu = GTK_MENU_ITEM (gtk_builder_get_object (builder, "open_menu"));
	main_window.save_menu = GTK_MENU_ITEM (gtk_builder_get_object (builder, "save_menu"));
	main_window.calculate_button = GTK_BUTTON (gtk_builder_get_object (builder, "calculate_button"));
	main_window.simulate_button = GTK_BUTTON (gtk_builder_get_object (builder, "simulate_button"));
	
	main_window.file_open = 0;
	main_window.interface_locked = 0;
	
	gtk_builder_connect_signals (builder, (gpointer) &main_window);
	g_signal_connect (G_OBJECT (main_window.window), "destroy", G_CALLBACK(main_window_destroy), NULL);
	
	refresh_main_window (&main_window);
}

void refresh_main_window (MainWindow* main_window_local)
{
	assert (main_window_local -> calculate_button != NULL);
	assert (main_window_local -> simulate_button != NULL);
	assert (main_window_local -> save_menu != NULL);
	assert (main_window_local -> open_menu != NULL);
	assert (main_window_local -> quit != NULL);
	
	
	if (main_window_local -> file_open == 0 || main_window_local -> interface_locked == 1)
	{
		gtk_widget_set_sensitive (GTK_WIDGET(main_window_local -> calculate_button), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET(main_window_local -> simulate_button), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET(main_window_local -> save_menu), FALSE);
	}
	else
	{
		gtk_widget_set_sensitive (GTK_WIDGET(main_window_local -> calculate_button), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET(main_window_local -> simulate_button), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET(main_window_local -> save_menu), TRUE);
	}
	
	if (main_window_local -> interface_locked == 1)
	{
		gtk_widget_set_sensitive (GTK_WIDGET(main_window_local -> open_menu), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET(main_window_local -> quit), FALSE);
	}
	else
	{
		gtk_widget_set_sensitive (GTK_WIDGET(main_window_local -> open_menu), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET(main_window_local -> quit), TRUE);
	}
}

void init_calculate_window ()
{
	GtkBuilder *builder = NULL;
  GError *error = NULL;
  char main_path[255];
  memset(main_path, 0, sizeof (char) * 255);
  sprintf(main_path, "%s/calculate.glade", UI_GLADE);
	
	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, main_path, &error))
  {
    g_warning ("Couldn't load builder file: %s", error -> message);
    g_error_free (error);
  }
  
  calculate_window.window = GTK_WINDOW (gtk_builder_get_object (builder, "main"));
	calculate_window.cancel_button = GTK_BUTTON (gtk_builder_get_object (builder, "cancel_button"));
	calculate_window.progressbar = GTK_PROGRESS_BAR (gtk_builder_get_object (builder, "progressbar"));
	
	gtk_builder_connect_signals (builder, (gpointer) &calculate_window);
	g_signal_connect (G_OBJECT (calculate_window.window), "destroy", G_CALLBACK(calculate_window_destroy), NULL);
	
	calculate_window.cancel_operation = 0;
	
	refresh_main_window (&main_window);
}

void init_simulate_window ()
{
	GtkBuilder *builder = NULL;
  GError *error = NULL;
  char main_path[255];
  memset(main_path, 0, sizeof (char) * 255);
  sprintf(main_path, "%s/simulate.glade", UI_GLADE);
	
	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, main_path, &error))
  {
    g_warning ("Couldn't load builder file: %s", error -> message);
    g_error_free (error);
  }
  
  simulate_window.window = GTK_WINDOW (gtk_builder_get_object (builder, "main"));
	simulate_window.drawingarea = GTK_DRAWING_AREA (gtk_builder_get_object (builder, "drawingarea"));
	simulate_window.play_button = GTK_BUTTON (gtk_builder_get_object (builder, "play_button"));
	simulate_window.pause_button = GTK_BUTTON (gtk_builder_get_object (builder, "pause_button"));
	simulate_window.stop_button = GTK_BUTTON (gtk_builder_get_object (builder, "stop_button"));
	
	gtk_builder_connect_signals (builder, (gpointer) &simulate_window);
	g_signal_connect (G_OBJECT (simulate_window.window), "destroy", G_CALLBACK(simulate_window_destroy), NULL);

}


static void main_window_destroy(GtkWidget *window, gpointer data)
{
  g_debug ("main_destroy triggs");
  gtk_main_quit();
}

static void calculate_window_destroy (GtkWidget *window, gpointer data)
{
	main_window.interface_locked = 0;
	refresh_main_window (&main_window);
}

static void simulate_window_destroy (GtkWidget *window, gpointer data)
{
	main_window.interface_locked = 0;
	refresh_main_window (&main_window);
}

void on_menu_file_action_quit_activate (GtkWidget *menu, MainWindow *main_window)
{
	gtk_widget_destroy (GTK_WIDGET (main_window -> window));
}

void on_calculate_button_clicked (GtkWidget *calculate_button, MainWindow *main_window_local)
{
	g_debug ("on_calculate_button_clicked");
	init_calculate_window ();
	main_window_local -> interface_locked = 1;
	refresh_main_window (main_window_local);
	
	gtk_widget_show_all (GTK_WIDGET (calculate_window.window));
	//calculate_simulation();
}

void on_simulate_button_clicked (GtkWidget *calculate_button, MainWindow *main_window_local)
{
	init_simulate_window ();
	main_window_local -> interface_locked = 1;
	refresh_main_window (main_window_local);
	
	gtk_widget_show_all (GTK_WIDGET (simulate_window.window));
}
 
void on_open_menu_activate (GtkWidget *widget, MainWindow *main_window_local)
{
	assert (main_window_local != NULL);
	g_debug ("on_open_menu_activate");
	
	GtkWidget *dialog = NULL;
  gchar *filename = NULL;
  
  dialog = gtk_file_chooser_dialog_new ("Open File ...",
                                        main_window_local -> window,
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
		PtrSimulationTextStorage simulation_text_storage = NULL;
		simulation_text_storage_create (&simulation_text_storage);
		simulation_text_storage_set_file (simulation_text_storage, file);
		simulation = simulation_text_storage_read_file (simulation_text_storage);
		simulation_text_storage_destroy (&simulation_text_storage);
		fclose (file);
		
		if (simulation != NULL)
		{
			strcpy(main_window_local -> filename, filename);
			main_window_local -> file_open = 1;
		}
		
		refresh_main_window (main_window_local);
  }
  else
	{
		refresh_main_window (main_window_local);
	}
	
  gtk_widget_destroy (dialog);
}

void on_save_menu_activate (GtkWidget *widget, MainWindow *main_window_local)
{
}

void on_cancel_button_clicked (GtkWidget *widget, CalculateWindow *calculate_window_local)
{
	calculate_window.cancel_operation = 1;
}

void calculate_simulation ()
{	
	PtrTimeline timeline = simulation_get_timeline (simulation);
	PtrGroundArea ground_area = simulation_get_ground_area (simulation);
	PtrGroundAreaEnergyMap ground_area_energy_map = simulation -> file_ground_area_energy_map;
	
	int final_time = timeline_get_final_time (timeline);
	gtk_progress_bar_set_activity_blocks (calculate_window.progressbar, final_time);
	
	while (timeline_get_current_time (timeline) < final_time && calculate_window.cancel_operation == 0)
	{
		register_events_for_propagation_on_timeline_from_ground_area (timeline,
																																	ground_area);
		timeline_execute_events (timeline);
		simplify_wave_signals_after_propagation_on_ground_area (ground_area);
		
		PtrGroundAreaEnergyMap ground_area_energy_map = NULL;
		ground_area_energy_map_create (&ground_area_energy_map, ground_area);
		
		gtk_progress_bar_get_pulse_step (calculate_window.progressbar);
		timeline_move_current_time (timeline, 1);
		simulation_set_push_energy_map (simulation, ground_area_energy_map);
		
		if (gtk_events_pending())
		{
			DEBUG_IF (1, "%s", "test");
			gtk_main_iteration();
		}
	}
	
	if (calculate_window.cancel_operation == 1)
	{
		while (simulation_energy_map_empty (simulation) == 0)
		{
			PtrGroundAreaEnergyMap energy_map = simulation_set_pop_energy_map (simulation);
			ground_area_energy_map_destroy (&energy_map);
		}
	}
	
	calculate_window.cancel_operation = 0;
}