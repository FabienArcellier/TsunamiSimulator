#include "test.h"

/* Prototypes des fonctions de tests */
void wave_signal_create_destroy_test ();
void wave_signal_set_get_energy_test ();
void wave_signal_set_get_frequency_test ();
void wave_signal_set_get_next_signal_wave_test();
void wave_signal_insert_wave_signal_sort_by_frequency_asc_test ();

int main (void)
{
	wave_signal_create_destroy_test ();
}

void wave_signal_create_destroy_test ()
{
	TEST_TITLE ("wave_signal_create_destroy_test");
	PtrWaveSignal wave_signal = NULL;
	wave_signal_create (&wave_signal);
	
	TEST (wave_signal != NULL);
	
	wave_signal_destroy (&wave_signal)
	TEST (wave_signal == NULL);
}

void wave_signal_set_get_energy_test ()
{
	TEST_TITLE ("wave_signal_set_get_energy_test");
	PtrWaveSignal wave_signal = NULL;
	wave_signal_create (&wave_signal);
	
	double energy = wave_signal_get_energy (&wave_signal)
	TEST (energy == 0.0);
	
	wave_signal_set_energy (&wave_signal, 240.0);
	energy = wave_signal_get_energy (&wave_signal);
	TEST (energy == 240.0);
	
	wave_signal_destroy (&wave_signal);
}

void wave_signal_set_get_frequency_test ()
{
	TEST_TITLE ("wave_signal_set_get_frequency_test");
	PtrWaveSignal wave_signal = NULL;
	wave_signal_create (&wave_signal);
	
	double energy = wave_get_frequency (&wave_signal)
	TEST (energy == 0.0);
	
	wave_signal_set_frequency (&wave_signal, 100.0);
	energy = wave_signal_set_frequency (&wave_signal);
	TEST (frequency == 100.0);
	
	wave_signal_destroy (&wave_signal);
}

void wave_signal_set_get_next_signal_wave_test ()
{
	TEST_TITLE ("wave_signal_set_get_next_signal_wave_test");
	PtrWaveSignal wave_signal1 = NULL, wave_signal_2 = NULL;
	wave_signal_create (&wave_signal1);
	wave_signal_create (&wave_signal2);
	
	TEST (wave_signal_get_next_wave_signal (wave_signal1) == NULL);
	
	wave_signal_set_next_wave_signal (wave_signal1, wave_signal2);
	TEST (wave_signal_get_next_wave_signal (wave_signal1) == wave_signal2);
	
	wave_signal_destroy (&wave_signal);
}

/*!
 * \brief verifie l'insertion de 3 maillons de type wave_signal
 * 
 * Ils doivent etre trie par frequence croissante
 */
void wave_signal_insert_wave_signal_sort_by_frequency_asc_test ()
{
	TEST_TITLE ("wave_signal_insert_wave_signal_sort_by_frequency_asc_test");
	
	PtrWaveSignal wave_signal1 = NULL, wave_signal_2 = NULL, wave_signal3 = NULL;
	
	wave_signal_create (&wave_signal1);
	wave_signal_set_frequency (wave_signal1, 1.0);
	wave_signal_create (&wave_signal2);
	wave_signal_set_frequency (wave_signal2, 1.2);
	wave_signal_create (&wave_signal3);
	wave_signal_set_frequency (wave_signal3, 0.5);
	
	PtrWaveSignal list_wave_signals = NULL;
	list_wave_signals = wave_signal_insert_wave_signal_sort_by_frequency_asc (list_wave_signals, wave_signal1);
	list_wave_signals = wave_signal_insert_wave_signal_sort_by_frequency_asc (list_wave_signals, wave_signal2);
	list_wave_signals = wave_signal_insert_wave_signal_sort_by_frequency_asc (list_wave_signals, wave_signal3);
	
	TEST (list_wave_signals == wave_signal3);
	TEST (wave_signal_get_next_wave_signal (list_wave_signals) == wave_signal1);
	
}