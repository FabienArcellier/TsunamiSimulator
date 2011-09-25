#include "test.h"
#include "debug.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_map_navigator.h"

/* Prototypes des fonctions de tests */
void ground_area_energy_map_navigator_create_destroy_tests ();
void ground_area_energy_map_navigator_add_tests ();
void ground_area_energy_map_navigator_delete_tests ();

int main (void)
{
	ground_area_energy_map_navigator_create_destroy_tests ();
	ground_area_energy_map_navigator_add_tests ();
	ground_area_energy_map_navigator_delete_tests ();
	return 0;
}

void ground_area_energy_map_navigator_create_destroy_tests ()
{
	TEST_TITLE ("ground_area_energy_map_navigator_create_destroy_tests");
	
	PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator = NULL;
	ground_area_energy_map_navigator_create (&ground_area_energy_map_navigator);
	
	TEST (ground_area_energy_map_navigator != NULL);
	
	ground_area_energy_map_navigator_destroy (&ground_area_energy_map_navigator);
	TEST (ground_area_energy_map_navigator == NULL);
}

void ground_area_energy_map_navigator_add_tests ()
{
	TEST_TITLE ("ground_area_energy_map_navigator_add_tests");
	
	PtrGroundArea ground_area = NULL;
  ground_area_create (&ground_area, 1000, 1000);
	
	PtrGroundAreaEnergyMap map1 = NULL, map2 = NULL, map3 = NULL;
	ground_area_energy_map_create (&map1, ground_area);
	ground_area_energy_map_create (&map2, ground_area);
	ground_area_energy_map_create (&map3, ground_area);
	
	PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator = NULL;
	ground_area_energy_map_navigator_create (&ground_area_energy_map_navigator);
	
	TEST (ground_area_energy_map_navigator_get_count (ground_area_energy_map_navigator) == 0);
	
	ground_area_energy_map_navigator_add (ground_area_energy_map_navigator, map1);
	ground_area_energy_map_navigator_add (ground_area_energy_map_navigator, map2);
	ground_area_energy_map_navigator_add (ground_area_energy_map_navigator, map3);
	
	TEST (ground_area_energy_map_navigator_get_count (ground_area_energy_map_navigator) == 3);
	
	TEST (ground_area_energy_map_navigator -> first == map1);
	TEST (ground_area_energy_map_get_next (map1) == map2);
	TEST (ground_area_energy_map_get_next (map2) == map3);
	TEST (ground_area_energy_map_get_next (map3) == NULL);
}

void ground_area_energy_map_navigator_delete_tests ()
{
	TEST_TITLE ("ground_area_energy_map_navigator_delete_tests");
	
	PtrGroundArea ground_area = NULL;
  ground_area_create (&ground_area, 1000, 1000);
	
	PtrGroundAreaEnergyMap map1 = NULL, map2 = NULL, map3 = NULL;
	ground_area_energy_map_create (&map1, ground_area);
	ground_area_energy_map_create (&map2, ground_area);
	ground_area_energy_map_create (&map3, ground_area);
	
	PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator = NULL;
	ground_area_energy_map_navigator_create (&ground_area_energy_map_navigator);
	
	ground_area_energy_map_navigator_add (ground_area_energy_map_navigator, map1);
	ground_area_energy_map_navigator_add (ground_area_energy_map_navigator, map2);
	ground_area_energy_map_navigator_add (ground_area_energy_map_navigator, map3);
	TEST (ground_area_energy_map_navigator_get_count (ground_area_energy_map_navigator) == 3);
	
	ground_area_energy_map_navigator_delete (ground_area_energy_map_navigator, map1);
	ground_area_energy_map_destroy (&map1);
	ground_area_energy_map_navigator_delete (ground_area_energy_map_navigator, map3);
	ground_area_energy_map_destroy (&map3);
	
	DEBUG_IF (!(ground_area_energy_map_navigator -> first == map2), "%p", ground_area_energy_map_navigator -> first);
	TEST (ground_area_energy_map_navigator -> first == map2);
	TEST (ground_area_energy_map_get_next (map2) == NULL);
	TEST (ground_area_energy_map_navigator_get_count (ground_area_energy_map_navigator) == 1);
}