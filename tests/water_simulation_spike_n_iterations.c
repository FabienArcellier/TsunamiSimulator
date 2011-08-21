#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "water_hmap.h"
#include "water_hmap_csv_storage.h"
#include "water_simulation_engine.h"

#define ITERATION 100

int main (void)
{
  PtrWaterSimulationEngine water_simulation_engine = NULL;
  water_simulation_engine_create (&water_simulation_engine, 40, 40);
  PtrWaterHmap current_hmap = water_simulation_engine_get_current_hmap (water_simulation_engine);
  
  /* Configure the data */
  int i = 0, j = 0;
  for (i = 0; i < 5; i++)
  {
    for (j = 0; j < 40; j++)
    {
      water_hmap_set_water_height (current_hmap, 5 + i, j, 10000);
    }
  }
  
  for (i = 0; i < ITERATION; i++)
  {
    current_hmap = water_simulation_engine_get_current_hmap (water_simulation_engine);
    char filename [50] = "";
    sprintf (filename, "water_simulation_spike_100_%d.txt", i);
    //DEBUG_IF(1, "%s", filename);
    FILE *file = fopen (filename, "w+");
    if (file == NULL)
    {
      abort();
    }
    
    PtrWaterHmapCsvStorage water_hmap_csv_storage = NULL;
    water_hmap_csv_storage_create (&water_hmap_csv_storage, file);
    water_hmap_csv_storage_write (water_hmap_csv_storage, current_hmap);
    water_hmap_csv_storage_destroy (&water_hmap_csv_storage);
    
    printf("%d : %d\n", i, water_hmap_get_water_height(current_hmap, 5, 5));
    
    /* Simulation de l'iteration suivante */
    water_simulation_engine_set_next_hmap (water_simulation_engine);
  }
  
  water_simulation_engine_destroy (&water_simulation_engine);
  
  return 0;
}