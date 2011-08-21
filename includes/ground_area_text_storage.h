typedef struct ground_area_text_storage
{
  FILE *file;
  char datatype[32];
  char version [32];
} GroundAreaTextStorage;

#define GROUND_AREA_TEXT_STORAGE_DATATYPE "ground_area_text_storage"
#define GROUND_AREA_TEXT_STORAGE_VERSION "1.0.0"

typedef GroundAreaTextStorage * PtrGroundAreaTextStorage;

/*!
 * \brief Cree une instance de l'objet GroundAreaTextStorage
 */
void ground_area_text_storage_create (PtrGroundAreaTextStorage*);

/*!
 * \brief Detruit l'instance d'un objet GroundAreaTextStorage
 */
void ground_area_text_storage_destroy (PtrGroundAreaTextStorage*);

/*!
 * \brief Permet de configurer le handle du fichier pour l'ecriture
 */
void ground_area_text_storage_set_file (PtrGroundAreaTextStorage, FILE*);

/*!
 * \brief Lance l'ecriture du fichier
 */
void ground_area_text_storage_write_file (PtrGroundAreaTextStorage, PtrGroundArea);

/*!
 * \brief Lit le fichier
 */
PtrGroundArea ground_area_text_storage_read_file (PtrGroundAreaTextStorage);