#include "debug.h"
#include "test.h"
#include "wave_signal.h"
#include "event.h"
#include "ground.h"
#include "ground_neighbour.h"
#include "wave_propagation_event.h"

/* Prototypes des fonctions de tests */
void wave_propagation_event_create_destroy_tests ();
void wave_propagation_event_execute_test ();
void wave_propagation_event_calculate_ratio_energy_tests ();
void wave_propagation_event_get_wave_speed_tests ();

int main (void)
{
	wave_propagation_event_create_destroy_tests ();
	wave_propagation_event_execute_test ();
	wave_propagation_event_calculate_ratio_energy_tests();
	return 0;
}

void wave_propagation_event_create_destroy_tests ()
{
	TEST_TITLE ("wave_propagation_event_create_destroy_tests");
	PtrWaveSignal wave_signal = NULL;
	wave_signal_create (&wave_signal);
	
	PtrGround ground = NULL;
	ground_create (&ground);
	ground_insert_signal (ground, wave_signal);
	
	PtrWavePropagationEvent wave_propagation_event = NULL;
	wave_propagation_event_create (&wave_propagation_event, ground, wave_signal);
	
	TEST (wave_propagation_event != NULL);
	
	wave_propagation_event -> Destroy (&wave_propagation_event);
	TEST (wave_propagation_event == NULL);
	TEST (ground != NULL);
	TEST (wave_signal != NULL);
}

void wave_propagation_event_execute_test ()
{
	TEST_TITLE ("wave_propagation_event_execute_test");
	
	PtrWaveSignal wave_signal = NULL;
	wave_signal_create (&wave_signal);
	wave_signal_set_energy (wave_signal, 400.0);
	wave_signal_set_direction (wave_signal, 0.0);
	
	PtrGround ground = NULL;
	ground_create (&ground);
	ground_insert_signal (ground, wave_signal);
	
	PtrWavePropagationEvent wave_propagation_event = NULL;
	wave_propagation_event_create (&wave_propagation_event, ground, wave_signal);
	
	wave_propagation_event -> Execute (wave_propagation_event);
	
	DEBUG_IF ((wave_signal_get_energy (wave_signal) == 0.0) == 0,
						"%f",
					 wave_signal_get_energy (wave_signal));
	
	TEST (wave_signal_get_energy (wave_signal) == 0.0);
	
	wave_propagation_event -> Destroy (&wave_propagation_event);
}

void wave_propagation_event_calculate_ratio_energy_tests ()
{
	TEST_TITLE ("wave_propagation_event_calculate_ratio_energy_tests");
	DEBUG_IF ((wave_propagation_event_calculate_ratio_energy (10.0, 10.0) == 1.0) == 0, 
						"%f", 
					 wave_propagation_event_calculate_ratio_energy (10.0, 10.0));
	
	TEST (wave_propagation_event_calculate_ratio_energy (10.0, 10.0) == 1.0);
	TEST (wave_propagation_event_calculate_ratio_energy (345.0, 10.0) == 0.0);
}