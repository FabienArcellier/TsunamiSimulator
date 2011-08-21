#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "test.h"
#include "water_hmap.h"
#include "water_hmap_csv_storage.h"

static void water_hmap_csv_storage_write_tests ();

int main (void)
{
  water_hmap_csv_storage_write_tests();
}

static void water_hmap_csv_storage_write_tests ()
{
  TEST_TITLE("water_hmap_csv_storage_write_tests : Controler manuellement le fichier hmap.txt");
  
  PtrWaterHmap hmap = NULL;
  water_hmap_create (&hmap, 30, 30);
  water_hmap_set_water_height (hmap, 0, 0, 24);
  
  FILE *file = fopen ("hmap.txt", "w+");
  if (file == NULL)
  {
    abort();
  }
  
  PtrWaterHmapCsvStorage hmap_storage = NULL;
  water_hmap_csv_storage_create(&hmap_storage, file);
  water_hmap_csv_storage_write (hmap_storage, hmap);
  water_hmap_csv_storage_destroy(&hmap_storage);
  water_hmap_destroy(&hmap);
  
  fclose (file);
}