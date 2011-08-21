#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "water_hmap.h"
#include "water_simulation_engine.h"
#include "water_rendering_engine.h"
#include "ui/main_ui.h"
#include "ui/main_builder.h"


/*!
 * \brief Cree une instance de Mainbuilder
 */
void main_builder_create (PtrMainBuilder *main_builder)
{
  assert (*main_builder == NULL);
  
  *main_builder = (PtrMainBuilder) malloc (sizeof (MainBuilder));
  memset (*main_builder, 0, sizeof (MainBuilder));
  
  //(*main_builder) -> Build = main_builder_build;
}

/*!
 * \brief Detruit une instance de MainBuilder
 */
void main_builder_destroy (PtrMainBuilder *main_builder)
{
  assert (*main_builder != NULL);
  
  free (*main_builder);
  *main_builder = NULL;
}

/*!
 * \brief assesseur du champs ui_repository_path
 */
void main_builder_set_ui_repository_path (PtrMainBuilder main_builder, char* ui_repository_path)
{
  assert (main_builder != NULL);
  assert (ui_repository_path != NULL);
  
  main_builder -> ui_repository_path = ui_repository_path;
}

/*!
 * \brief Construit une fenetre main et retourne sa reference
 */
PtrMainUI main_builder_build (PtrMainBuilder main_builder)
{
  GtkBuilder *builder = NULL;
  GError *error = NULL;
  
  char main_path[255];
  memset(main_path, 0, sizeof (char) * 255);
  sprintf(main_path, "%s/main.glade", main_builder -> ui_repository_path);
  
  
  builder = gtk_builder_new();
  if (!gtk_builder_add_from_file (builder, main_path, &error))
  {
    g_warning ("Couldn't load builder file: %s", error -> message);
    g_error_free (error);
  }
  
  PtrMainUI main_ui = NULL;
  main_ui_create (&main_ui);
  
  main_ui -> window = GTK_WIDGET (gtk_builder_get_object (builder, "main"));
  main_ui -> drawing_area = GTK_DRAWING_AREA (gtk_builder_get_object (builder, "drawing_area"));
  main_ui -> status_bar = GTK_STATUSBAR (gtk_builder_get_object (builder, "status_bar"));
  
  gtk_builder_connect_signals (builder, (gpointer) main_ui);
  
  return main_ui;
}