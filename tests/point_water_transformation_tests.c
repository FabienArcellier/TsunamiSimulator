#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "test.h"
#include "water_hmap.h"
#include "water_simulation_engine.h"
#include "point_water_transformation.h"

static void point_water_transformation_apply_test();

int main (void)
{
  point_water_transformation_apply_test();
  
  return 0;
}

static void point_water_transformation_apply_test()
{
  TEST_TITLE("point_water_transformation_apply_test");
  
  PtrWaterSimulationEngine water_simulation_engine = NULL;
  water_simulation_engine_create (&water_simulation_engine, 300, 300);
  
  PtrPointWaterTransformation point_water_transformation = NULL;
  point_water_transformation_create (&point_water_transformation);
  point_water_transformation_set_water_height (point_water_transformation, 456);
  point_water_transformation_set_application_point (point_water_transformation, 5, 5);
  point_water_transformation -> Apply (point_water_transformation, water_simulation_engine);
  
  PtrWaterHmap hmap = water_simulation_engine_get_current_hmap (water_simulation_engine);
  TEST(water_hmap_get_water_height (hmap, 5, 5) == 456);
  
  point_water_transformation -> Apply (point_water_transformation, water_simulation_engine);
  TEST(water_hmap_get_water_height (hmap, 5, 5) == 456 * 2);
  
  point_water_transformation_destroy (&point_water_transformation);
  water_simulation_engine_destroy (&water_simulation_engine);
}

