#include "test.h"
#include "event.h"
#include "timeline.h"

/* Prototypes des fonctions de tests */

/*!
 * \brief Teste la fonction de creation et de destruction de la timeline
 */
static void timeline_create_destroy_test ();

/*!
 * \brief Teste la fonction qui fixe le temps initial
 */
static void timeline_set_get_initial_time ();

/*!
 * \brief Teste la fonction qui fixe le temps initial
 */
static void timeline_set_get_final_time ();

/*!
 * \brief Teste la fonction qui deplace le curseur de la timeline
 */
static void timeline_move_current_time_test ();

/*!
 * \brief Teste la fonction add event de la timeline
 */
static void timeline_insert_get_event_test ();

/*!
 * \brief Teste la fonction clear events de la timeline
 */
static void timeline_clear_events_test ();

/*!
 * \brief Teste la fonction d'execution des events de la timeline
 */
static void timeline_execute_events_test ();

int main (void)
{
	timeline_create_destroy_test ();
	timeline_set_get_initial_time ();
	timeline_set_get_final_time ();
	timeline_move_current_time_test();
	timeline_insert_get_event_test();
  return 0;
}

/*!
 * \brief Teste la fonction de creation et de destruction de la timeline
 */
static void timeline_create_destroy_test ()
{
  TEST_TITLE ("timeline_create_destroy_test");
  PtrTimeline timeline = NULL;
  
  timeline_create (&timeline);
  TEST (timeline != NULL);
  
  // int time = timeline_get_current_time (timeline);
  // TEST (time == 0);
  
  timeline_destroy (&timeline);
  TEST (timeline == NULL);
}

/*!
 * \brief Teste la fonction qui fixe le temps initial
 */
static void timeline_set_get_initial_time ()
{
	TEST_TITLE ("timeline_set_get_initial_time");
  PtrTimeline timeline = NULL;
  
  timeline_create (&timeline);
	int time = -1;
	time = timeline_get_initial_time (timeline);
	TEST (time == 0);
	
	timeline_set_initial_time (timeline, 15);
	
	time = timeline_get_initial_time (timeline);
	TEST (time == 15);
	
	timeline_destroy (&timeline);
}

/*!
 * \brief Teste la fonction qui fixe le temps final
 */
static void timeline_set_get_final_time ()
{
	TEST_TITLE ("timeline_set_get_final_time");
  PtrTimeline timeline = NULL;
  
  timeline_create (&timeline);
	int time = -1;
	time = timeline_get_final_time (timeline);
	TEST (time == 0);
	
	timeline_set_final_time (timeline, 15);
	
	time = timeline_get_final_time (timeline);
	TEST (time == 15);
	
	timeline_destroy (&timeline);
}

/*!
 * \brief Teste la fonction qui deplace le curseur de la timeline
 */
static void timeline_move_current_time_test ()
{
  TEST_TITLE ("timeline_move_current_time_test");
  PtrTimeline timeline = NULL;
  
  timeline_create (&timeline);
	timeline_set_final_time (timeline, 60);
  int previous_time = timeline_get_current_time (timeline);
  timeline_move_current_time (timeline, 1);
  int current_time = timeline_get_current_time (timeline);
  
  TEST (current_time == previous_time + 1);
}

/*!
 * \brief Teste la fonction add event de la timeline
 */
static void timeline_insert_get_event_test ()
{
	TEST_TITLE ("timeline_insert_event_test");
	PtrEvent event1 = NULL, event2 = NULL, event3 = NULL;
	PtrTimeline timeline = NULL;
	
	timeline_create (&timeline);
	event_create (&event1);
	event_set_time (event1, 25);
	
	event_create (&event2);
	event_set_time (event2, 20);
	
	event_create (&event3);
	event_set_time (event3, 23);
	
	
	timeline_insert_event (timeline, event1);
	timeline_insert_event (timeline, event2);
	timeline_insert_event (timeline, event3);
	
	PtrEvent events = timeline_get_events (timeline);
	
	TEST (events == event2);
	TEST (event_get_next_event(events) == event3);
	TEST (event_get_next_event(event_get_next_event(events)) == event1);
}



