typedef struct simulation
{
	PtrTimeline timeline;
	PtrGroundArea ground_area;
	PtrGroundAreaEnergyMap file_ground_area_energy_map;
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
 * \brief Assesseur en ecriture de file_ground_area_energy_map
 */
void simulation_set_push_energy_map (PtrSimulation, PtrGroundAreaEnergyMap);

/*!
 * \brief Assesseur en lecture de file_ground_area_energy_map
 */
PtrGroundAreaEnergyMap simulation_set_pop_energy_map (PtrSimulation);

/*!
 * \brief Retourne 0 si l'energie map est vide
 */
int simulation_energy_map_empty (PtrSimulation);
