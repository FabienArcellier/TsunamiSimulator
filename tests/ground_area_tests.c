#include "debug.h"
#include "test.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"

/* Prototypes des fonctions à tester */
void ground_area_create_destroy_tests();
void ground_area_get_ground_tests();

int main (void)
{
  ground_area_create_destroy_tests();
  ground_area_get_ground_tests();
  return 0;
}

/*!
 * \brief Verifie que la creation et la destruction d'un objet ground_area se fait correctement
 */
void ground_area_create_destroy_tests()
{
  TEST_TITLE ("ground_area_create_destroy_tests");
  
  PtrGroundArea ground_area = NULL;
  ground_area_create (&ground_area, 1000, 1000);
  
  TEST (ground_area -> array_width == 10);
  TEST (ground_area -> array_length == 10);
  TEST (&(ground_area -> area[99]) != NULL);
  
  ground_area_destroy (&ground_area);
  
  TEST (ground_area == NULL);
}

/*!
 * \brief  Teste le fonctionnement de la methode ground_area_get_ground
 */
void ground_area_get_ground_tests()
{
  TEST_TITLE ("ground_area_get_ground_tests");
  
  PtrGroundArea ground_area = NULL;
  PtrGround ground = NULL;
  ground_area_create (&ground_area, 1000, 1000);
  
  ground = ground_area_get_ground (ground_area, 9, 9);
  TEST (&(ground_area -> area[99]) == ground);
	TEST (ground_get_position_X (ground) == 900);
	DEBUG_IF (ground_get_position_X (ground) != 900, "%d", ground_get_position_X (ground));
	TEST (ground_get_position_Y (ground) == 900);
	DEBUG_IF (ground_get_position_Y (ground) != 900, "%d", ground_get_position_Y (ground));
  ground = ground_area_get_ground (ground_area, 0, 0);
  TEST (&(ground_area -> area[0]) == ground);
	TEST (ground_get_position_X (ground) == 0);
	TEST (ground_get_position_Y (ground) == 0);
  
}