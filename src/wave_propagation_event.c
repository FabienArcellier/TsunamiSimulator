#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "angle.h"
#include "debug.h"
#include "event.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_neighbour.h"
#include "wave_propagation_event.h"

/*!
 * \brief Cree une instance de l'evenement de propagation d'une onde
 */
void wave_propagation_event_create (PtrWavePropagationEvent *wave_propagation_event, PtrGround ground, PtrWaveSignal wave_signal)
{
	assert (*wave_propagation_event == NULL);
	assert (ground != NULL);
	assert (wave_signal != NULL);
	
	*wave_propagation_event = (PtrWavePropagationEvent) malloc (sizeof (WavePropagationEvent));
	memset (*wave_propagation_event, 0, sizeof (WavePropagationEvent));
	
	wave_propagation_event_init (*wave_propagation_event, ground, wave_signal);
}

/*!
 * \brief Initialise les methodes de la structure
 */
void wave_propagation_event_init (PtrWavePropagationEvent wave_propagation_event, PtrGround ground, PtrWaveSignal wave_signal)
{
	event_init (EVENT (wave_propagation_event));
	EVENT (wave_propagation_event) -> Destroy = wave_propagation_event_destroy_parent;
	EVENT (wave_propagation_event) -> Execute = wave_propagation_event_execute_parent;
	wave_propagation_event -> Destroy = wave_propagation_event_destroy;
	wave_propagation_event -> Execute = wave_propagation_event_execute;
	wave_propagation_event -> ground = ground;
	wave_propagation_event -> wave_signal = wave_signal;
}

/*!
 * \brief detruit une instance de l'evenement
 */
void wave_propagation_event_destroy (PtrWavePropagationEvent *wave_propagation_event)
{
	assert (*wave_propagation_event != NULL);
	
	free (*wave_propagation_event);
	*wave_propagation_event = NULL;
}

/*!
 * \brief surcharge de event -> destroy avec un cast (appel de wave_propagation_event_destroy)
 */
void wave_propagation_event_destroy_parent (PtrEvent *event)
{
	PtrWavePropagationEvent *wave_propagation_event = (PtrWavePropagationEvent*) event;
	(*wave_propagation_event) -> Destroy (wave_propagation_event);
}

/*!
 * \brief retourne le terrain lié a l'onde à propager
 */
PtrGround wave_propagation_event_get_ground (PtrWavePropagationEvent wave_propagation_event)
{
	assert (wave_propagation_event != NULL);
	return wave_propagation_event -> ground;
}

/*!
 * \brief retourne la wave qui doit se propager
 */
PtrWaveSignal wave_propagation_event_get_wave_signal (PtrWavePropagationEvent wave_propagation_event)
{
	assert (wave_propagation_event != NULL);
	return wave_propagation_event -> wave_signal;
}

/*!
 * \brief Declenche la propagation des ondes vers les cases voisines
 */
void wave_propagation_event_execute (PtrWavePropagationEvent wave_propagation_event)
{
	assert (wave_propagation_event != NULL);
	
	PtrGround ground = wave_propagation_event_get_ground (wave_propagation_event);
	PtrWaveSignal wave_signal = wave_propagation_event_get_wave_signal (wave_propagation_event);
	int time_remaining = 1000.0; // en millisecond
	
	if (wave_signal != NULL)
	{
		double energy_before_processing = wave_signal_get_energy (wave_signal);
		wave_propagation_event_dispatch_wave_neighbours (ground -> ground_neighbour,
																										wave_signal,
																										time_remaining);
		
		
		if (wave_signal_get_energy (wave_signal) == energy_before_processing)
		{
			wave_signal_set_energy (wave_signal, 0.0);
		}
	}
}

/*!
 * \brief surcharge de event -> execute avec un cast (appel de wave_propagation_event_execute)
 */
void wave_propagation_event_execute_parent (PtrEvent event)
{
	PtrWavePropagationEvent wave_propagation_event = (PtrWavePropagationEvent) event;
	wave_propagation_event -> Execute (wave_propagation_event);
}

