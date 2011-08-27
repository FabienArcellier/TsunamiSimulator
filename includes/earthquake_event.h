typedef struct earthquake_event
{
	Event parent;
	PtrGround ground;
	double energy;
	void (*Destroy) (struct earthquake_event**);
	void (*Execute) (struct earthquake_event*);
} EarthquakeEvent;

typedef EarthquakeEvent * PtrEarthquakeEvent;

/*!
 * \brief Cree une instance de type EarthquakeEvent
 */
void earthquake_event_create (PtrEarthquakeEvent*);

/*!
 * \brief Detruit une instance de type EarthquakeEvent
 */
void earthquake_event_destroy (PtrEarthquakeEvent*);

/*!
 * \brief Detruit une instance de type EarthquakeEvent
 */
void earthquake_event_destroy_parent (PtrEvent*);

/*!
 * \brief Assesseur en ecriture de l'attribut ground
 */
void earthquake_event_set_ground (PtrEarthquakeEvent, PtrGround);

/*!
 * \brief Assesseur en lecture de l'attribut ground
 */
PtrGround earthquake_event_get_ground (PtrEarthquakeEvent);

/*!
 * \brief Assesseur en ecriture de l'attribut energy
 */
void earthquake_event_set_energy (PtrEarthquakeEvent, double);

/*!
 * \brief Assesseur en lecture de l'attribut energy
 */
double earthquake_event_get_energy (PtrEarthquakeEvent);

/*!
 * \brief Fonction herite de event
 */
void earthquake_event_execute (PtrEarthquakeEvent);

/*!
 * \brief Fonction herite de event
 */
void earthquake_event_execute_parent (PtrEvent);