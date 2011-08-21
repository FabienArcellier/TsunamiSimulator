typedef struct water_hmap_csv_storage
{
  FILE *file;
  char datatype[50];
  char version[50];
} WaterHmapCsvStorage;

typedef WaterHmapCsvStorage * PtrWaterHmapCsvStorage;

/*!
 * \brief Cree une instance permettant d'écrire un objet WaterHmap au format Csv
 */ 
void water_hmap_csv_storage_create (PtrWaterHmapCsvStorage*, FILE*);

/*!
 * \brief Detruit l'objet
 */
void water_hmap_csv_storage_destroy (PtrWaterHmapCsvStorage*);

/*!
 * \brief Ecrit l'objet WaterHmap au format Csv
 */ 
void water_hmap_csv_storage_write (PtrWaterHmapCsvStorage, PtrWaterHmap);

/*!
 * \brief A partir d'un handle de fichier, cree un objet WaterHmap
 * 
 * Retourne NULL si la lecture du fichier est un echec. Le curseur est remis a sa
 * position d'origine.
 */
PtrWaterHmap water_hmap_csv_storage_read (PtrWaterHmapCsvStorage);