void wave_propagation_event_dispatch_wave_neighbours (PtrGroundNeighbour list_neighbours, 
																								 PtrWaveSignal wave_signal, 
																								 int time_remaining)
{
	assert (wave_signal != NULL);
	
	if (time_remaining <= 0 || list_neighbours == NULL)
	{
		return;
	}
	else
	{
		double total_energy_repartition = 0.0;
// 		DEBUG_IF (1, "%d", time_remaining);
		
		PtrGround ground_main = ground_neighbour_get_main (list_neighbours);
		int height = ground_get_height (ground_main);
		double dawning = ground_get_dawning (ground_main);
		double wave_speed = wave_propagation_event_get_wave_speed (height);
		
		PtrGroundNeighbour neighbour = list_neighbours;
		
		double wave_direction = wave_signal_get_direction (wave_signal);
		
		while (neighbour != NULL)
		{
			double neighbour_direction = ground_neighbour_get_direction (neighbour);
			total_energy_repartition += wave_propagation_event_calculate_ratio_energy (wave_direction, neighbour_direction);
			neighbour = ground_neighbour_get_next (neighbour);
		}
		
		neighbour = list_neighbours;
		
		double energy = wave_signal_get_energy (wave_signal);
		
		while (neighbour != NULL && total_energy_repartition >= 1.0)
		{
			double neighbour_direction = ground_neighbour_get_direction (neighbour);
			double local_energy_repartition = 0.0;
			local_energy_repartition = wave_propagation_event_calculate_ratio_energy (wave_direction, neighbour_direction);
			double ratio_energy = local_energy_repartition / total_energy_repartition;
			double energy_to_transfer = energy * ratio_energy;
			PtrGround ground_neighbour = ground_neighbour_get_neighbour (neighbour);
			double distance_to_do = ground_neighbour_get_distance (neighbour) - wave_signal_get_distance (wave_signal);
			
			if (energy_to_transfer >= 500.0)
			{
				/*DEBUG_IF (1, "%f", "energy_to_transfer");
				DEBUG_IF (1, "%f", total_energy_repartition);
				DEBUG_IF (1, "%f", local_energy_repartition);*/
				PtrWaveSignal new_wave_signal = NULL;
				double energy_that_stay = wave_signal_get_energy (wave_signal);
				wave_signal_create (&new_wave_signal);
				wave_signal_set_direction (new_wave_signal, wave_direction);
				wave_signal_set_energy (new_wave_signal, energy_to_transfer * dawning);
				if ((energy_that_stay - energy_to_transfer) * 11.0 < energy)
				{
					wave_signal_set_energy (wave_signal, 0.0);
				}
				else
				{
					wave_signal_set_energy (wave_signal, energy_that_stay - energy_to_transfer);
				}
				
				int new_time_remaining = time_remaining - (int)((distance_to_do / wave_speed) * 1000);
				if (new_time_remaining > 0)
				{
					wave_signal_set_distance (new_wave_signal, 0.0);
					ground_insert_signal (ground_neighbour, new_wave_signal);
					wave_propagation_event_dispatch_wave_neighbours (ground_neighbour -> ground_neighbour, 
																													new_wave_signal, 
																													new_time_remaining);
				}
				else
				{
					double distance_done = (((double) time_remaining) / 1000) * wave_speed;
// 					DEBUG_IF (1, "%d", time_remaining);
// 					DEBUG_IF (1, "%f", wave_speed);
// 					DEBUG_IF (1, "%f", distance_done);
					wave_signal_set_distance (new_wave_signal, distance_done);
					ground_insert_signal (ground_main, new_wave_signal);
				}
			}
			neighbour = ground_neighbour_get_next (neighbour);
		}
	}
}

/*!
 * \brief Calcule un ratio entre 0 et 1 permettant de calculer la repartition de l'energie entre plusieurs voisins
 */
double wave_propagation_event_calculate_ratio_energy (double wave_direction, double neighbour_direction)
{
	assert (wave_direction >=0 && wave_direction < 360.0);
	
	assert (neighbour_direction >= 0 && neighbour_direction <= 360.0);
	double delta_direction = angle_shortener_rotation (wave_direction, neighbour_direction);
	double result = 0.0;
	if (delta_direction < -75.0 || delta_direction > 75.0)
	{
		result = 0.0;
	}
	else if (delta_direction < 0)
	{
		result = 1.0 - (fabs (delta_direction) / 75.0);
	}
	else
	{ 
		result = 1.0 - (fabs (delta_direction) /75.0);
	}
	
	//DEBUG_IF ((result <= 1.0 && result >= 0.0) == 0, "%f", result);
	assert (result <= 1.0 && result >= 0.0);
	
	return result;
}

/*!
 * \brief retourne la vitesse de deplacement de l'onde sur un terrain donne (m/s)
 */
double wave_propagation_event_get_wave_speed (int height)
{
	return sqrt (9.81 * abs(height));
}