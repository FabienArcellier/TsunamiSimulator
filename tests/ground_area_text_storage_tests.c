#include "test.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_text_storage.h"

/* Prototypes des fonctions de tests */
void ground_area_text_storage_write_file_tests ();
void ground_area_text_storage_read_file_tests ();
void ground_area_text_storage_write_file_with_content_tests ();
void ground_area_text_storage_read_file_with_content_tests ();

int main (void)
{
  ground_area_text_storage_write_file_tests();
  ground_area_text_storage_read_file_tests();
  ground_area_text_storage_write_file_with_content_tests();
  ground_area_text_storage_read_file_with_content_tests ();
  return 0;
}

/*! 
 * \brief Teste de la fonction ground_area_text_storage_write_file
 */
void ground_area_text_storage_write_file_tests ()
{
  TEST_TITLE ("ground_area_text_storage_write_file_tests");
  // Initialisation d'un jeu de donnee
  PtrGroundArea ground_area = NULL;
  ground_area_create (&ground_area, 1000, 1000);
  
  
  PtrGroundAreaTextStorage ground_area_text_storage = NULL;
  ground_area_text_storage_create (&ground_area_text_storage);
  
  char path_scenario[255] = "ground_area.txt";
  FILE *file = NULL;
  file = fopen (path_scenario, "w+");
  ground_area_text_storage_set_file (ground_area_text_storage, file);
  ground_area_text_storage_write_file (ground_area_text_storage, ground_area);
  ground_area_text_storage_destroy (&ground_area_text_storage);
  
  fclose (file);
}

void ground_area_text_storage_read_file_tests()
{
  TEST_TITLE ("ground_area_text_storage_read_file_tests");
  PtrGroundArea ground_area = NULL;
  
  PtrGroundAreaTextStorage ground_area_text_storage = NULL;
  ground_area_text_storage_create (&ground_area_text_storage);
  
  char path_scenario[255] = "ground_area.txt";
  FILE *file = NULL;
  file = fopen (path_scenario, "r");
  ground_area_text_storage_set_file (ground_area_text_storage, file);
  ground_area = ground_area_text_storage_read_file (ground_area_text_storage);
  ground_area_text_storage_destroy (&ground_area_text_storage);
  
  fclose (file);
  
  TEST (ground_area != NULL);
  TEST (ground_area -> width == 1000);
  TEST (ground_area -> length == 1000);
}

/*! 
 * \brief Teste de la fonction ground_area_text_storage_write_file
 */
void ground_area_text_storage_write_file_with_content_tests ()
{
  TEST_TITLE ("ground_area_text_storage_write_file_with_content_tests");
  // Initialisation d'un jeu de donnee
  PtrGroundArea ground_area = NULL;
  PtrGround ground = NULL;
  ground_area_create (&ground_area, 1000, 1000);
  ground = ground_area_get_ground (ground_area, 1, 1);
  ground_set_type (ground, ground_type_ground); 
  
  PtrGroundAreaTextStorage ground_area_text_storage = NULL;
  ground_area_text_storage_create (&ground_area_text_storage);
  
  char path_scenario[255] = "ground_area_with_content.txt";
  FILE *file = NULL;
  file = fopen (path_scenario, "w+");
  ground_area_text_storage_set_file (ground_area_text_storage, file);
  ground_area_text_storage_write_file (ground_area_text_storage, ground_area);
  ground_area_text_storage_destroy (&ground_area_text_storage);
  
  fclose (file);
}

void ground_area_text_storage_read_file_with_content_tests()
{
  TEST_TITLE ("ground_area_text_storage_read_file_with_content_tests");
  PtrGroundArea ground_area = NULL;
  
  PtrGroundAreaTextStorage ground_area_text_storage = NULL;
  ground_area_text_storage_create (&ground_area_text_storage);
  
  char path_scenario[255] = "ground_area_with_content.txt";
  FILE *file = NULL;
  file = fopen (path_scenario, "r");
  ground_area_text_storage_set_file (ground_area_text_storage, file);
  ground_area = ground_area_text_storage_read_file (ground_area_text_storage);
  ground_area_text_storage_destroy (&ground_area_text_storage);
  
  fclose (file);
  
  PtrGround ground = NULL;
  ground = ground_area_get_ground (ground_area, 1, 1);
  enum GROUND_TYPE type_ground = ground_get_type (ground);
  
  TEST (ground_area != NULL);
  TEST (ground_area -> width == 1000);
  TEST (ground_area -> length == 1000);
  TEST (type_ground == ground_type_ground);
}