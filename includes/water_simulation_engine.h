typedef struct water_simulation_engine
{
  int temps;
  int width;
  int height;
  double damping;
  PtrWaterHmap water_hmap_previous2;
  PtrWaterHmap water_hmap_previous;
  PtrWaterHmap water_hmap_current;
} WaterSimulationEngine;

typedef WaterSimulationEngine * PtrWaterSimulationEngine;

/*!
 * \brief Cree un objet WaterSimulationEngine
 */
void water_simulation_engine_create (PtrWaterSimulationEngine*, int width, int height);

/*!
 * \brief Destruit un objet WaterSimulationEngine
 */
void water_simulation_engine_destroy (PtrWaterSimulationEngine*);

/*!
 * \brief Calcule la water_hmap suivante
 */
void water_simulation_engine_set_next_hmap (PtrWaterSimulationEngine);

/*!
 * \brief Retourne la water_hmap courante
 */
PtrWaterHmap water_simulation_engine_get_current_hmap (PtrWaterSimulationEngine);