#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "water_hmap.h"
#include "water_simulation_engine.h"

/*!
 * \brief Effectue une rotation des hmaps. La plus ancienne devient la courante
 * 
 * L'objet est dans un etat instable apres cette operation. Il est necessaire de
 * calculer cet hmap avec la fonction water_simulation_engine_calculate_next_hmap().
 */
static void water_simulation_engine_rotate_water_hmaps (PtrWaterSimulationEngine);

/*!
 * \brief Calcule la hmap courante à partir des 2 précédentes
 */
static void water_simulation_engine_calculate_next_hmap (PtrWaterSimulationEngine);


/*!
 * \brief Cree un objet WaterSimulationEngine
 */
void water_simulation_engine_create (PtrWaterSimulationEngine* water_simulation_engine, int width, int height)
{
  assert (*water_simulation_engine == NULL);
  
  *water_simulation_engine = (PtrWaterSimulationEngine) malloc (sizeof (WaterSimulationEngine));
  if (*water_simulation_engine == NULL)
  {
    abort();
  }
  
  memset (*water_simulation_engine, 0, sizeof (WaterSimulationEngine));
  (*water_simulation_engine) -> width = width;
  (*water_simulation_engine) -> height = height;
  (*water_simulation_engine) -> damping = 0.9;
  
  /* Instanciation des objets WaterHmap */
  PtrWaterHmap water_hmap_previous2 = NULL, water_hmap_previous = NULL, water_hmap_current = NULL;
  
  water_hmap_create (&water_hmap_previous2, width, height);
  water_hmap_create (&water_hmap_previous, width, height);
  water_hmap_create (&water_hmap_current, width, height);
  
  (*water_simulation_engine) -> water_hmap_previous2 = water_hmap_previous2;
  (*water_simulation_engine) -> water_hmap_previous = water_hmap_previous;
  (*water_simulation_engine) -> water_hmap_current = water_hmap_current;
  
  assert (*water_simulation_engine != NULL);
  assert ((*water_simulation_engine) -> water_hmap_previous2  != NULL);
  assert ((*water_simulation_engine) -> water_hmap_previous != NULL);
  assert ((*water_simulation_engine) -> water_hmap_current != NULL);
}

/*!
 * \brief Destruit un objet WaterSimulationEngine
 */
void water_simulation_engine_destroy (PtrWaterSimulationEngine *water_simulation_engine)
{
  assert (*water_simulation_engine != NULL);
  assert ((*water_simulation_engine) -> water_hmap_previous2  != NULL);
  assert ((*water_simulation_engine) -> water_hmap_previous != NULL);
  assert ((*water_simulation_engine) -> water_hmap_current != NULL);
  
  /* Desallocation des objets WaterHmap */
  PtrWaterHmap water_hmap_previous2 = NULL, water_hmap_previous = NULL, water_hmap_current = NULL;
  
  water_hmap_previous2 = (*water_simulation_engine) -> water_hmap_previous2;
  water_hmap_previous = (*water_simulation_engine) -> water_hmap_previous;
  water_hmap_current = (*water_simulation_engine) -> water_hmap_current;
  
  water_hmap_destroy (&water_hmap_previous2);
  water_hmap_destroy (&water_hmap_previous);
  water_hmap_destroy (&water_hmap_current);
  
  free (*water_simulation_engine);
  *water_simulation_engine = NULL;
  
  assert (*water_simulation_engine == NULL);
}

/*!
 * \brief Calcule la water_hmap suivante
 */
void water_simulation_engine_set_next_hmap (PtrWaterSimulationEngine water_simulation_engine)
{
  assert (water_simulation_engine != NULL);
  assert (water_simulation_engine -> water_hmap_previous2  != NULL);
  assert (water_simulation_engine -> water_hmap_previous != NULL);
  assert (water_simulation_engine -> water_hmap_current != NULL);
  
  water_simulation_engine_rotate_water_hmaps (water_simulation_engine);
  water_simulation_engine_calculate_next_hmap (water_simulation_engine);
  
  assert (water_simulation_engine != NULL);
  assert (water_simulation_engine -> water_hmap_previous2  != NULL);
  assert (water_simulation_engine -> water_hmap_previous != NULL);
  assert (water_simulation_engine -> water_hmap_current != NULL);
}

