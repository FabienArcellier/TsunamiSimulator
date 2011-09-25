typedef struct ground_area_energy_map
{
	struct ground_area_energy_map *next;
	struct ground_area_energy_map *previous;
	int array_width;
	int array_length;
	double *map;
} GroundAreaEnergyMap;

typedef GroundAreaEnergyMap * PtrGroundAreaEnergyMap;

/*!
 * \brief Cree une instance de type GroundAreaEnergyMap
 */
void ground_area_energy_map_create (PtrGroundAreaEnergyMap*, PtrGroundArea);

/*!
 * \brief Detruit une instance de type GroundAreaEnergyMap
 */
void ground_area_energy_map_destroy (PtrGroundAreaEnergyMap*);

/*!
 * \brief Calcule la carte d'energie d'une ground area
 */
void ground_area_energy_map_calculate (PtrGroundAreaEnergyMap, PtrGroundArea);

/*!
 * \brief Empile une instance de type PtrGroundAreaEnergyMap
 * \deprecated
 */
void ground_area_energy_map_push (PtrGroundAreaEnergyMap*, PtrGroundAreaEnergyMap);

/*!
 * \brief Depile une instance de type PtrGroundAreaEnergyMap
 * \deprecated
 */
PtrGroundAreaEnergyMap ground_area_energy_map_pop (PtrGroundAreaEnergyMap*);

/*!
 * \brief Definit la carte energetique suivante
 */
void ground_area_energy_map_set_next (PtrGroundAreaEnergyMap, PtrGroundAreaEnergyMap);

/*!
 * \brief Obtient la carte energetique suivante
 */
PtrGroundAreaEnergyMap ground_area_energy_map_get_next (PtrGroundAreaEnergyMap);

/*!
 * \brief Obtient la carte energetique precedente
 */
void ground_area_energy_map_set_previous (PtrGroundAreaEnergyMap, PtrGroundAreaEnergyMap);

/*!
 * \brief Obtient la carte energetique precedente
 */
PtrGroundAreaEnergyMap ground_area_energy_map_get_previous (PtrGroundAreaEnergyMap);

/*!
 * \brief Retourne 0 si il n y a aucune energie map
 */
int ground_area_energy_map_empty (PtrGroundAreaEnergyMap);

/*!
 * \brief Assesseur en lecture de array_width
 */
int ground_area_energy_map_get_array_width (PtrGroundAreaEnergyMap);

/*!
 * \brief Assesseur en lecture de array_length
 */
int ground_area_energy_map_get_array_length (PtrGroundAreaEnergyMap);

/*!
 * \brief Renvoie la quantite d'energie presente sur une case
 */
double ground_area_energy_map_get_energy (PtrGroundAreaEnergyMap, int, int);

/*!
 * \brief Renvoie la quantite d'energie presente sur une case
 */
void ground_area_energy_map_set_energy (PtrGroundAreaEnergyMap, int, int, double);


