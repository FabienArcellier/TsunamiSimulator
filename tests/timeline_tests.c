#include "test.h"
#include "timeline.h"

/* Prototypes des fonctions de tests */

/*!
 * \brief Teste la fonction de creation et de destruction de la timeline
 */
static void timeline_create_destroy_test ();

/*!
 * \brief Teste la fonction qui deplace le curseur de la timeline
 */
static void timeline_move_current_time_test ();

/*!
 * \brief Teste la fonction add event de la timeline
 */
static void timeline_insert_event_test ();

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
  
  int time = timeline_get_current_time (timeline);
  TEST (time == 0);
  
  int count_events = timeline_count_events (timeline);
  TEST (count_events == 0);
  
  timeline_destroy (&timeline);
  TEST (timeline == NULL);
}

/*!
 * \brief Teste la fonction qui deplace le curseur de la timeline
 */
static void timeline_move_current_time_test ()
{
  TEST_TITLE ("timeline_move_current_time_test");
  PtrTimeline timeline = NULL;
  
  timeline_create (&timeline);
  int previous_time = timeline_get_current_time (timeline);
  timeline_move_current_time (timeline, 1);
  int current_time = timeline_get_current_time (timeline);
  
  TEST (current_time == previous_time + 1);
}



