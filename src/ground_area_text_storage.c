#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_text_storage.h"

/*!
 * \brief Convertit le type du ground en chaine de caractere
 */
static void convert_ground_type_to_string (enum GROUND_TYPE, char*);

/*!
 * \brief Convertit une chaine de caractere vers le type ground
 */
static enum GROUND_TYPE convert_string_to_ground_type (char*);

/*!
 * \brief Saute les commentaires
 */
static void jump_over_commentary (FILE*);

/*!
 * \brief Cree une instance de l'objet GroundAreaTextStorage
 */
void ground_area_text_storage_create (PtrGroundAreaTextStorage *ground_area_text_storage)
{
  assert (*ground_area_text_storage == NULL);
  
  *ground_area_text_storage = (PtrGroundAreaTextStorage) malloc (sizeof (GroundAreaTextStorage));
  memset (*ground_area_text_storage, 0, sizeof (GroundAreaTextStorage));
  
  strcpy ((*ground_area_text_storage) -> datatype, GROUND_AREA_TEXT_STORAGE_DATATYPE);
  strcpy ((*ground_area_text_storage) -> version, GROUND_AREA_TEXT_STORAGE_VERSION);
}

/*!
 * \brief Detruit l'instance d'un objet GroundAreaTextStorage
 */
void ground_area_text_storage_destroy (PtrGroundAreaTextStorage *ground_area_text_storage)
{
  assert (*ground_area_text_storage != NULL);
  
  free (*ground_area_text_storage);
  *ground_area_text_storage = NULL;
}

/*!
 * \brief Permet de configurer le handle du fichier pour l'ecriture
 */
void ground_area_text_storage_set_file (PtrGroundAreaTextStorage ground_area_text_storage, FILE *file)
{
  assert (ground_area_text_storage != NULL);
  assert (file != NULL);
  
  ground_area_text_storage -> file = file;
}

/*!
 * \brief Lance l'ecriture du fichier
 */
void ground_area_text_storage_write_file (PtrGroundAreaTextStorage ground_area_text_storage, PtrGroundArea ground_area)
{
  assert (ground_area_text_storage != NULL);
  assert (ground_area_text_storage -> file != NULL);
  assert (ground_area != NULL);
  
  FILE* file = ground_area_text_storage -> file;
  
  fprintf (file,
           "datatype\t%s\tversion\t%s\n", 
           ground_area_text_storage -> datatype, 
           ground_area_text_storage -> version);
  fprintf (file,"# ground size in meter\n");
  fprintf (file,"width\t%d\n", ground_area -> width);
  fprintf (file,"length\t%d\n", ground_area -> length);
  
  int array_width = ground_area -> array_width;
  int array_length = ground_area -> array_length;
  
  fprintf (file, "#positionX\tpositionY\tHeight\n");
  
  int i = 0, j = 0;
  for (i = 0; i < array_width; i++)
  {
    for (j = 0; j < array_length; j++)
    {
      char type_string[32] = "";
      PtrGround ground = ground_area_get_ground (ground_area, i , j);
      enum GROUND_TYPE type = ground_get_type (ground);
      convert_ground_type_to_string (type, type_string);
      double height = ground_get_height (ground);
      
      fprintf (file, "%d\t%d\t%s\t%f\n", i, j, type_string, height);
    }
  }
  
  fprintf (file, "\n");  
}

/*!
 * \brief Lit le fichier
 */
PtrGroundArea ground_area_text_storage_read_file (PtrGroundAreaTextStorage ground_area_text_storage)
{
  assert (ground_area_text_storage != NULL);
  assert (ground_area_text_storage -> file != NULL);
  
  char datatype[32] = "";
  char version[32] = "";
  int operation_done = 0;
  FILE *file = ground_area_text_storage -> file;
  long file_initial_position = ftell (file);
  
  jump_over_commentary(file);
  operation_done = fscanf (
    file,
    "datatype\t%s\tversion\t%s\n",
    datatype,
    version
  );
  
//   DEBUG_IF (1, "%ld", file_initial_position);
//   DEBUG_IF (1, "%ld", ftell (file));
//   DEBUG_IF (1, "%d", operation_done);
//   DEBUG_IF (1, "%s", datatype);
//   DEBUG_IF (1, "%s", version);
  
  if (operation_done != 2
    || strcmp(ground_area_text_storage -> datatype, datatype) != 0
    || strcmp(ground_area_text_storage -> version, version) != 0
  )
  {
    fseek (file, file_initial_position, SEEK_SET);
    return NULL;
  }
  
  /* Recuperation des parametres de configuration */
  int width = 0;
  int length = 0;
  
  jump_over_commentary(file);
  operation_done = fscanf (file, "width\t%d\n", &width);
  jump_over_commentary(file);
  operation_done += fscanf (file, "length\t%d\n", &length);
  
  if (operation_done != 2)
  {
    fseek (file, file_initial_position, SEEK_SET);
    return NULL;
  }
  
  PtrGroundArea ground_area = NULL;
  ground_area_create (&ground_area, width, length);
  
  int array_width = ground_area -> array_width;
  int array_length = ground_area -> array_length;
  
  int i = 0, j = 0;
  for (i = 0; i < array_width; i++)
  {
    for (j= 0; j < array_length; j++)
    {
      int x = 0, y = 0;
      char type_string[32] = "";
      double height = 0.0;
      enum GROUND_TYPE type = ground_type_unknown;
      
      jump_over_commentary (file);
      operation_done = fscanf (file,
              "%d\t%d\t%s\t%lf", 
              &x,
              &y,
              type_string,
              &height);
      
      type = convert_string_to_ground_type (type_string);
      
      PtrGround ground = ground_area_get_ground (ground_area, x, y);
      ground_set_type (ground, type);
      ground_set_height (ground, height);
      
    }
  }
  
  return ground_area;
}

/*!
 * \brief Convertit le type du ground en chaine de caractere
 */
static void convert_ground_type_to_string (enum GROUND_TYPE type, char *string)
{
  assert (type != ground_type_unknown);
  
  if (type == ground_type_water)
  {
    strcpy (string, "water");
  }
  else if (type == ground_type_ground)
  {
    strcpy (string, "ground");
  }
  else
  {
    strcpy (string, "unknown");
  }
}

/*!
 * \brief Convertit une chaine de caractere vers le type ground
 */
static enum GROUND_TYPE convert_string_to_ground_type (char *string)
{
  enum GROUND_TYPE type = ground_type_unknown;
  
  if (strcmp (string, "water") == 0)
  {
    type = ground_type_water;
  }
  else if (strcmp (string, "ground") == 0)
  {
    type = ground_type_ground;
  }
  
  assert (type != ground_type_unknown);
  
  return type;
}

/*!
 * \brief Saute les commentaires
 */
static void jump_over_commentary (FILE *file)
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