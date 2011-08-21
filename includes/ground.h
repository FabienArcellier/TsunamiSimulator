enum GROUND_TYPE {
  ground_type_unknown,
  ground_type_ground, 
  ground_type_water
};

typedef struct ground
{
  enum GROUND_TYPE type;
  int width;
  int length;
  double height;
  double dawning;
} Ground;

typedef Ground * PtrGround;

/*!
 * \brief Cree un terrain de 100m par 100m
 */
void ground_create (PtrGround*);

/*!
 * \brief Initialise un espace memoire deja reserve
 */
PtrGround ground_init (PtrGround);

/*!
 * \brief Detruit une instance de terrain
 */
void ground_destroy (PtrGround*);

/*!
 * \brief Configure le type d'un terrain
 */
void ground_set_type (PtrGround, enum GROUND_TYPE);

/*!
 * \brief Obtient le type d'un terrain
 */
enum GROUND_TYPE ground_get_type (PtrGround ground);

/*!
 * \brief Fixe la hauteur d'un terrain
 */
void ground_set_height (PtrGround, double);

/*!
 * \brief Retourne la hauteur d'un terrain
 */
double ground_get_height (PtrGround);

/*!
 * \brief Fixe l'absorbtion energétique du terrain (entre 0 et 1)
 */
void ground_set_dawning (PtrGround, double);

/*!
 * \brief Retourne le coefficient d'absorbtion du terrain
 */
double ground_get_dawning (PtrGround);


