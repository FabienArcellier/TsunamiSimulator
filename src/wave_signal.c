#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "wave_signal.h"

/*!
 * \brief cree une instance de type wave_signal
 */
void wave_signal_create (PtrWaveSignal *wave_signal)
{
	assert (*wave_signal == NULL);
	
	*wave_signal = (PtrWaveSignal) malloc (sizeof (WaveSignal));
	memset (*wave_signal, 0, sizeof (WaveSignal));
}

/*!
 * \brief detruit une instance et ses liens de type wave_signal
 */
void wave_signal_destroy (PtrWaveSignal *wave_signal)
{
	assert (*wave_signal != NULL);
	PtrWaveSignal next = (*wave_signal) -> next;
	if (next != NULL)
	{
		wave_signal_destroy (&next);
	}
	
	free (*wave_signal);
	*wave_signal = NULL;
}

/*!
 * \brief Assesseur d'ecriture de energy
 */
void wave_signal_set_energy (PtrWaveSignal wave_signal, double energy)
{
	assert (wave_signal != NULL);
	DEBUG_IF ((energy >= -0.2) == 0, "%f", energy);
	assert (energy >= -0.2);
	
	wave_signal -> energy = energy;
}

/*!
 * \brief Assesseur de lecture de energy
 */
double wave_signal_get_energy (PtrWaveSignal wave_signal)
{
	assert (wave_signal != NULL);
	return wave_signal -> energy;
}

/*!
 * \brief Assesseur d'ecriture de la frequence de l'onde
 */
void wave_signal_set_length (PtrWaveSignal wave_signal, double length)
{
	assert (wave_signal != NULL);
	assert (length >= 0);
	
	wave_signal -> length = length;
}

/*!
 * \brief Assesseur de lecture de la frequence de l'onde
 */
double wave_signal_get_length (PtrWaveSignal wave_signal)
{
	assert (wave_signal != NULL);
	
	return wave_signal -> length;
}

/*!
 * \brief Assesseur d'ecriture de l'attribut direction (en degree)
 * 
 * La direction est modulé par 360.
 */
void wave_signal_set_direction (PtrWaveSignal wave_signal, double direction)
{
	assert (wave_signal != NULL);
	
	double direction_module = (direction / 360.0);
	direction_module = (direction_module - (int) direction_module) * 360.0;
	wave_signal -> direction = direction_module;
}

/*!
 * \brief Assesseur de lecture de l'attribut direction (en degree)
 */
double wave_signal_get_direction (PtrWaveSignal wave_signal)
{
	assert (wave_signal != NULL);
	
	return wave_signal -> direction;
}

/*!
 * \brief Assesseur d'ecriture de la distance sur la case
 */
void wave_signal_set_distance (PtrWaveSignal wave_signal, double distance)
{
	assert (wave_signal != NULL);
	assert (distance >= 0.0);
	
	wave_signal -> distance = distance;
}

/*!
 * \brief Assesseur de lecture de la distance sur la case
 */
double wave_signal_get_distance (PtrWaveSignal wave_signal)
{
	assert (wave_signal != NULL);
	return wave_signal -> distance;
}

/*!
 * \brief Assesseur d'ecriture de l'attribut next
 */
void wave_signal_set_next_wave_signal (PtrWaveSignal wave_signal, PtrWaveSignal wave_signal_to_set)
{
	assert (wave_signal != NULL);
	
	wave_signal -> next = wave_signal_to_set;
}

/*!
 * \brief Assesseur de lecture de l'attribut next
 */
PtrWaveSignal wave_signal_get_next_wave_signal (PtrWaveSignal wave_signal)
{
	assert (wave_signal != NULL);
	return wave_signal -> next;
}

/*!
 * \brief Insere une instance de type wave signal dans une liste
 * 
 * Cette methode presuppose que la liste est deja ordonne par frequence croissante
 * Accepte l'argument NULL pour wave_signal
 */
PtrWaveSignal wave_signal_insert_wave_signal_sort_by_length_asc (PtrWaveSignal wave_signal, PtrWaveSignal wave_signal_to_insert)
{
	assert (wave_signal_to_insert != NULL);
	
	if (wave_signal == NULL)
	{
		return wave_signal_to_insert;
	}
	else if (wave_signal_to_insert -> length <= wave_signal -> length)
	{
		wave_signal_set_next_wave_signal (wave_signal_to_insert, wave_signal);
		return wave_signal_to_insert;
	}
	else
	{
		PtrWaveSignal wave_signal_result = wave_signal_insert_wave_signal_sort_by_length_asc (
			wave_signal -> next, 
			wave_signal_to_insert);
		
		wave_signal_set_next_wave_signal (wave_signal, wave_signal_result);
		return wave_signal;
	}
}

/*!
 * \brief Supprime un signal de la liste chainée
 */
PtrWaveSignal wave_signal_delete_wave_signal (PtrWaveSignal wave_signal, PtrWaveSignal wave_signal_to_delete)
{
	assert (wave_signal_to_delete != NULL);
	if (wave_signal == NULL)
	{
		return NULL;
	}
	else if (wave_signal == wave_signal_to_delete)
	{
		return wave_signal_get_next_wave_signal (wave_signal);
	}
	else
	{
		PtrWaveSignal new_next = wave_signal_delete_wave_signal (wave_signal_get_next_wave_signal (wave_signal), wave_signal_to_delete);
		wave_signal_set_next_wave_signal (wave_signal, new_next);
		return wave_signal;
	}
}