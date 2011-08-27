#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

/*!
 * \brief Cree une instance de l'objet Event
 */
void event_create (PtrEvent *event)
{
	assert (*event == NULL);
	*event = (PtrEvent) malloc (sizeof (Event));
	memset (*event, 0, sizeof (Event));
	
	event_init (*event);
}

/*!
 * \brief Cree une instance de l'objet Destroy
 */
void event_destroy (PtrEvent *event)
{
	assert (*event != NULL);
	
	PtrEvent next_event = event_get_next_event (*event);
	if (next_event != NULL)
	{
		next_event -> Destroy (&next_event);
	}
	
	*event = NULL;
}

/*!
 * \brief Initialise les fonctions virtuelle de l'objet Event
 */
void event_init (PtrEvent event)
{
	event -> Destroy = event_destroy;
	event -> Execute = event_execute;
}

/*!
 * \brief Execute le code de l'evenement
 * A reecrire si hérité
 */
void event_execute (PtrEvent event)
{
	assert (event != NULL);
	
	fprintf(stderr,
					"%s - %d : Le code de la methode event_execute est une methode abstraite\n",
				 __FILE__,
				 __LINE__);
}

/*!
 * \brief Fixe le temps de declenchement de l'evenement
 */
void event_set_time (PtrEvent event, int time)
{
	assert (event != NULL);
	assert (time >= 0);
	
	event -> time = time;
}

/*!
 * \brief Renvoie le temps de declenchement de l'evenement
 */
int event_get_time (PtrEvent event)
{
	assert (event != NULL);
	
	return event -> time;
}

/*!
 * \brief Renvoie l'evenement suivant dans la liste
 */
PtrEvent event_get_next_event (PtrEvent event)
{
	assert (event != NULL);
	
	return event -> next;
}

/*!
 * \brief Permet de fixer l'evenement suivant dans la liste
 */
void event_set_next_event (PtrEvent event, PtrEvent next_event)
{
	assert (event != NULL);
	event -> next = next_event;
}

/*!
 * \brief Insere un evenement dans une file en se basant sur le temps
 * 
 * La file est supposé déjà ordonné
 */
PtrEvent event_insert_sort_by_time_asc (PtrEvent file_event, PtrEvent event_to_insert)
{
	assert (event_to_insert != NULL);
	if (file_event == NULL)
	{
		return event_to_insert;
	}
	else if (event_get_time (file_event) >= event_get_time (event_to_insert))
	{
		event_set_next_event (event_to_insert, file_event);
		return event_to_insert;
	}
	else
	{
		PtrEvent event = event_insert_sort_by_time_asc(event_get_next_event (file_event), event_to_insert);
		event_set_next_event (file_event, event);
		return file_event;
	}
}