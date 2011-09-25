typedef struct ground_area_energy_text_storage
{
	FILE *file;
	char datatype[32];
	char version[32];
} GroundAreaEnergyTextStorage;

typedef GroundAreaEnergyTextStorage * PtrGroundAreaEnergyTextStorage;

#define GROUND_AREA_ENERGY_TEXT_STORAGE_DATATYPE "ground_area_energy_text_storage"
#define GROUND_AREA_ENERGY_TEXT_STORAGE_VERSION "1.0.0"

/*!
 * \brief Cree un rapport d'energie pour ground area.
 */
void ground_area_energy_text_storage_create (PtrGroundAreaEnergyTextStorage*);

/*!
 * \brief Detruit une instance de l'objet ground_area_energy_text_storage
 */
void ground_area_energy_text_storage_destroy (PtrGroundAreaEnergyTextStorage*);

/*!
 * \brief Assesseur de l'attribut file en ecriture
 */
void ground_area_energy_text_storage_set_file (PtrGroundAreaEnergyTextStorage, FILE*);

/*!
 * \brief Assesseur de l'attribut file en lecture
 */
FILE* ground_area_energy_text_storage_get_file (PtrGroundAreaEnergyTextStorage);

/*!
 * \brief Ecrire le fichier ground_area_energy_text_storage
 */
void ground_area_energy_text_storage_write_file (PtrGroundAreaEnergyTextStorage, PtrGroundAreaEnergyMap);

/*!
 * \brief Lit le fichier ground_area_energy_text_storage
 */
PtrGroundAreaEnergyMap ground_area_energy_text_storage_read_file (PtrGroundAreaEnergyTextStorage ground_area_energy_text_storage,
																																	PtrGroundArea ground_area);
