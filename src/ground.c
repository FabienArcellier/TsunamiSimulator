#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_neighbour.h"

/*!
 * \brief Cree un terrain de 100m par 100m
 */
void ground_create (PtrGround *ground)
{
  assert (*ground == NULL);
  *ground = (PtrGround) malloc (sizeof (Ground));
  memset (*ground, 0, sizeof (Ground));
  
  *ground = ground_init (*ground);
}

/*!
 * \brief Initialise un espace memoire deja reserve
 */
PtrGround ground_init (PtrGround ground)
{
  assert (ground != NULL);
  
  ground -> type = ground_type_water;
  ground -> width = 100;
  ground -> length = 100;
  ground -> height = -3000.0;
  ground -> dawning = 1.0;
  
  return ground;
}

/*!
 * \brief Detruit une instance de terrain
 */
void ground_destroy (PtrGround *ground)
{
  assert (*ground != NULL);
  
  free (*ground);
  *ground = NULL;
}

/*!
 * \brief Configure le type d'un terrain
 */
void ground_set_type (PtrGround ground, enum GROUND_TYPE ground_type)
{
  assert (ground != NULL);
  
  ground -> type = ground_type; 
}

/*!
 * \brief Obtient le type d'un terrain
 */
enum GROUND_TYPE ground_get_type (PtrGround ground)
{
  assert (ground != NULL);
  
  return ground -> type;
}

/*!
 * \brief Assesseur en ecriture de la position X
 */
void ground_set_position_X (PtrGround ground, int positionX)
{
	assert (ground != NULL);
	assert (positionX >= 0);
	
	ground -> positionX = positionX;
}

/*!
 * \brief Assesseur en lecture de la position X
 */
int ground_get_position_X (PtrGround ground)
{
	return ground -> positionX;
}

/*!
 * \brief Assesseur en ecriture de la position Y
 */
void ground_set_position_Y (PtrGround ground, int positionY)
{
	assert (ground != NULL);
	assert (positionY >= 0);
	
	ground -> positionY = positionY;
}

/*!
 * \brief Assesseur en lecture de la position Y
 */
int ground_get_position_Y (PtrGround ground)
{
	assert (ground != NULL);
	return ground -> positionY;
}

/*!
 * \brief Assesseur en ecriture de l'attribut width
 */
void ground_set_width (PtrGround ground, int width) 
{
	assert (ground != NULL);
	assert (width >= 0);
	
	ground -> width = width;
}

/*!
 * \brief Assesseur en lecture de l'attribut width
 */
int ground_get_width (PtrGround ground)
{
	assert (ground != NULL);
	
	return ground -> width;
}

/*!
 * \brief Assesseur en ecriture de l'attribut length
 */
void ground_set_length (PtrGround ground, int length)
{
	assert (ground != NULL);
	assert (length >= 0);
	
	ground -> length = length;
}

/*!
 * \brief Assesseur en lecture de l'attribut length
 */
int ground_get_length (PtrGround ground)
{
	assert (ground != NULL);
	
	return ground -> length;
}

/*!
 * \brief Fixe la hauteur d'un terrain
 */
void ground_set_height (PtrGround ground, double height)
{
  assert (ground != NULL);
  ground -> height = height;
  
}

/*!
 * \brief Retourne la hauteur d'un terrain
 */
double ground_get_height (PtrGround ground)
{
  return ground -> height;
}

/*!
 * \brief Fixe l'absorbtion energétique du terrain (entre 0 et 1)
 */
void ground_set_dawning (PtrGround ground, double dawning)
{
  assert (ground != NULL);
  assert (dawning >= 0.0 && dawning <= 1.0);
  
  ground -> dawning = dawning;
}

/*!
 * \brief Retourne le coefficient d'absorbtion du terrain
 */
double ground_get_dawning (PtrGround ground)
{
  return ground -> dawning;
}

/*!
 * \brief Assesseur de l'attribut wave_signal rattache a un terrain
 */
void ground_set_wave_signals (PtrGround ground, PtrWaveSignal list_wave_signal)
{
	assert (ground != NULL);
	ground -> list_wave_signal = list_wave_signal;
}

/*!
 * \brief Assesseur de l'attribut wave_signal rattache a un terrain
 */
PtrWaveSignal ground_get_wave_signals (PtrGround ground)
{
	assert (ground != NULL);
	return ground -> list_wave_signal;
}

/*!
 * \brief Insere un signal sur un terrain
 */
void ground_insert_signal (PtrGround ground, PtrWaveSignal signal)
{
	assert (ground != NULL);
	assert (signal != NULL);
	PtrWaveSignal wave_signals = ground_get_wave_signals (ground);
	wave_signals = wave_signal_insert_wave_signal_sort_by_length_asc (wave_signals, signal);
	ground_set_wave_signals (ground, wave_signals);
}

/*!
 * \brief Insere un voisin dans la liste des voisins
 */
void ground_insert_ground_neighbour (PtrGround ground, PtrGround neighbour)
{
	assert (ground != NULL);
	assert (neighbour != NULL);
	
	PtrGroundNeighbour ground_neighbour = NULL;
	ground_neighbour_create (&ground_neighbour, ground, neighbour);
	
	ground -> ground_neighbour = ground_neighbour_insert(ground -> ground_neighbour, ground_neighbour);
}
