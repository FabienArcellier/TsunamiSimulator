#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "test.h"
#include "water_hmap.h"

static void test_water_hmap_get_water_height ();
static void test_water_hmap_set_water_height ();

int main (void)
{
  test_water_hmap_get_water_height ();
  test_water_hmap_set_water_height ();
  
  return 0;
}

static void test_water_hmap_get_water_height()
{
  TEST_TITLE ("test_water_hmap_get_water_height");
  
  PtrWaterHmap water_hmap = NULL;
  water_hmap_create (&water_hmap, 10, 10);
  
  water_hmap -> map[19] = 45;
  TEST (water_hmap_get_water_height (water_hmap, 9, 1) == 45);
  TEST (water_hmap_get_water_height (water_hmap, 8, 1) == 0);
}

static void test_water_hmap_set_water_height()
{
  TEST_TITLE ("test_water_hmap_set_water_height");
  
  PtrWaterHmap water_hmap = NULL;
  water_hmap_create (&water_hmap, 10, 10);
  
  water_hmap_set_water_height (water_hmap, 9, 1, 45);
  TEST (water_hmap_get_water_height (water_hmap, 9, 1) == 45);
  TEST (water_hmap_get_water_height (water_hmap, 8, 1) == 0);
}