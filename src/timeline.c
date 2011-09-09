#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "timeline.h"

/*!
 * \brief Cree une instance de timeline
 */
void timeline_create (PtrTimeline *timeline)
{
	assert (*timeline == NULL);
	
	*timeline = (PtrTimeline) malloc (sizeof (Timeline));
	memset (*timeline, 0, sizeof (Timeline));
}

/*!
 * \brief Detruit une instance de timeline et la file d'evenement
 */
void timeline_destroy (PtrTimeline *timeline)
{
	assert (*timeline != NULL);
	
	PtrEvent events = NULL;
	events = (*timeline) -> events;
	if (events != NULL)
	{
		events -> Destroy( &events);
	}
	
	free (*timeline);
	*timeline = NULL;
}

/*!
 * \brief Fixe le temps initial de la timeline
 */
void timeline_set_initial_time (PtrTimeline timeline, int time)
{
	assert (timeline != NULL);
	assert (time >= 0);
	
	timeline -> time_initial = time;
	if (timeline -> time_current < time)
	{
		timeline -> time_current = time;
	}
	
	if (timeline -> time_final < time)
	{
		timeline -> time_final = time;
	}
}

/*!
 * \brief Retourne le temps initial de la timeline
 */
int timeline_get_initial_time (PtrTimeline timeline)
{
	assert (timeline != NULL);
	
	return timeline -> time_initial;
}

/*!
 * \brief Retourne le temps final de la timeline
 */
int timeline_get_final_time (PtrTimeline timeline)
{
	assert (timeline != NULL);
	
	return timeline -> time_final;
}

/*!
 * \brief Fixe le temps final de la timeline
 */
void timeline_set_final_time (PtrTimeline timeline, int time)
{
	assert (timeline != NULL);
	assert (timeline -> time_initial <= time);
	
	timeline -> time_final = time;
	if (timeline -> time_current > time)
	{
		timeline -> time_current = time;
	}
}

/*!
 * \brief Retourne le temps actuel de la timeline
 */
int timeline_get_current_time (PtrTimeline timeline)
{
	assert (timeline != NULL);
	
	return timeline -> time_current;
}

/*!
 * \brief Deplace le temps courant de la timeline
 */
void timeline_move_current_time (PtrTimeline timeline, int time_moving)
{
	assert (timeline != NULL);
	assert (timeline -> time_current + time_moving >= timeline -> time_initial);
	assert (timeline -> time_current + time_moving <= timeline -> time_final);
	
	timeline -> time_current += time_moving;
}

/*!
 * \brief Retourne la file d'evenement de la timeline
 */
PtrEvent timeline_get_events (PtrTimeline timeline)
{
	assert (timeline != NULL);
	return timeline -> events;
}

/*!
 * \brief Assesseur de l'attribut event
 */
void timeline_set_events (PtrTimeline timeline, PtrEvent events)
{
	assert (timeline != NULL);
	timeline -> events = events;
}


/*!
 * \brief Insere un event dans la timeline
 */
void timeline_insert_event(PtrTimeline timeline, PtrEvent event)
{
	assert (timeline != NULL);
	PtrEvent events = timeline_get_events (timeline);
	timeline -> events = event_insert_sort_by_time_asc (events, event);
}

/*!
 * \brief Ajout un event en tete dans la timeline
 */
void timeline_push_event(PtrTimeline timeline, PtrEvent event)
{
	assert (timeline != NULL);
	if (event != NULL)
	{
		PtrEvent current_event = timeline_get_events (timeline);
		event_set_next_event (event, current_event);
		timeline_set_events (timeline, event);
	}
}

/*!
 * \brief Retire un event dans la timeline
 */
PtrEvent timeline_pop_event(PtrTimeline timeline)
{
	assert (timeline != NULL);
	PtrEvent event = timeline_get_events (timeline);
	if (event != NULL)
	{
		PtrEvent next_event = event_get_next_event (event);
		timeline_set_events (timeline, next_event);
	}
	
	return event;
}

/*!
 * \brief Execute les events qui correspondent au temps courant de la timeline
 */
void timeline_execute_events (PtrTimeline timeline)
{
	int current_time = timeline_get_current_time (timeline);
	PtrEvent event = NULL;
	int execute_event = 0;
	do
	{
		execute_event = 0;
		event = timeline_pop_event (timeline);
		if (event != NULL && event_get_time (event) == current_time)
		{
			event -> Execute (event);
			event -> Destroy (&event);
			execute_event = 1;
		}
		else
		{
			timeline_push_event (timeline, event);
		}
	} while (execute_event == 1);
}