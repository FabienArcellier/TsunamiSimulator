#include "test.h"
#include "event.h"

/* Prototypes des fonctions de type event */
void event_create_destroy ();
void event_execute_test ();
void event_cast_test ();

/*!
 * \brief Teste le fonctionnement de l'assesseur qui permet d'accéder au temps
 */
void event_set_get_time_test ();
void event_set_next_event_test ();
void event_get_next_event_test ();


int main (void)
{
	event_create_destroy ();
	event_execute_test ();
	event_cast_test ();
	event_set_get_time_test ();
	/*event_set_next_event_test ();
	event_get_next_event_test ();*/
  return 0;
}

void event_create_destroy ()
{
	TEST_TITLE ("event_create_destroy");
	PtrEvent event = NULL;
	event_create (&event);
	
	TEST (event != NULL);
	
	event -> Destroy (&event);
	
	TEST (event == NULL);
}

void event_execute_test()
{
	TEST_TITLE ("event_execute_test : Doit afficher un warning");
	PtrEvent event = NULL;
	event_create (&event);
	
	event -> Execute (event);
	event -> Destroy (&event);
}

/*!
 * \brief Teste le cast EVENT(pointer)
 */
void event_cast_test ()
{
	TEST_TITLE ("event_cast_test");
	PtrEvent event = NULL;
	event_create (&event);
	void* cast_event = (void*) event;
	
	TEST (EVENT (cast_event) -> next == NULL);
	event -> Destroy (&event);
	
}

/*!
 * \brief Teste le fonctionnement de l'assesseur qui permet d'accéder au temps
 */
void event_set_get_time_test ()
{
	TEST_TITLE ("event_set_get_time_test");
	PtrEvent event = NULL;
	event_create (&event);
	int time = event_get_time (event);
	TEST (time == 0);
	
	event_set_time (event, 15);
	
	time = event_get_time (event);
	TEST (time == 15);
	
	event -> Destroy (&event);
}