/*!
 * \brief Retourne la water_hmap courante
 */
PtrWaterHmap water_simulation_engine_get_current_hmap (PtrWaterSimulationEngine water_simulation_engine)
{
  return water_simulation_engine -> water_hmap_current;
}

/*!
 * \brief Effectue une rotation des hmaps. La plus ancienne devient la courante
 * 
 * L'objet est dans un etat instable apres cette operation. Il est necessaire de
 * calculer cet hmap avec la fonction water_simulation_engine_calculate_next_hmap().
 */
static void water_simulation_engine_rotate_water_hmaps (PtrWaterSimulationEngine water_simulation_engine)
{
  assert (water_simulation_engine != NULL);
  assert (water_simulation_engine -> water_hmap_previous2  != NULL);
  assert (water_simulation_engine -> water_hmap_previous != NULL);
  assert (water_simulation_engine -> water_hmap_current != NULL);
  
  PtrWaterHmap water_hmap_previous2 = NULL, water_hmap_previous = NULL, water_hmap_current = NULL;
  water_hmap_previous2 = water_simulation_engine -> water_hmap_previous2;
  water_hmap_previous = water_simulation_engine -> water_hmap_previous;
  water_hmap_current = water_simulation_engine -> water_hmap_current;
  
  water_simulation_engine -> water_hmap_previous2 = water_hmap_previous;
  water_simulation_engine -> water_hmap_previous = water_hmap_current;
  water_simulation_engine -> water_hmap_current = water_hmap_previous2;
  
  assert (water_simulation_engine != NULL);
  assert (water_simulation_engine -> water_hmap_previous2  != NULL);
  assert (water_simulation_engine -> water_hmap_previous != NULL);
  assert (water_simulation_engine -> water_hmap_current != NULL);
}

/*!
 * \brief Calcule la hmap courante à partir des 2 précédentes
 */
static void water_simulation_engine_calculate_next_hmap (PtrWaterSimulationEngine water_simulation_engine)
{
  assert (water_simulation_engine != NULL);
  assert (water_simulation_engine -> water_hmap_previous2  != NULL);
  assert (water_simulation_engine -> water_hmap_previous != NULL);
  assert (water_simulation_engine -> water_hmap_current != NULL);
  
  int width = water_simulation_engine -> width, height = water_simulation_engine -> height;
  int i = 0, j = 0;
  PtrWaterHmap water_hmap_previous2 = NULL, water_hmap_previous = NULL, water_hmap_current = NULL;
  
  water_hmap_previous2 = water_simulation_engine -> water_hmap_previous2;
  water_hmap_previous = water_simulation_engine -> water_hmap_previous;
  water_hmap_current = water_simulation_engine -> water_hmap_current;
  
  // Pour tous les elements sauf ceux en bordure
  for (i = 1; i < width - 1; i++)
  {
    for (j = 1; j < height - 1; j++)
    {
      int water_height = 0;
      
      water_height = (int) ((water_hmap_get_water_height (water_hmap_previous, i - 1, j) +
                      water_hmap_get_water_height (water_hmap_previous, i + 1, j) +
                      water_hmap_get_water_height (water_hmap_previous, i, j - 1) +
                      water_hmap_get_water_height (water_hmap_previous, i, j + 1)) / 2);
      water_height = water_height - (water_hmap_get_water_height(water_hmap_previous2, i, j));
      
      // Simulation de la perte d'energie par l'amortissement
      water_height = (int) (water_height * water_simulation_engine -> damping);
      
      water_hmap_set_water_height (water_hmap_current, i, j, water_height);
    }
  }
  
  assert (water_simulation_engine != NULL);
  assert (water_simulation_engine -> water_hmap_previous2  != NULL);
  assert (water_simulation_engine -> water_hmap_previous != NULL);
  assert (water_simulation_engine -> water_hmap_current != NULL);
}