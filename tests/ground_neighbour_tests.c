#include "debug.h"
#include "test.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_neighbour.h"

/* Prototypes des fonctions de test */
void ground_neighbour_create_destroy_tests ();
void ground_neighbour_calculate_direction_test ();
void ground_neighbour_calculate_distance_test ();
void ground_neighbour_get_set_neighbour_tests ();
void ground_neighbour_insert_neighbour_test ();

int main (void)
{
	ground_neighbour_create_destroy_tests();
	ground_neighbour_calculate_direction_test();
	ground_neighbour_calculate_distance_test();
	ground_neighbour_get_set_neighbour_tests();
	ground_neighbour_insert_neighbour_test();
	
	return 0;
}

/*!
 * \brief fonction de test de creation et de destruction d'un voisin
 */
void ground_neighbour_create_destroy_tests ()
{
	TEST_TITLE ("ground_neighbour_create_destroy_tests");
	PtrGround ground = NULL, ground_voisin1 = NULL;
	ground_create (&ground);
	ground_set_position_X (ground, 100);
	ground_set_position_Y (ground, 100);
	ground_set_width (ground, 50);
	ground_set_length (ground, 50);
	
	ground_create (&ground_voisin1);
	ground_set_position_X (ground_voisin1, 150);
	ground_set_position_Y (ground_voisin1, 100);
	ground_set_width (ground_voisin1, 50);
	ground_set_length (ground_voisin1, 50);
	
	PtrGroundNeighbour ground_neighbour = NULL;
	
	ground_neighbour_create (&ground_neighbour, ground, ground_voisin1);
	TEST (ground_neighbour != NULL);
	
	ground_neighbour_destroy (&ground_neighbour);
	TEST (ground_neighbour == NULL);
	
	ground_destroy (&ground);
	ground_destroy (&ground_voisin1);
	
}

/*!
 * \brief Teste la methode privé de calcul de direction entre 2 terrains
 */
void ground_neighbour_calculate_direction_test ()
{
	TEST_TITLE ("ground_neighbour_calculate_direction_test");
	
	PtrGround ground = NULL, ground_voisin = NULL;
	ground_create (&ground);
	ground_set_position_X (ground, 100);
	ground_set_position_Y (ground, 100);
	ground_set_width (ground, 50);
	ground_set_length (ground, 50);
	
	ground_create (&ground_voisin);
	ground_set_position_X (ground_voisin, 150);
	ground_set_position_Y (ground_voisin, 150);
	ground_set_width (ground_voisin, 50);
	ground_set_length (ground_voisin, 50);
	
	PtrGroundNeighbour ground_neighbour = NULL;
	ground_neighbour_create (&ground_neighbour, ground, ground_voisin);
	
	ground_neighbour_calculate_direction (ground_neighbour);
	double direction = ground_neighbour_get_direction (ground_neighbour);
	DEBUG_IF ((direction >= 134.9 && direction <= 135.1) == 0, "%f", direction);
	TEST (direction >= 134.9 && direction <= 135.1);
	
	
	ground_neighbour_destroy (&ground_neighbour);
	ground_destroy (&ground);
	ground_destroy (&ground_voisin);
}

void ground_neighbour_calculate_distance_test ()
{
	TEST_TITLE ("ground_neighbour_calculate_distance_test");
	
	PtrGround ground = NULL, ground_voisin = NULL;
	ground_create (&ground);
	ground_set_position_X (ground, 100);
	ground_set_position_Y (ground, 100);
	ground_set_width (ground, 50);
	ground_set_length (ground, 50);
	
	ground_create (&ground_voisin);
	ground_set_position_X (ground_voisin, 150);
	ground_set_position_Y (ground_voisin, 100);
	ground_set_width (ground_voisin, 50);
	ground_set_length (ground_voisin, 50);
	
	PtrGroundNeighbour ground_neighbour = NULL;
	ground_neighbour_create (&ground_neighbour, ground, ground_voisin);
	
	ground_neighbour_calculate_distance (ground_neighbour);
	double distance = ground_neighbour_get_distance (ground_neighbour);
	DEBUG_IF (distance != 50.0, "%f", distance);
	TEST (distance == 50.0);
	
	ground_neighbour_destroy (&ground_neighbour);
	ground_destroy (&ground);
	ground_destroy (&ground_voisin);
}

