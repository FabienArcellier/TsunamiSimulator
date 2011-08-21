#include <gtk/gtk.h>
#include "colored_pixbuf_factory.h"
#include "water_hmap.h"
#include "water_simulation_engine.h"
#include "water_rendering_engine.h"
#include "point_water_transformation.h"
#include "ui/main_ui.h"
#include "ui/main_builder.h"

#define DRAWING_AREA_WIDTH 200
#define DRAWING_AREA_HEIGHT 200
#define FRAME_DELAY 50
#define UI_GLADE "ui"

static void main_destroy (GtkWidget *window, gpointer data);

static void init_frame_before_water_rendering (PtrMainUI);
static void init_water_rendering_engine (PtrMainUI);
static void init_water_simulation_engine (PtrMainUI);

static gint refresh_simulation_state (gpointer);

int main (int argc, char *argv[])
{
  gtk_init (&argc, &argv);
  
  PtrMainBuilder main_builder = NULL;
  PtrMainUI main_ui = NULL;
  
  main_builder_create (&main_builder);
  main_builder_set_ui_repository_path (main_builder, UI_GLADE);
  main_ui = main_builder_build (main_builder);
  
  g_signal_connect (G_OBJECT (main_ui -> window), "destroy", G_CALLBACK(main_destroy), NULL);
  
  init_frame_before_water_rendering (main_ui);
  init_water_rendering_engine (main_ui);
  init_water_simulation_engine (main_ui);
  
  g_timeout_add (FRAME_DELAY, refresh_simulation_state, (gpointer) main_ui);
  
  gtk_widget_show_all (main_ui -> window);
  
  gtk_main();
  return 0;
}

static void init_frame_before_water_rendering (PtrMainUI main_ui)
{
  /* Construit l'image initiale */
  PtrColoredPixbufFactory factory = NULL;
  colored_pixbuf_factory_create(&factory);
  factory -> width = DRAWING_AREA_WIDTH;
  factory -> height = DRAWING_AREA_HEIGHT;
  factory -> red = 128;
  factory -> blue = 128;
  factory -> green = 128;
  GdkPixbuf* frame = colored_pixbuf_factory_instanciate(factory);
  GdkPixbuf* frame_to_display = colored_pixbuf_factory_instanciate(factory);
  colored_pixbuf_factory_destroy(&factory);
  
  main_ui_set_frame_before_water_rendering (main_ui, frame);
  main_ui_set_frame_to_display (main_ui, frame_to_display);
}

static void init_water_rendering_engine (PtrMainUI main_ui)
{
  PtrWaterRenderingEngine water_rendering_engine = NULL;
  water_rendering_engine_create (&water_rendering_engine);
  
  main_ui_set_water_rendering_engine (main_ui, water_rendering_engine);
}

static void init_water_simulation_engine (PtrMainUI main_ui)
{
  PtrWaterSimulationEngine water_simulation_engine = NULL;
  water_simulation_engine_create(&water_simulation_engine, DRAWING_AREA_WIDTH, DRAWING_AREA_HEIGHT);
  
  main_ui_set_water_simulation_engine (main_ui, water_simulation_engine);
}

static gint refresh_simulation_state (gpointer data)
{
  //g_debug ("refresh_simulation_state");
  PtrMainUI main_ui = (PtrMainUI) data;
  PtrWaterRenderingEngine water_rendering_engine = NULL;
  PtrWaterSimulationEngine water_simulation_engine = NULL;
  water_rendering_engine = main_ui_get_water_rendering_engine (main_ui);
  water_simulation_engine = main_ui_get_water_simulation_engine (main_ui);
  
  water_simulation_engine_set_next_hmap(water_simulation_engine);
  
  GdkPixbuf *frame_before_water_rendering = NULL, *frame_to_display = NULL;
  frame_before_water_rendering = main_ui_get_frame_before_water_rendering (main_ui);
  frame_to_display = main_ui_get_frame_to_display (main_ui);
  gdk_pixbuf_copy_area (frame_before_water_rendering, 0, 0, DRAWING_AREA_WIDTH, DRAWING_AREA_HEIGHT,frame_to_display, 0, 0);

  water_rendering_engine_set_water_hmap (water_rendering_engine, water_simulation_engine_get_current_hmap(water_simulation_engine));
  water_rendering_engine_set_frame (water_rendering_engine, frame_to_display);
  water_rendering_engine_rendering_water (water_rendering_engine);
  
  GtkDrawingArea* drawing_area = main_ui -> drawing_area;
  
  GDK_THREADS_ENTER ();
  gtk_widget_queue_draw (GTK_WIDGET(drawing_area));
  GDK_THREADS_LEAVE ();
  
  return TRUE;
}

static void main_destroy(GtkWidget *window, gpointer data)
{
  g_debug ("main_destroy triggs");
  gtk_main_quit();
}