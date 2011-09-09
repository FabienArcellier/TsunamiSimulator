typedef struct earthquake_events_text_storage
{
	FILE* file;
  char datatype[32];
  char version [32];
} EarthquakeEventsTextStorage;

#define EARTHQUAKE_EVENTS_TEXT_STORAGE_DATATYPE "earthquake_events_text_storage"
#define EARTHQUAKE_EVENTS_TEXT_STORAGE_VERSION "1.0.0"

typedef EarthquakeEventsTextStorage * PtrEarthquakeEventsTextStorage;

/*!
 * \brief Cree une instance de EarthquakeEventsTextStorage
 */
void earthquake_events_text_storage_create (PtrEarthquakeEventsTextStorage*);

/*!
 * \brief Detruit une instance de EarthquakeEventsTextStorage
 */
void earthquake_events_text_storage_destroy (PtrEarthquakeEventsTextStorage*);

/*!
 * \brief Assesseur en ecriture de l'attribut file
 */
void earthquake_events_text_storage_set_file (PtrEarthquakeEventsTextStorage, FILE*);

/*!
 * \brief Assesseur en lecture de l'attribut file
 */
FILE* earthquake_events_text_storage_get_file (PtrEarthquakeEventsTextStorage);

/*!
 * \brief Lance l'ecriture du fichier
 */
void earthquake_events_text_storage_write_file (PtrEarthquakeEventsTextStorage, PtrEvent);

/*!
 * \brief Lance la lecture du fichier
 */
PtrEvent earthquake_events_text_storage_read_file (PtrEarthquakeEventsTextStorage earthquake_events_text_storage, 
																														 PtrGroundArea ground_area);