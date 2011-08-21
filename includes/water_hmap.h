
/*!
 * \brief structure qui represente une carte de la hauteur d'eau
 * 
 * La hauteur d'eau varie entre 0 et 255
 */
typedef struct water_hmap
{
  int width;
  int height;
  int *map;
} WaterHmap;

typedef WaterHmap * PtrWaterHmap;

/*!
 * \brief cree une instance PtrWaterHmap
 */
void water_hmap_create (PtrWaterHmap*, int, int);

/*!
 * \brief desalloue la memoire
 */
void water_hmap_destroy (PtrWaterHmap*);

/*!
 * \brief retourne la valeur d'un element selon ses coordonnes x et y
 */ 
int water_hmap_get_water_height (PtrWaterHmap, int x, int y);

/*!
 * \brief modifie la valeur d'un element selon ses coordonnes x et y
 */ 
void water_hmap_set_water_height (PtrWaterHmap, int x, int y, int water_height);