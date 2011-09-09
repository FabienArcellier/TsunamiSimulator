#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_neighbour.h"

/*!
 * \brief Cree une instance de type voisin à partir du proprietaire et du voisin
 */
void ground_neighbour_create (PtrGroundNeighbour *ground_neighbour, PtrGround main, PtrGround neighbour)
{
	assert (*ground_neighbour == NULL);
	assert (main != NULL);
	assert (neighbour != NULL);
	
	*ground_neighbour = (PtrGroundNeighbour) malloc (sizeof (GroundNeighbour));
	memset (*ground_neighbour, 0, sizeof (GroundNeighbour));
	
	(*ground_neighbour) -> main = main;
	(*ground_neighbour) -> neighbour = neighbour;
	ground_neighbour_calculate_distance (*ground_neighbour);
	ground_neighbour_calculate_direction (*ground_neighbour);
	
}

/*!
 * \brief Detruit une instance
 */
void ground_neighbour_destroy (PtrGroundNeighbour *ground_neighbour)
{
	if ((*ground_neighbour) -> next != NULL)
	{
		PtrGroundNeighbour next = (*ground_neighbour) -> next;
		ground_neighbour_destroy (&next);
	}
	
	free (*ground_neighbour);
	*ground_neighbour = NULL;
}

/*!
 * \brief Retourne le terrain principal
 */
PtrGround ground_neighbour_get_main (PtrGroundNeighbour ground_neighbour)
{
	assert (ground_neighbour != NULL);
	assert (ground_neighbour -> main != NULL);
	
	return ground_neighbour -> main;
}

/*!
 * \brief Retourne le terrain voisin
 */
PtrGround ground_neighbour_get_neighbour (PtrGroundNeighbour ground_neighbour)
{
	assert (ground_neighbour != NULL);
	assert (ground_neighbour -> neighbour != NULL);
	
	return ground_neighbour -> neighbour;
}

/*!
 * \brief Calcule la direction du voisin par rapport au terrain d'origine.
 * 0 represente le nord, on tourne dans le sens des aiguilles d'une montre entre 0 et 360
 */
void ground_neighbour_calculate_direction (PtrGroundNeighbour ground_neighbour)
{
	PtrGround ground_main = NULL, neighbour = NULL;
	
	ground_main = ground_neighbour_get_main (ground_neighbour);
	neighbour = ground_neighbour_get_neighbour (ground_neighbour);
	
	// Calcul du point de reference dans le terrain principal
	int x_main = 0, y_main = 0;
	x_main = ground_get_position_X (ground_main);
	x_main += (int) (ground_get_width (ground_main) / 2);
	y_main = ground_get_position_Y (ground_main);
	y_main += (int) (ground_get_length (ground_main) / 2);
	
	// Calcul du point de reference dans le terrain voisin
	int x_neighbour = 0, y_neighbour = 0;
	x_neighbour = ground_get_position_X (neighbour);
	x_neighbour += (int) (ground_get_width (neighbour) / 2);
	y_neighbour = ground_get_position_Y (neighbour);
	y_neighbour += (int) (ground_get_length (neighbour) / 2);
	
	// Calcul hypothenus (distance)
	double distance = 0.0;
	distance = (x_neighbour - x_main) *  (x_neighbour - x_main);
	distance += (y_neighbour - y_main) *  (y_neighbour - y_main);
	distance = sqrt (distance);
	
	// Calcul cote adjacent
	int adjacent = 0.0;
	adjacent = x_neighbour - x_main;
	
	// Calcul cote oppose
	int oppose = 0.0;
	oppose = y_neighbour - y_main;
	
	// Calcul du cosinus
	double cos_direction = adjacent / distance;
	
	double direction = acos (cos_direction) * (180/3.14);
	
	if (oppose < 0)
	{
		direction = fmod(-direction, 360.0);
	}
	
	// Decalage de repere pour optenir l'angle 0 au nord
	direction = fmod(direction + 90.0, 360.0);
	if (direction < 0.0)
	{
		direction = direction + 360.0;
	}
	
	ground_neighbour -> direction = direction;
}

/*!
 * \brief Retourne la direction entre les 2 voisins
 */
double ground_neighbour_get_direction (PtrGroundNeighbour ground_neighbour)
{
	assert (ground_neighbour != NULL);
	
	return ground_neighbour -> direction;
}

/*!
 * \brief Calcule la distance qui sépare un terrain de son voisin
 */
void ground_neighbour_calculate_distance (PtrGroundNeighbour ground_neighbour)
{
	PtrGround ground_main = NULL, neighbour = NULL;
	
	ground_main = ground_neighbour_get_main (ground_neighbour);
	neighbour = ground_neighbour_get_neighbour (ground_neighbour);
	
	// Calcul du point de reference dans le terrain principal
	int x_main = 0, y_main = 0;
	x_main = ground_get_position_X (ground_main);
	x_main += (int) (ground_get_width (ground_main) / 2);
	y_main = ground_get_position_Y (ground_main);
	y_main += (int) (ground_get_length (ground_main) / 2);
	
	// Calcul du point de reference dans le terrain voisin
	int x_neighbour = 0, y_neighbour = 0;
	x_neighbour = ground_get_position_X (neighbour);
	x_neighbour += (int) (ground_get_width (neighbour) / 2);
	y_neighbour = ground_get_position_Y (neighbour);
	y_neighbour += (int) (ground_get_length (neighbour) / 2);
	
	// Calcul hypothenus (distance)
	double distance = 0.0;
	distance = (x_neighbour - x_main) *  (x_neighbour - x_main);
	distance += (y_neighbour - y_main) *  (y_neighbour - y_main);
	distance = sqrt (distance);
	
	distance = fabs (distance);
	ground_neighbour -> distance = distance;
	
}

/*!
 * \brief Retourne la distance entre les 2 voisins
 */
double ground_neighbour_get_distance (PtrGroundNeighbour ground_neighbour)
{
	assert (ground_neighbour != NULL);
	
	return ground_neighbour -> distance;
}

/*!
 * \brief Assesseur en lecture de l'attribut next
 */
PtrGroundNeighbour ground_neighbour_get_next (PtrGroundNeighbour ground_neighbour)
{
	return ground_neighbour -> next;
}

/*!
 * \brief Assesseur en ecriture de l'attribut next
 */
void ground_neighbour_set_next (PtrGroundNeighbour ground_neighbour, PtrGroundNeighbour ground_neighbour_next)
{
	assert (ground_neighbour != NULL);
	
	ground_neighbour -> next = ground_neighbour_next;
}

/*!
 * \brief Insere un element de type PtrGroundNeighbour en tete
 * Accepte NULL en premier argument
 */
PtrGroundNeighbour ground_neighbour_insert (PtrGroundNeighbour list_ground_neighbour, PtrGroundNeighbour ground_neighbour_to_insert)
{
	assert (ground_neighbour_to_insert != NULL);
	
	ground_neighbour_set_next(ground_neighbour_to_insert, list_ground_neighbour);
	return ground_neighbour_to_insert;
}