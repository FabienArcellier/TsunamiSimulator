#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_builder.h"
#include "test.h"

/* Prototypes des fonctions de tests */
void ground_area_builder_create_destroy_test ();

int main (void)
{
	ground_area_builder_create_destroy_test();
}

void ground_area_builder_create_destroy_test ()
{
	TEST_TITLE ("ground_area_builder_create_destroy_test");
	TEST (1 == 1);
}