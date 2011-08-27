#include "debug.h"
#include "test.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "event.h"
#include "earthquake_event.h"

/* Prototype des fonctions de tests */
void earthquake_event_create_destroy_test ();
void earthquake_event_configure_test ();
void earthquake_event_execute_test ();

int main (void)
{
	earthquake_event_create_destroy_test ();
	earthquake_event_configure_test ();
	earthquake_event_execute_test ();
	return 0;
}

void earthquake_event_create_destroy_test ()
{
	TEST_TITLE ("earthquake_event_create_destroy_test");
	
	PtrEarthquakeEvent earthquake_event = NULL;
	earthquake_event_create (&earthquake_event);
	TEST (earthquake_event != NULL);
	
	
	earthquake_event -> Destroy (&earthquake_event);
	TEST (earthquake_event == NULL);
}

void earthquake_event_configure_test ()
{
	TEST_TITLE ("earthquake_event_configure_test");
	PtrEarthquakeEvent earthquake_event = NULL;
	earthquake_event_create (&earthquake_event);
	
	PtrGroundArea ground_area = NULL;
	ground_area_create (&ground_area, 10000, 10000);
	PtrGround ground = ground_area_get_ground (ground_area, 10, 10);
	
	earthquake_event_set_energy (earthquake_event, 100000.0);
	earthquake_event_set_ground (earthquake_event, ground);
	event_set_time (EVENT (earthquake_event), 5);
	
	double energy = earthquake_event_get_energy (earthquake_event);
	int time = event_get_time (EVENT (earthquake_event));
	PtrGround ground_stored = earthquake_event_get_ground (earthquake_event);
	
	TEST (energy == 100000.0);
	TEST (ground_stored == ground);
	TEST (time == 5);
	
	earthquake_event -> Destroy (&earthquake_event);
	ground_area_destroy (&ground_area);
}

void earthquake_event_execute_test ()
{
	TEST_TITLE ("earthquake_event_execute_test");
	
	PtrEarthquakeEvent earthquake_event = NULL;
	earthquake_event_create (&earthquake_event);
	
	PtrGroundArea ground_area = NULL;
	ground_area_create (&ground_area, 10000, 10000);
	PtrGround ground = ground_area_get_ground (ground_area, 10, 10);
	
	earthquake_event_set_energy (earthquake_event, 100000.0);
	earthquake_event_set_ground (earthquake_event, ground);
	event_set_time (EVENT (earthquake_event), 5);
	
	earthquake_event -> Execute (earthquake_event);
	
	PtrWaveSignal signals = ground_get_wave_signals (ground);
	
	TEST (signals != NULL);
	double energy = wave_signal_get_energy (signals);
	DEBUG_IF ((energy == (100000.0/(4 * 9))) == 0, "%f", energy);
	TEST (energy == (100000.0/(4 * 9)));
	
	earthquake_event -> Destroy (&earthquake_event);
	ground_area_destroy (&ground_area);
}