#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "water_hmap.h"
#include "water_simulation_engine.h"
#include "water_rendering_engine.h"
#include "point_water_transformation.h"
#include "ui/main_ui.h"

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
}

/*!
 * \brief Detruit une instance MainUI
 */
void main_ui_destroy (PtrMainUI *main_ui)
{
  assert (*main_ui != NULL);
  
  free (*main_ui);
  *main_ui = NULL;
}

void on_main_destroy (GtkWidget* window)
{
  g_debug ("on_main_destroy triggs");
}

void on_menu_file_action_quit_activate (GtkMenuItem* menu_file_action_quit, PtrMainUI main_ui)
{
  g_debug ("on_menu_file_action_quit_activate triggs");
  
  gtk_widget_destroy(GTK_WIDGET (main_ui -> window));
}

gboolean on_drawing_area_button_press_event (GtkDrawingArea* drawing_area, GdkEventButton *event, PtrMainUI main_ui)
{
  //g_message ("on_drawing_area_button_press_event triggs button :%d", event -> button);
  
  if (event->button == 1)
  {
    PtrWaterSimulationEngine water_simulation_engine = main_ui -> water_simulation_engine;
    PtrPointWaterTransformation point_water_transformation = NULL;
    point_water_transformation_create (&point_water_transformation);
    point_water_transformation_set_water_height (point_water_transformation, 100000000);
    point_water_transformation_set_application_point (point_water_transformation, event -> x, event -> y);
    point_water_transformation -> Apply (point_water_transformation, water_simulation_engine);
    point_water_transformation_destroy (&point_water_transformation);
    
    return TRUE;
  }
  
  return FALSE;
}

gboolean on_drawing_area_expose_event (GtkDrawingArea *drawing_area, GdkEventExpose *event, PtrMainUI main_ui)
{
  //g_message ("on_drawing_area_expose_event triggs");
  
  cairo_t *cr = NULL;
  GdkPixbuf *frame = NULL;
  
  cr = gdk_cairo_create(event->window);
  frame = water_rendering_engine_get_frame(main_ui -> water_rendering_engine);
  gdk_cairo_set_source_pixbuf (cr, frame, 0, 0);
  gdk_cairo_rectangle(cr, &event->area);
  cairo_fill (cr);
  
  cairo_destroy (cr);
  
  return TRUE;
}

/*!
 * \brief Retourne la frame avant le rendu de l'eau
 */
GdkPixbuf* main_ui_get_frame_before_water_rendering (PtrMainUI main_ui)
{
  assert (main_ui != NULL);
  return main_ui -> frame_before_water_rendering;
}

/*!
 * \brief Enregistre la frame avant le rendu de l'eau
 */
void main_ui_set_frame_before_water_rendering (PtrMainUI main_ui, GdkPixbuf* frame)
{
  assert (main_ui != NULL);
  main_ui -> frame_before_water_rendering = frame;
}

/*!
 * \brief Retourne la frame a afficher
 */
GdkPixbuf* main_ui_get_frame_to_display (PtrMainUI main_ui)
{
  assert (main_ui != NULL);
  return main_ui -> frame_to_display;
}

/*!
 * \brief Permet d'enregistrer la frame a afficher
 */
void main_ui_set_frame_to_display (PtrMainUI main_ui, GdkPixbuf* frame)
{
  assert (main_ui != NULL);
  main_ui -> frame_to_display = frame;
}

/*!
 * \brief Retourne le moteur de rendu de l'eau
 */
PtrWaterRenderingEngine main_ui_get_water_rendering_engine (PtrMainUI main_ui)
{
  assert (main_ui != NULL);
  return main_ui -> water_rendering_engine;
}

/*!
 * \brief Set le moteur de rendu de l'eau
 */
void main_ui_set_water_rendering_engine (PtrMainUI main_ui, PtrWaterRenderingEngine water_rendering_engine)
{
  assert (main_ui != NULL);
  main_ui -> water_rendering_engine = water_rendering_engine;
}

/*!
 * \brief Retourne le moteur de simulation
 */
PtrWaterSimulationEngine main_ui_get_water_simulation_engine (PtrMainUI main_ui)
{
  assert (main_ui != NULL);
  return main_ui -> water_simulation_engine;
}

/*!
 * \brief Set le moteur de simulation de l'eau
 */
void main_ui_set_water_simulation_engine (PtrMainUI main_ui, PtrWaterSimulationEngine water_simulation_engine)
{
  assert (main_ui != NULL);
  main_ui -> water_simulation_engine = water_simulation_engine;
}