typedef struct ground_area_energy_map_navigator
{
	PtrGroundAreaEnergyMap current;
	int current_position;
	PtrGroundAreaEnergyMap first;
	int count;
} GroundAreaEnergyMapNavigator;

typedef GroundAreaEnergyMapNavigator* PtrGroundAreaEnergyMapNavigator;

/*!
 * \brief Instancie un navigateur pour des energy maps
 */
void ground_area_energy_map_navigator_create (PtrGroundAreaEnergyMapNavigator*);

/*!
 * \brief Detruit un navigateur d'energy map
 */
void ground_area_energy_map_navigator_destroy (PtrGroundAreaEnergyMapNavigator*);

/*!
 * \brief Ajoute une energy map a la fin de la liste existante
 */
void ground_area_energy_map_navigator_add (PtrGroundAreaEnergyMapNavigator, PtrGroundAreaEnergyMap);

/*!
 * \brief Supprime une energy map de la liste existante
 */
void ground_area_energy_map_navigator_delete (PtrGroundAreaEnergyMapNavigator, PtrGroundAreaEnergyMap);

/*!
 * \brief Deplace le curseur courant a l'energy map d'apres
 * 
 * retourne 1 si le deplacement est un succes, 0 autrement
 */
int ground_area_energy_map_navigator_move_next (PtrGroundAreaEnergyMapNavigator);

/*!
 * \brief Deplace le curseur courant a l'energy map d'avant
 * 
 *  retourne 1 si le deplacement est un succes, 0 autrement
 */
int ground_area_energy_map_navigator_move_previous (PtrGroundAreaEnergyMapNavigator);

/*!
 * \brief Deplace le curseur courant a une position donnee
 * 
 *  retourne 1 si le deplacement est un succes, 0 autrement
 */
int ground_area_energy_map_navigator_move_position (PtrGroundAreaEnergyMapNavigator, int position);

/*!
 * \brief Retourne le nombre total d'energy map
 */
int ground_area_energy_map_navigator_get_count (PtrGroundAreaEnergyMapNavigator);

/*!
 * \brief Retourne l'energy map courante
 */
PtrGroundAreaEnergyMap ground_area_energy_map_navigator_get_current (PtrGroundAreaEnergyMapNavigator);