void ground_neighbour_get_set_neighbour_tests ()
{
	TEST_TITLE ("ground_neighbour_get_set_neighbour_tests");
	
	PtrGround ground = NULL, ground_voisin1 = NULL, ground_voisin2 = NULL;
	ground_create (&ground);
	ground_set_position_X (ground, 100);
	ground_set_position_Y (ground, 100);
	ground_set_width (ground, 50);
	ground_set_length (ground, 50);
	
	ground_create (&ground_voisin1);
	ground_set_position_X (ground_voisin1, 150);
	ground_set_position_Y (ground_voisin1, 100);
	ground_set_width (ground_voisin1, 50);
	ground_set_length (ground_voisin1, 50);
	
	ground_create (&ground_voisin2);
	ground_set_position_X (ground_voisin2, 150);
	ground_set_position_Y (ground_voisin2, 150);
	ground_set_width (ground_voisin2, 50);
	ground_set_length (ground_voisin2, 50);
	
	PtrGroundNeighbour ground_neighbour1 = NULL, ground_neighbour2 = NULL;
	ground_neighbour_create (&ground_neighbour1, ground, ground_voisin1);
	ground_neighbour_create (&ground_neighbour2, ground, ground_voisin2);
	
	PtrGroundNeighbour ground_neighbour_stored = NULL;
	ground_neighbour_stored = ground_neighbour_get_next (ground_neighbour1);
	TEST (ground_neighbour_stored == NULL);
	
	ground_neighbour_set_next (ground_neighbour1, ground_neighbour2);
	ground_neighbour_stored = ground_neighbour_get_next (ground_neighbour1);
	TEST (ground_neighbour_stored == ground_neighbour2);
	
	ground_neighbour_destroy (&ground_neighbour1);
	
	ground_destroy (&ground);
	ground_destroy (&ground_voisin1);
	ground_destroy (&ground_voisin2);
}

void ground_neighbour_insert_neighbour_test ()
{
	TEST_TITLE ("ground_neighbour_insert_neighbour_test");
	
	PtrGround ground = NULL, ground_voisin1 = NULL, ground_voisin2 = NULL;
	ground_create (&ground);
	ground_set_position_X (ground, 100);
	ground_set_position_Y (ground, 100);
	ground_set_width (ground, 50);
	ground_set_length (ground, 50);
	
	ground_create (&ground_voisin1);
	ground_set_position_X (ground_voisin1, 150);
	ground_set_position_Y (ground_voisin1, 100);
	ground_set_width (ground_voisin1, 50);
	ground_set_length (ground_voisin1, 50);
	
	ground_create (&ground_voisin2);
	ground_set_position_X (ground_voisin2, 150);
	ground_set_position_Y (ground_voisin2, 150);
	ground_set_width (ground_voisin2, 50);
	ground_set_length (ground_voisin2, 50);
	
	PtrGroundNeighbour ground_neighbour1 = NULL, ground_neighbour2 = NULL;
	ground_neighbour_create (&ground_neighbour1, ground, ground_voisin1);
	ground_neighbour_create (&ground_neighbour2, ground, ground_voisin2);
	
	PtrGroundNeighbour list_ground_neighbour = NULL;
	list_ground_neighbour = ground_neighbour_insert (list_ground_neighbour, ground_neighbour1);
	list_ground_neighbour = ground_neighbour_insert (list_ground_neighbour, ground_neighbour2);
	
	TEST (list_ground_neighbour == ground_neighbour2);
	TEST (ground_neighbour_get_next (list_ground_neighbour) == ground_neighbour1);
	
	ground_neighbour_destroy (&list_ground_neighbour);
	
	ground_destroy (&ground);
	ground_destroy (&ground_voisin1);
	ground_destroy (&ground_voisin2);
}