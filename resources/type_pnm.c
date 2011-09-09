#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "debug.h"

#define PROFONDEUR_MAX 10000
#define HAUTEUR_MAX 4000
#define NB_COLOR 255
#define GROUND_WIDTH 100
#define GROUND_LENGTH 100

int main (int argc, char *argv[])
{
	DEBUG_IF (1, "%d", argc);
	if (argc == 1)
	{
		printf ("Saisissez le nom d'une image pnm\n");
		return 1;
	}
	
	char path_image[255];
	char path_ground[255];
	char type[2];
	strcpy (path_image, argv[1]);
	strcpy (path_ground, argv[2]);
	DEBUG_IF (1, "%s", path_image);
	DEBUG_IF (1, "%s", path_ground);
	
	FILE *file = NULL, *file_ground = NULL;
	file = fopen (path_image, "r");
	file_ground = fopen (path_ground, "w");
	
	fscanf (file, "%s", type);
	if (strcmp (type, "P2"))
	{
		printf("Type de fichier invalide");
	}
	
	int array_width = 0, array_length = 0;
  char poubelle[255];
  fgets (poubelle, 255, file);
  fgets (poubelle, 255, file);
	fscanf (file, "%d %d", &array_width, &array_length);
	
	int i = 0, size = array_width *array_length;
	
	fprintf (file_ground, "P2\n");
	fprintf (file_ground,  "%d %d\n", array_width, array_length);
  fprintf (file_ground,  "%d\n", 255);
	
	for (i = 0; i < size; i++)
	{
		int grey_intensity = 0;
		fscanf (file, "%d", &grey_intensity);
		assert (grey_intensity >= 0 && grey_intensity < 256);
		
		int hauteur = (int) ((((PROFONDEUR_MAX + HAUTEUR_MAX) * grey_intensity) / NB_COLOR) - PROFONDEUR_MAX);
		int color = 0;
		if (hauteur < 0)
		{
			color = 0;
		}
		else
		{
			color = 255;
		}
		
		fprintf (file_ground,
						 "%d\n",
						 color);
	}
	
	fclose (file);
	fclose (file_ground);
	
	return 0;
}