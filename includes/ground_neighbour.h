#ifndef GROUND_NEIGHBOUR_H
#define GROUND_NEIGHBOUR_H 

typedef struct ground_neighbour
{
	PtrGround main;
	PtrGround neighbour;
	double direction;
	double distance;
	struct ground_neighbour *next;
} GroundNeighbour;

typedef GroundNeighbour * PtrGroundNeighbour;

/*!
 * \brief Cree une instance de type voisin à partir du proprietaire et du voisin
 */
void ground_neighbour_create (PtrGroundNeighbour*, PtrGround owner, PtrGround neighbour);

/*!
 * \brief Detruit une instance
 */
void ground_neighbour_destroy (PtrGroundNeighbour*);

/*!
 * \brief Retourne le terrain principal
 */
PtrGround ground_neighbour_get_main (PtrGroundNeighbour);

/*!
 * \brief Retourne le terrain voisin
 */
PtrGround ground_neighbour_get_neighbour (PtrGroundNeighbour);

/*!
 * \brief Calcule la direction du voisin par rapport au terrain d'origine.
 * 0 represente le nord, on tourne dans le sens des aiguilles d'une montre entre 0 et 360
 */
void ground_neighbour_calculate_direction (PtrGroundNeighbour);

/*!
 * \brief Retourne la direction entre les 2 voisins
 */
double ground_neighbour_get_direction (PtrGroundNeighbour);

/*!
 * \brief Calcule la distance qui sépare un terrain de son voisin
 */
void ground_neighbour_calculate_distance (PtrGroundNeighbour);

/*!
 * \brief Retourne la distance entre les 2 voisins
 */
double ground_neighbour_get_distance (PtrGroundNeighbour);

/*!
 * \brief Assesseur en lecture de l'attribut next
 */
PtrGroundNeighbour ground_neighbour_get_next (PtrGroundNeighbour);

/*!
 * \brief Assesseur en ecriture de l'attribut next
 */
void ground_neighbour_set_next (PtrGroundNeighbour, PtrGroundNeighbour);

/*!
 * \brief Insere un element de type PtrGroundNeighbour en tete
 * Accepte NULL en premier argument
 */
PtrGroundNeighbour ground_neighbour_insert (PtrGroundNeighbour, PtrGroundNeighbour);

#endif