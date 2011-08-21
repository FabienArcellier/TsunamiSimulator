#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "water_hmap.h"
#include "water_simulation_engine.h"
#include "point_water_transformation.h"

/*!
 * \brief Cree une instance pour transformer un point de la zone liquide
 */
void point_water_transformation_create (PtrPointWaterTransformation *point_water_transformation)
{
  assert (*point_water_transformation == NULL);
  
  *point_water_transformation = (PtrPointWaterTransformation) malloc (sizeof (PointWaterTransformation));
  memset (*point_water_transformation, 0, sizeof (PointWaterTransformation));
  
  (*point_water_transformation) -> Apply = point_water_transformation_apply;
  
}

/*!
 * \brief detruit l'objet
 */
void point_water_transformation_destroy (PtrPointWaterTransformation *point_water_transformation)
{
  assert (*point_water_transformation != NULL);
  
  free (*point_water_transformation);
  *point_water_transformation = NULL;
}

/*!
 * \brief Configure la hauteur d'eau
 */
void point_water_transformation_set_water_height (PtrPointWaterTransformation point_water_transformation, int water_height)
{
  assert (point_water_transformation != NULL);
  
  point_water_transformation -> water_height = water_height;
  
  assert (point_water_transformation != NULL);
}

/*!
 * \brief Configure le point d'application de cette transformation
 */
void point_water_transformation_set_application_point (PtrPointWaterTransformation point_water_transformation, int x, int y)
{
  assert (point_water_transformation != NULL);
  assert (x >= 0);
  assert (y >= 0);
  
  point_water_transformation -> x = x;
  point_water_transformation -> y = y;
  
  assert (point_water_transformation != NULL);
}

/*!
 * \brief Applique la transformation
 */
void point_water_transformation_apply (
  PtrPointWaterTransformation point_water_transformation, 
  PtrWaterSimulationEngine water_simulation_engine)
{
  PtrWaterHmap hmap = water_simulation_engine_get_current_hmap (water_simulation_engine);
  
  if (point_water_transformation -> x < hmap -> width &&
    point_water_transformation -> y < hmap -> height)
  {
    int water_height = water_hmap_get_water_height (hmap,
                                                    point_water_transformation -> x,
                                                    point_water_transformation -> y);

    water_hmap_set_water_height (hmap, 
                                 point_water_transformation -> x,
                                 point_water_transformation -> y,
                                 water_height + point_water_transformation -> water_height);
  }
}