#include <assert.h>
#include <stdio.h>
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