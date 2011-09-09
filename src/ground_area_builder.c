#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_builder.h"

/*!
 * \brief Cree une instance de type GroundAreaBuilder
 */
void ground_area_builder_create (PtrGroundAreaBuilder *ground_area_builder)
{
}

/*!
 * \brief Detruit une instance de type GroundAreaBuilder
 */
void ground_area_builder_destroy (PtrGroundAreaBuilder *ground_area_builder)
{
}

/*!
 * \brief Renvoie le terrain genere
 * Si le terrain n'a pas ete genere alors renvoie NULL
 */
PtrGroundAreaBuilder ground_area_builder_get_ground_area (PtrGroundAreaBuilder ground_area_builder)
{
	return NULL;
}

/*!
 * \brief Renvoie la largeur en m
 */
int ground_area_builder_get_width (PtrGroundAreaBuilder ground_area_builder)
{
	return -1;
}

/*!
 * \brief Definit la largeur en m
 */
void ground_area_builder_set_width (PtrGroundAreaBuilder ground_area_builder, int width)
{
}

/*!
 * \brief Renvoie la hauteur en m
 */
int ground_area_builder_get_height (PtrGroundAreaBuilder ground_area_builder)
{
	return -1;
}

/*!
 * \brief Definit la largeur de la carte en m
 */
void ground_area_builder_set_height (PtrGroundAreaBuilder ground_area_builder, int height)
{
}

/*!
 * \brief Position de l'eau entre 0 et 1
 */
double ground_area_builder_get_water_position (PtrGroundAreaBuilder ground_area_builder)
{
	return 0.0;
}

/*!
 * \brief Assesseur en ecriture de la position de l'eau, defini entre 0 et 1
 */
void ground_area_builder_set_water_position (PtrGroundAreaBuilder ground_area_builder, double water_position)
{
}

/*!
 * \brief Renvoie le type de la carte a generer
 */
GroundAreaBuilderGroundType ground_area_builder_get_type (PtrGroundAreaBuilder ground_area_builder)
{
	return Island;
}

/*!
 * \brief Definit le type de la carte a generer
 */
void ground_area_builder_set_type (PtrGroundAreaBuilder ground_area_builder, GroundAreaBuilderGroundType type)
{
}