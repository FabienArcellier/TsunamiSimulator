#include "debug.h"
#include "test.h"
#include "wave_signal.h"
#include "ground.h"

/* Prototypes des fonctions de test*/
void ground_create_destroy_test ();
void ground_configure_ground ();
void ground_get_set_wave_signals ();
void ground_insert_ground_neighbour_test ();

int main (void)
{
  ground_create_destroy_test ();
  ground_configure_ground ();
	ground_get_set_wave_signals ();
	ground_insert_ground_neighbour_test();
  
  return 0;
}

/*!
 * \brief teste la creation d'un objet
 */
void ground_create_destroy_test ()
{
  TEST_TITLE ("ground_create_destroy_test");
  PtrGround ground = NULL;
  ground_create (&ground);
  
  ground_destroy (&ground);
  
  TEST (ground == NULL);
}

/*!
 * \brief Teste de la configuration d'un terrain
 */
void ground_configure_ground ()
{
  TEST_TITLE ("ground_configure_tests");
  
  PtrGround ground = NULL;
  ground_create (&ground);
  ground_set_type (ground, ground_type_water);
  ground_set_height (ground, -120);
  ground_set_dawning (ground, 0.2);
  
  TEST (ground -> type == ground_type_water);
  TEST (ground -> height == -120);
	DEBUG_IF (ground -> height != -120, "%d", ground -> height);
  TEST (ground -> dawning == 0.2);
	DEBUG_IF (ground -> dawning != 0.2, "%d", ground -> dawning);
  
  ground_destroy (&ground);
}


void ground_get_set_wave_signals ()
{
	TEST_TITLE ("ground_get_set_wave_signals");
	
	PtrGround ground = NULL;
	ground_create (&ground);
	
	PtrWaveSignal wave_signals = ground_get_wave_signals (ground);
	TEST (wave_signals == NULL);
	
	wave_signal_create (&wave_signals);
	
	ground_set_wave_signals (ground, wave_signals);
	PtrWaveSignal wave_signal_stored = ground_get_wave_signals (ground);
	
	TEST (wave_signals == wave_signal_stored);
}

void ground_insert_ground_neighbour_test ()
{
	TEST_TITLE ("ground_insert_ground_neighbour_test");
	
	PtrGround ground = NULL, ground_neighbour1 = NULL, ground_neighbour2 = NULL;
	ground_create (&ground);
	ground_create (&ground_neighbour1);
	ground_create (&ground_neighbour2);
	
	ground_insert_ground_neighbour (ground, ground_neighbour1);
	ground_insert_ground_neighbour (ground, ground_neighbour2);
}
