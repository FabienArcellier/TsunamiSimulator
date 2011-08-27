typedef struct wave_propagation_event
{
	Event parent;
	PtrWaveSignal wave_signal;
	PtrGround ground;
	void (*Destroy) (struct wave_propagation_event**);
	void (*Execute) (struct wave_propagation_event*);
} WavePropagationEvent;

typedef WavePropagationEvent* PtrWavePropagationEvent;

/*!
 * \brief Cree une instance de l'evenement de propagation d'une onde
 */
void wave_propagation_event_create (PtrWavePropagationEvent*, PtrGround, PtrWaveSignal);

/*!
 * \brief Initialise les methodes de la structure
 */
void wave_propagation_event_init (PtrWavePropagationEvent, PtrGround, PtrWaveSignal);

/*!
 * \brief detruit une instance de l'evenement
 */
void wave_propagation_event_destroy (PtrWavePropagationEvent*);

/*!
 * \brief retourne le terrain lié a l'onde à propager
 */
PtrGround wave_propagation_event_get_ground (PtrWavePropagationEvent);

/*!
 * \brief retourne la wave qui doit se propager
 */
PtrWaveSignal wave_propagation_event_get_wave_signal (PtrWavePropagationEvent);

/*!
 * \brief surcharge de event -> destroy avec un cast (appel de wave_propagation_event_destroy)
 */
void wave_propagation_event_destroy_parent (PtrEvent*);

/*!
 * \brief Declenche la propagation des ondes vers les cases voisines
 */
void wave_propagation_event_execute (PtrWavePropagationEvent);

/*!
 * \brief surcharge de event -> execute avec un cast (appel de wave_propagation_event_execute)
 */
void wave_propagation_event_execute_parent (PtrEvent);

void wave_propagation_event_dispatch_wave_neighbours (PtrGroundNeighbour list_neighbours, 
																								 PtrWaveSignal wave_signal, 
																								 int time_remaining);

/*!
 * \brief Calcule un ratio entre 0 et 1 permettant de calculer la repartition de l'energie entre plusieurs voisins
 */
double wave_propagation_event_calculate_ratio_energy (double wave_direction, double neighbour_direction);

/*!
 * \brief retourne la vitesse de deplacement de l'onde sur un terrain donne (m/s)
 */
double wave_propagation_event_get_wave_speed (int height);
