#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "water_hmap.h"
#include "water_hmap_csv_storage.h"

/*!
 * \brief Cree une instance permettant d'écrire un objet WaterHmap au format Csv
 */ 
void water_hmap_csv_storage_create (PtrWaterHmapCsvStorage* water_hmap_csv_storage, FILE* file)
{
  assert (*water_hmap_csv_storage == NULL);
  assert (file != NULL);
  
  *water_hmap_csv_storage = (PtrWaterHmapCsvStorage) malloc (sizeof (WaterHmapCsvStorage));
  if (*water_hmap_csv_storage == NULL)
  {
    abort();
  }
  
  memset(*water_hmap_csv_storage, 0, sizeof (WaterHmapCsvStorage));
  (*water_hmap_csv_storage) -> file = file;
  strcpy((*water_hmap_csv_storage) -> datatype, "WaterHmapCsvStorage");
  strcpy((*water_hmap_csv_storage) -> version, "1.0.0");
  
  assert (*water_hmap_csv_storage != NULL);
}

/*!
 * \brief Detruit l'objet
 */
void water_hmap_csv_storage_destroy (PtrWaterHmapCsvStorage* water_hmap_csv_storage)
{
  assert (*water_hmap_csv_storage != NULL);
  
  free (*water_hmap_csv_storage);
  *water_hmap_csv_storage = NULL;
  
  assert (*water_hmap_csv_storage == NULL);
}

/*!
 * \brief Ecrit l'objet WaterHmap au format Csv
 */ 
void water_hmap_csv_storage_write (PtrWaterHmapCsvStorage water_hmap_csv_storage, PtrWaterHmap water_hmap)
{
  assert (water_hmap_csv_storage != NULL);
  assert (water_hmap_csv_storage -> file != NULL);
  
  int width = water_hmap -> width;
  int height = water_hmap -> height;
  FILE* file = water_hmap_csv_storage -> file;
  
  fprintf(
    file, 
    "datatype\t%s\tversion\t%s\n", 
    water_hmap_csv_storage -> datatype, 
    water_hmap_csv_storage -> version);
  
  fprintf(file, "width\t%d\theight\t%d\n", width, height);
  
  int i = 0, j = 0;
  for (i = 0; i < width; i++)
  {
    for (j = 0; j < height; j++)
    {
      int water_height = water_hmap_get_water_height (water_hmap, i, j);
      fprintf(file, "%d\t", water_height);
    }
    
    fprintf(file,"\n");
  }
  
  fprintf(file,"\n");
}

/*!
 * \brief A partir d'un handle de fichier, cree un objet WaterHmap
 * 
 * Retourne NULL si la lecture du fichier est un echec. Le curseur est remis a sa
 * position d'origine.
 */
PtrWaterHmap water_hmap_csv_storage_read (PtrWaterHmapCsvStorage water_hmap_csv_storage)
{
  assert (water_hmap_csv_storage != NULL);
  assert (water_hmap_csv_storage -> file != NULL);
  
  char datatype[50] = "";
  char version[50] = "";
  int succes = 0;
  
  /* Recuperation des informations standart : Datatype, version */
  FILE* file = water_hmap_csv_storage -> file;
  long file_position = ftell (file);
  succes = fscanf (
    file,
    "datatype\t%s\tversion\t%s\n",
    datatype,
    version
  );
  
  if (succes != 2
    || strcmp(water_hmap_csv_storage -> datatype, datatype) != 0
    || strcmp(water_hmap_csv_storage -> version, version) != 0)
  {
    fseek (file, file_position, SEEK_SET);
    return NULL;
  }
  
  /* Recuperation des parametres de configuration */
  int width = 0;
  int height = 0;
  
  succes = fscanf (
    file,
    "width\t%d\theight\t%d\n",
    &width,
    &height
  );
  
  if (succes != 2
    || width <= 0
    || height <= 0)
  {
    fseek (file, file_position, SEEK_SET);
    return NULL;
  }
  
  /* Recuperation de la carte des hauteurs */
  
  PtrWaterHmap water_hmap = NULL;
  water_hmap_create (&water_hmap, width, height);
  
  int i = 0, j = 0;
  for (i = 0; i < width; i++)
  {
    for (j = 0; j < height; j++)
    {
      int water_height = 0;
      succes = fscanf(file, "%d\t", &water_height);
      
      if (succes != 1
        || water_height < 0)
      {
        water_hmap_destroy (&water_hmap);
        fseek (file, file_position, SEEK_SET);
        return NULL;
      }
      
      water_hmap_set_water_height (water_hmap, i, j, water_height);
    }
    
    fscanf (file, "\n");
  }
  
  return water_hmap;
}