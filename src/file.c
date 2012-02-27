#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

/*!
* \brief Saute les commentaires (ligne commencant par #)
*/
void jump_over_commentary_sharp (FILE *file)
{
	assert (file != NULL);
	long file_init_position = ftell (file);
	
	while (fgetc (file) == '#')
	{
		while(fgetc (file) != '\n')
		{
		}
		file_init_position = ftell (file);
	}
	
	fseek (file, file_init_position, SEEK_SET);
	return;
}

/*!
 * \brief retourne le nom du fichier charge
 * 
 * La liberation de la memoire est à votre charge
 */
char* get_filename_with_extension (char path[])
{
	assert (path != NULL);
	int longueur = strlen (path);
	int i = 0;
	
	for (i = longueur; i >= 0 && path[i] != '\\' && path[i] != '/'; i--)
	{
	}
	
	char* filename = (char*) malloc ((longueur - i) * sizeof (char));
	
	strcpy (filename, &(path[i + 1]));
	return filename;
}