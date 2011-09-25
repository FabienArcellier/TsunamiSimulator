#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_text_storage.h"
#include "ground_area_energy_map.h"
#include "ground_area_to_pixbuf_factory.h"

/* Prototypes des fonctions de test */
void ground_area_to_pixbuf_test ();

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	ground_area_to_pixbuf_test ();
}

void ground_area_to_pixbuf_test ()
{
	puts ("Chargement du terrain");
	
	FILE *ground_file = fopen ("ground.txt", "r");
	fscanf (ground_file, "[Terrain]\n");
	PtrGroundAreaTextStorage ground_area_text_storage = NULL;
	ground_area_text_storage_create (&ground_area_text_storage);
	ground_area_text_storage_set_file (ground_area_text_storage, ground_file);
	
	PtrGroundArea ground_area = NULL;
	ground_area = ground_area_text_storage_read_file (ground_area_text_storage);
	ground_area_text_storage_destroy (&ground_area_text_storage);
	fclose (ground_file);
	
	GdkPixbuf* picture = ground_area_to_pixbuf (ground_area);
	gdk_pixbuf_save (picture, "ground.png", "png", NULL, NULL);
}