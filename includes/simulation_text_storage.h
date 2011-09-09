typedef struct simulation_text_storage
{
	FILE *file;
	PtrEarthquakeEventsTextStorage earthquake_events_text_storage;
	PtrGroundAreaTextStorage ground_area_text_storage;
	PtrGroundAreaEnergyTextStorage ground_area_energy_text_storage;
} SimulationTextStorage;

typedef SimulationTextStorage* PtrSimulationTextStorage;

/*!
 * \brief Cree une instance de l'objet SimulationTextStorage
 */
void simulation_text_storage_create (PtrSimulationTextStorage*);

/*!
 * \brief Detruit l'instance d'un objet SimulationTextStorage
 */
void simulation_text_storage_destroy (PtrSimulationTextStorage*);

/*!
 * \brief Assesseur en ecriture de file
 */
void simulation_text_storage_set_file (PtrSimulationTextStorage, FILE*);

/*!
 * \brief Assesseur en lecture de file
 */
FILE* simulation_text_storage_get_file (PtrSimulationTextStorage);

/*!
 * \brief Assesseur en ecriture earthquake_events_text_storage
 */
void simulation_text_storage_set_earthquake_events_text_storage (PtrSimulationTextStorage, PtrEarthquakeEventsTextStorage);

/*!
 * \brief Assesseur en lecture earthquake_events_text_storage
 */
PtrEarthquakeEventsTextStorage simulation_text_storage_get_earthquake_events_text_storage (PtrSimulationTextStorage);

/*!
 * \brief Assesseur en ecriture ground_area_text_storage
 */
void simulation_text_storage_set_ground_area_text_storage (PtrSimulationTextStorage, PtrGroundAreaTextStorage);

/*!
 * \brief Assesseur en lecture ground_area_text_storage
 */
PtrGroundAreaTextStorage simulation_text_storage_get_ground_area_text_storage (PtrSimulationTextStorage);

/*!
 * \brief Assesseur en ecriture de ground_area_energy_text_storage
 */
void simulation_text_storage_set_ground_area_energy_text_storage (PtrSimulationTextStorage, PtrGroundAreaEnergyTextStorage);

/*!
 * \brief Assesseur en lecture de ground_area_energy_text_storage
 */
PtrGroundAreaEnergyTextStorage simulation_text_storage_get_ground_area_energy_text_storage (PtrSimulationTextStorage);

/*!
 * \brief Ecrit un fichier simulation a partir d'un objet simulation
 */
void simulation_text_storage_write_file (PtrSimulationTextStorage, PtrSimulation);

/*!
 * \brief Lit le fichier et renvoie un objet Simulation
 */
PtrSimulation simulation_text_storage_read_file (PtrSimulationTextStorage);

