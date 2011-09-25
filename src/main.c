#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "event.h"
#include "timeline.h"
#include "simulation.h"
#include "ui/main_ui.h"
#include "main.h"

int main (int argc, char *argv[])
{
	
	PtrMainStruct main_struct = NULL;
	main_create (&main_struct, argc, argv);
	main_application_start (main_struct);
	
	// Il manque la connexion du signal destroy sur la fenetre de main_ui
	
	return 0;
}

/*!
 * \brief Instancie un objet MainStruct
 */
void main_create (PtrMainStruct *main_struct, int argc, char **argv)
{
	assert (*main_struct == NULL);
	
	*main_struct = (PtrMainStruct) malloc (sizeof (MainStruct));
	memset (*main_struct, 0, sizeof (MainStruct));
	(*main_struct) -> argc = argc;
	(*main_struct) -> argv = argv;
}

/*!
 * \brief Detruit un objet MainStruct
 */
void main_destroy (PtrMainStruct *main_struct)
{
	assert (*main_struct != NULL);
	
	PtrMainUI main_ui = (*main_struct) -> main_ui;
	if (main_ui != NULL)
	{
		main_ui_destroy (&main_ui);
	}
	
	free (*main_struct);
}

/*!
 * \brief Demarre l'application et ouvre l'IHM
 */
void main_application_start (PtrMainStruct main_struct)
{
	assert (main_struct != NULL);
	int argc = main_struct -> argc;
	char **argv = main_struct -> argv;
	gtk_init (&argc, &argv);
	gtk_main ();
}

/*!
 * \brief Detruit les objets instanciés par main lors de la destruction de la fenetre principale
 */
void main_application_quit (PtrMainStruct main_struct, gpointer data)
{
	assert (main_struct != NULL);
	gtk_main_quit();
	main_destroy (&main_struct);
}

/*!
 * \brief Assesseur en lecture de l'attribut main_ui
 */
PtrMainUI main_get_main_ui (PtrMainStruct main_struct)
{
	assert (main_struct != NULL);
	
	return main_struct -> main_ui;
}
