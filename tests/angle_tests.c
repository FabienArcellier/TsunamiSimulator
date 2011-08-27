#include "test.h"
#include "angle.h"

/* Prototypes des fonctions de tests */
void angle_shortener_rotation_tests ();

int main (void)
{
	angle_shortener_rotation_tests ();
}

void angle_shortener_rotation_tests ()
{
	TEST_TITLE ("angle_shortener_rotation_tests");
	
	TEST (angle_shortener_rotation (10.0, 335.0) == -35.0);
	TEST (angle_shortener_rotation (10.0, 5.0) == -5.0);
	TEST (angle_shortener_rotation (10.0, 100.0) == 90.0);
}