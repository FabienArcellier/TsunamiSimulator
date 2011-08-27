typedef struct wave_signal
{
	double energy;
	double direction;
	double length;
	double distance;
	struct wave_signal *next;
} WaveSignal;

typedef WaveSignal * PtrWaveSignal;

/*!
 * \brief cree une instance de type wave_signal
 */
void wave_signal_create (PtrWaveSignal*);

/*!
 * \brief detruit une instance et ses liens de type wave_signal
 */
void wave_signal_destroy (PtrWaveSignal*);

/*!
 * \brief Assesseur d'ecriture de energy
 */
void wave_signal_set_energy (PtrWaveSignal, double);

/*!
 * \brief Assesseur de lecture de energy
 */
double wave_signal_get_energy (PtrWaveSignal);

/*!
 * \brief Assesseur d'ecriture de la frequence de l'onde
 */
void wave_signal_set_length (PtrWaveSignal, double);

/*!
 * \brief Assesseur de lecture de la frequence de l'onde
 */
double wave_signal_get_length (PtrWaveSignal);

/*!
 * \brief Assesseur d'ecriture de l'attribut direction (en degree)
 * 
 * La direction est modulé par 360.
 */
void wave_signal_set_direction (PtrWaveSignal, double);

/*!
 * \brief Assesseur de lecture de l'attribut direction (en degree)
 */
double wave_signal_get_direction (PtrWaveSignal);

/*!
 * \brief Assesseur d'ecriture de l'attribut next
 */
void wave_signal_set_next_wave_signal (PtrWaveSignal, PtrWaveSignal);

/*!
 * \brief Assesseur de lecture de l'attribut next
 */
PtrWaveSignal wave_signal_get_next_wave_signal (PtrWaveSignal);

/*!
 * \brief Insere une instance de type wave signal dans une liste
 * 
 * Cette methode presuppose que la liste est deja ordonne par frequence croissante
 */
PtrWaveSignal wave_signal_insert_wave_signal_sort_by_length_asc (PtrWaveSignal, PtrWaveSignal);