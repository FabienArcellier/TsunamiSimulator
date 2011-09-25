typedef struct simulation
{
	PtrTimeline timeline;
	PtrGroundArea ground_area;
	PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator;
} Simulation;

typedef Simulation * PtrSimulation;

/*!
 * \brief Cree une instance de type Simulation
 */
void simulation_create (PtrSimulation*);

/*!
 * \brief Detruit une instance de type Simulation
 */
void simulation_destroy (PtrSimulation*);

/*!
 * \brief Assesseur en ecriture de timeline
 */
void simulation_set_timeline (PtrSimulation, PtrTimeline);
/*!
 * \brief Assesseur en lecture de timeline
 */
PtrTimeline simulation_get_timeline (PtrSimulation);

/*!
 * \brief Assesseur en ecriture de ground_area
 */
void simulation_set_ground_area (PtrSimulation, PtrGroundArea);

/*!
 * \brief Assesseur en lecture de ground_area
 */
PtrGroundArea simulation_get_ground_area (PtrSimulation);

/*!
 * \brief Assesseur en ecriture de ground_area_energy_map_navigator
 */
void simulation_set_energy_map_navigator (PtrSimulation, PtrGroundAreaEnergyMapNavigator);

/*!
 * \brief Assesseur en lecture de ground_area_energy_map_navigator
 */
PtrGroundAreaEnergyMapNavigator simulation_get_energy_map_navigator (PtrSimulation);