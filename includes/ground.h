#ifndef GROUND_H
#define GROUND_H

enum GROUND_TYPE {
  ground_type_unknown,
  ground_type_ground, 
  ground_type_water
};

typedef struct ground
{
  enum GROUND_TYPE type;
  int positionX;
  int positionY;
	int width;
	int length;
  double height;
  double dawning;
	struct ground_neighbour *ground_neighbour;
	PtrWaveSignal list_wave_signal;
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
 * \brief Assesseur en ecriture de la position X
 */
void ground_set_position_X (PtrGround, int);

/*!
 * \brief Assesseur en lecture de la position X
 */
int ground_get_position_X (PtrGround);

/*!
 * \brief Assesseur en ecriture de la position Y
 */
void ground_set_position_Y (PtrGround, int);

/*!
 * \brief Assesseur en lecture de la position Y
 */
int ground_get_position_Y (PtrGround);

/*!
 * \brief Assesseur en ecriture de l'attribut width
 */
void ground_set_width (PtrGround, int);

/*!
 * \brief Assesseur en lecture de l'attribut width
 */
int ground_get_width (PtrGround);

/*!
 * \brief Assesseur en ecriture de l'attribut length
 */
void ground_set_length (PtrGround, int);

/*!
 * \brief Assesseur en lecture de l'attribut length
 */
int ground_get_length (PtrGround);

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

/*!
 * \brief Assesseur de l'attribut list_wave_signal rattache a un terrain
 */
void ground_set_wave_signals (PtrGround, PtrWaveSignal);

/*!
 * \brief Assesseur de l'attribut list_wave_signal rattache a un terrain
 */
PtrWaveSignal ground_get_wave_signals (PtrGround);

/*!
 * \brief Insere un signal sur un terrain
 */
void ground_insert_signal (PtrGround, PtrWaveSignal);

/*!
 * \brief Insere un voisin dans la liste des voisins
 */
void ground_insert_ground_neighbour (PtrGround, PtrGround);

#endif
