typedef struct timeline
{
	int time_initial;
	int time_current;
	int time_final;
	PtrEvent events;
} Timeline;

typedef Timeline * PtrTimeline;

/*!
 * \brief Cree une instance de timeline
 */
void timeline_create (PtrTimeline*);

/*!
 * \brief Detruit une instance de timeline et la file d'evenement
 */
void timeline_destroy (PtrTimeline*);

/*!
 * \brief Fixe le temps initial de la timeline
 */
void timeline_set_initial_time (PtrTimeline, int);

/*!
 * \brief Retourne le temps final de la timeline
 */
int timeline_get_final_time (PtrTimeline);

/*!
 * \brief Fixe le temps final de la timeline
 */
void timeline_set_final_time (PtrTimeline, int);

/*!
 * \brief Retourne le temps initial de la timeline
 */
int timeline_get_initial_time (PtrTimeline);

/*!
 * \brief Retourne le temps actuel de la timeline
 */
int timeline_get_current_time (PtrTimeline);

/*!
 * \brief Deplace le temps courant de la timeline
 */
void timeline_move_current_time (PtrTimeline, int);

/*!
 * \brief Assesseur de l'attribut event
 */
void timeline_set_events (PtrTimeline timeline, PtrEvent events);

/*!
 * \brief Retourne la file d'evenement de la timeline
 */
PtrEvent timeline_get_events (PtrTimeline);

/*!
 * \brief Insere un event dans la timeline
 */
void timeline_insert_event(PtrTimeline, PtrEvent);

/*!
 * \brief Insere un event dans la timeline
 */
void timeline_push_event(PtrTimeline, PtrEvent);

/*!
 * \brief Insere un event dans la timeline
 */
PtrEvent timeline_pop_event(PtrTimeline);

/*!
 * \brief Execute les events qui correspondent au temps courant de la timeline
 */
void timeline_execute_events (PtrTimeline);
