#include "debug.h"
#include "test.h"
#include "wave_signal.h"

/* Prototypes des fonctions de tests */
void wave_signal_create_destroy_test ();
void wave_signal_set_get_energy_test ();
void wave_signal_set_get_length_test ();
void wave_signal_set_get_direction_test ();
void wave_signal_set_get_next_signal_wave_test();
void wave_signal_insert_wave_signal_sort_by_length_asc_test ();

int main (void)
{
	wave_signal_create_destroy_test ();
	wave_signal_set_get_energy_test ();
	wave_signal_set_get_length_test ();
	wave_signal_set_get_direction_test ();
	wave_signal_set_get_next_signal_wave_test ();
	wave_signal_insert_wave_signal_sort_by_length_asc_test ();
	
	return 0;
}

void wave_signal_create_destroy_test ()
{
	TEST_TITLE ("wave_signal_create_destroy_test");
	PtrWaveSignal wave_signal = NULL;
	wave_signal_create (&wave_signal);
	
	TEST (wave_signal != NULL);
	
	wave_signal_destroy (&wave_signal);
	TEST (wave_signal == NULL);
}

void wave_signal_set_get_energy_test ()
{
	TEST_TITLE ("wave_signal_set_get_energy_test");
	PtrWaveSignal wave_signal = NULL;
	wave_signal_create (&wave_signal);
	
	double energy = wave_signal_get_energy (wave_signal);
	TEST (energy == 0.0);
	
	wave_signal_set_energy (wave_signal, 240.0);
	energy = wave_signal_get_energy (wave_signal);
	TEST (energy == 240.0);
	
	wave_signal_destroy (&wave_signal);
}

void wave_signal_set_get_length_test ()
{
	TEST_TITLE ("wave_signal_set_get_length_test");
	PtrWaveSignal wave_signal = NULL;
	wave_signal_create (&wave_signal);
	
	double length = wave_signal_get_length (wave_signal);
	TEST (length == 0.0);
	
	wave_signal_set_length (wave_signal, 100.0);
	length = wave_signal_get_length (wave_signal);
	TEST (length == 100.0);
	
	wave_signal_destroy (&wave_signal);
}

/*!
 * \brief Teste les fonctions qui permettent de configurer la direction d'une onde
 */
void wave_signal_set_get_direction_test ()
{
	TEST_TITLE ("wave_signal_set_get_direction_test");
	
	PtrWaveSignal wave_signal = NULL;
	wave_signal_create (&wave_signal);
	double direction = wave_signal_get_direction (wave_signal);
	
	TEST (direction == 0.0);
	
	wave_signal_set_direction (wave_signal, 180.0);
	direction = wave_signal_get_direction (wave_signal);
	TEST (direction == 180.0);
	
	wave_signal_set_direction (wave_signal, 371.0);
	direction = wave_signal_get_direction (wave_signal);
	TEST (direction > 10.99 && direction < 11.01);
	DEBUG_IF (direction <= 10.99 || direction >= 11.01, "%f", direction);
}

void wave_signal_set_get_next_signal_wave_test ()
{
	TEST_TITLE ("wave_signal_set_get_next_signal_wave_test");
	PtrWaveSignal wave_signal1 = NULL, wave_signal2 = NULL;
	wave_signal_create (&wave_signal1);
	wave_signal_create (&wave_signal2);
	
	TEST (wave_signal_get_next_wave_signal (wave_signal1) == NULL);
	
	wave_signal_set_next_wave_signal (wave_signal1, wave_signal2);
	TEST (wave_signal_get_next_wave_signal (wave_signal1) == wave_signal2);
	
	wave_signal_destroy (&wave_signal1);
}

/*!
 * \brief verifie l'insertion de 3 maillons de type wave_signal
 * 
 * Ils doivent etre trie par frequence croissante
 */
void wave_signal_insert_wave_signal_sort_by_length_asc_test ()
{
	TEST_TITLE ("wave_signal_insert_wave_signal_sort_by_length_asc_test");
	
	PtrWaveSignal wave_signal1 = NULL, wave_signal2 = NULL, wave_signal3 = NULL;
	
	wave_signal_create (&wave_signal1);
	wave_signal_set_length (wave_signal1, 150000);
	wave_signal_create (&wave_signal2);
	wave_signal_set_length (wave_signal2, 300000);
	wave_signal_create (&wave_signal3);
	wave_signal_set_length (wave_signal3, 10000);
	
	PtrWaveSignal list_wave_signals = NULL;
	list_wave_signals = wave_signal_insert_wave_signal_sort_by_length_asc (list_wave_signals, wave_signal1);
	list_wave_signals = wave_signal_insert_wave_signal_sort_by_length_asc (list_wave_signals, wave_signal2);
	list_wave_signals = wave_signal_insert_wave_signal_sort_by_length_asc (list_wave_signals, wave_signal3);
	
	TEST (list_wave_signals == wave_signal3);
	TEST (wave_signal_get_next_wave_signal (list_wave_signals) == wave_signal1);
	
	wave_signal_destroy (&list_wave_signals);
}