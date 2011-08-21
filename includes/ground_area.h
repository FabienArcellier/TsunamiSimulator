typedef struct ground_area
{
  int width;
  int length;
  int array_width; // indice
  int array_length; //indice
  PtrGround area;
} GroundArea;

typedef GroundArea * PtrGroundArea;

#define GROUND_WIDTH 100
#define GROUND_LENGTH 100

/*!
 * \brief Cree un objet Ground Area qui contient un terrain (width en m, length en m)
 */
void ground_area_create (PtrGroundArea*, int width, int length);

/*!
 * \brief Destruit un objet Ground Area
 */
void ground_area_destroy (PtrGroundArea*);

/*!
 * \brief Retourne l'objet PtrGround pour les coordonnées données (indice)
 */
PtrGround ground_area_get_ground (PtrGroundArea, int x, int y);
