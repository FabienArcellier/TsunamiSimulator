#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_neighbour.h"
#include "ground_area.h"
#include "event.h"
#include "timeline.h"
#include "wave_propagation_event.h"

/*!
 * \brief Parcours une aire et pour chaque onde, enregistre un evenement
 * 	de propagation (wave_propagation_event)
 */
void register_events_for_propagation_on_timeline_from_ground_area (
	PtrTimeline timeline, 
	PtrGroundArea ground_area)
{
	assert (timeline != NULL);
	assert (ground_area != NULL);
	
	int array_width = ground_area -> array_width;
	int array_length = ground_area -> array_length;
	int time = timeline_get_current_time (timeline);
	
	int i = 0, j = 0;
	for (i = 0; i < array_width; i++)
	{
		for (j = 0; j < array_length; j++)
		{
			PtrGround ground = ground_area_get_ground (ground_area, i, j);
			PtrWaveSignal signal = ground_get_wave_signals (ground);
			while (signal != NULL)
			{
				PtrWavePropagationEvent wave_propagation_event = NULL;
				
				wave_propagation_event_create (&wave_propagation_event, ground, signal);
				event_set_time (EVENT (wave_propagation_event), time);
				timeline_insert_event (timeline, EVENT (wave_propagation_event));
				signal = wave_signal_get_next_wave_signal (signal);
			}
		}
	}
}

/*!
 * \brief Rassemble les waves signals qui ont la meme direction et la meme longueur d'onde
 */
void simplify_wave_signals_after_propagation_on_ground_area (PtrGroundArea ground_area)
{
	assert (ground_area != NULL);
	
	int array_width = ground_area -> array_width;
	int array_length = ground_area -> array_length;
	
	int i = 0, j = 0;
	for (i = 0; i < array_width; i++)
	{
		for (j = 0; j < array_length; j++)
		{
			PtrGround ground = ground_area_get_ground (ground_area, i, j);
			PtrWaveSignal signal_racine = ground_get_wave_signals (ground);
			PtrWaveSignal signal_current = signal_racine;
			int change_done = 1;
			
			while (change_done == 1 && signal_current != NULL)
			{
				double direction_current = wave_signal_get_direction (signal_current);
				double length_current = wave_signal_get_length (signal_current);
				double energy_current = wave_signal_get_energy (signal_current);
				double distance_current = wave_signal_get_distance (signal_current);
				PtrWaveSignal signal_to_compare = signal_current;
				
				change_done = 0;
				if (energy_current < 0.1)
				{
					PtrWaveSignal signal_to_destroy = signal_current;
					signal_racine = wave_signal_delete_wave_signal (signal_racine, signal_current);
					signal_current = wave_signal_get_next_wave_signal (signal_current);
					wave_signal_set_next_wave_signal (signal_to_destroy, NULL);
					wave_signal_destroy (&signal_to_destroy);
					
					change_done = 1;
				}
				else
				{
					while (signal_to_compare != NULL)
					{
// 						DEBUG_IF(1, "%p", signal_to_compare);
// 						DEBUG_IF(1, "%p", signal_current);
						if (signal_to_compare == signal_current)
						{
							signal_to_compare = wave_signal_get_next_wave_signal (signal_to_compare);
							continue;
						}
						
						double length_reference = wave_signal_get_length (signal_to_compare);
						double direction_reference = wave_signal_get_direction (signal_to_compare);
						double distance_reference = wave_signal_get_distance (signal_to_compare);
						
						// Transfere l'energie sur une instance qui possede les memes parametres
						if (direction_current == direction_reference &&
							length_current == length_reference &&
							distance_reference <= distance_current + 25 &&
							distance_reference >= distance_current - 25)
						{
							double energy_reference = wave_signal_get_energy (signal_to_compare);
							energy_current = wave_signal_get_energy (signal_current);
							wave_signal_set_energy (signal_current, energy_reference + energy_current);
							signal_current = wave_signal_delete_wave_signal (signal_current, signal_to_compare);
							PtrWaveSignal signal_to_destroy = signal_to_compare;
							signal_to_compare = wave_signal_get_next_wave_signal (signal_to_compare);
							wave_signal_set_next_wave_signal (signal_to_destroy, NULL);
							wave_signal_destroy (&signal_to_destroy);
							change_done = 1;
						}
						else
						{
							signal_to_compare = wave_signal_get_next_wave_signal (signal_to_compare);
						}
					}
					
					signal_current = wave_signal_get_next_wave_signal (signal_current);
				}
			}
			
			ground_set_wave_signals (ground, signal_racine);
		}
	}
}