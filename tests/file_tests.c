#include "debug.h"
#include "test.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"

/* Prototypes des fonctions de tests */
void get_filename_with_extension_tests ();

int main (void)
{
	get_filename_with_extension_tests ();
	return 0;
}

/*!
 * \brief Teste la fonction get_filename_with_extension
 */
void get_filename_with_extension_tests ()
{
	TEST_TITLE ("get_filename_with_extension_tests");
	
	char* filename = get_filename_with_extension ("/home/fabien.c");
	char* filename1 = get_filename_with_extension ("fabien.c");
	
	DEBUG_IF (!(strcmp (filename, "fabien.c") == 0), "%s", filename);
	TEST (strcmp (filename, "fabien.c") == 0);
	
	DEBUG_IF (!(strcmp (filename1, "fabien.c") == 0), "%s", filename1);
	TEST (strcmp (filename1, "fabien.c") == 0);
	
	free (filename);
	free (filename1);
}