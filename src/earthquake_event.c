#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "wave_signal.h"
#include "ground.h"
#include "event.h"
#include "earthquake_event.h"

/*!
 * \brief Cree une instance de type EarthquakeEvent
 */
void earthquake_event_create (PtrEarthquakeEvent* earthquake_event)
{
	//Initialise le parent
	*earthquake_event = (PtrEarthquakeEvent) malloc (sizeof (EarthquakeEvent));
	memset (*earthquake_event, 0, sizeof (EarthquakeEvent));
	event_init (EVENT (*earthquake_event));
	
	EVENT (*earthquake_event) -> Destroy = earthquake_event_destroy_parent;
	EVENT (*earthquake_event) -> Execute = earthquake_event_execute_parent;
	(*earthquake_event) -> Destroy = earthquake_event_destroy;
	(*earthquake_event) -> Execute = earthquake_event_execute;
}

/*!
 * \brief Detruit une instance de type EarthquakeEvent
 */
void earthquake_event_destroy (PtrEarthquakeEvent* earthquake_event)
{
	free (*earthquake_event);
	*earthquake_event = NULL;
}


/*!
 * \brief Detruit une instance de type EarthquakeEvent
 */
void earthquake_event_destroy_parent (PtrEvent* event)
{
	PtrEarthquakeEvent* earthquake_event = (PtrEarthquakeEvent*) event;
	(*earthquake_event) -> Destroy (earthquake_event);
}

/*!
 * \brief Assesseur en ecriture de l'attribut ground
 */
void earthquake_event_set_ground (PtrEarthquakeEvent earthquake_event, PtrGround ground)
{
	assert (earthquake_event != NULL);
	
	earthquake_event -> ground = ground;
}

/*!
 * \brief Assesseur en lecture de l'attribut ground
 */
PtrGround earthquake_event_get_ground (PtrEarthquakeEvent earthquake_event)
{
	return earthquake_event -> ground;
}

/*!
 * \brief Assesseur en ecriture de l'attribut energy
 */
void earthquake_event_set_energy (PtrEarthquakeEvent earthquake_event, double energy)
{
	assert (earthquake_event != NULL);
	
	earthquake_event -> energy = energy;
}

/*!
 * \brief Assesseur en lecture de l'attribut energy
 */
double earthquake_event_get_energy (PtrEarthquakeEvent earthquake_event)
{
	return earthquake_event -> energy;
}

/*!
 * \brief Fonction herite de event
 * 
 * Cette methode cree 9 wave signals dans 9 directions dont l'energy
 * egal energy / (4 * 9). On considere que le seisme ne transmet que 
 * 25% de son energie au tsunami d'où le 4.
 */
void earthquake_event_execute (PtrEarthquakeEvent earthquake_event)
{
	assert (earthquake_event != NULL);
	assert (earthquake_event_get_ground (earthquake_event) != NULL);
	
	PtrGround ground = earthquake_event_get_ground (earthquake_event);
	double energy = earthquake_event_get_energy (earthquake_event);
	double energy_wave = energy / (4 * 9);
	
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		PtrWaveSignal signal = NULL;
		int direction = i * 45;
		wave_signal_create (&signal);
		wave_signal_set_direction (signal, direction);
		wave_signal_set_energy (signal, energy_wave);
		ground_insert_signal (ground, signal);
	}
}

/*!
 * \brief Fonction herite de event
 */
void earthquake_event_execute_parent (PtrEvent event)
{
	earthquake_event_execute ((PtrEarthquakeEvent) event);
}