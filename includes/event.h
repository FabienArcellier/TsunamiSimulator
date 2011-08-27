typedef struct event
{
	void (*Execute) (struct event*);
	void (*Destroy) (struct event**);
	int time;
	struct event* next;
} Event;

typedef Event* PtrEvent ;

/*! 
 * \brief Macro pour caster un objet vers le type Event
 */
#define EVENT(Pointer) ((PtrEvent) Pointer)

/*!
 * \brief Cree une instance de l'objet Event
 */
void event_create (PtrEvent*);

/*!
 * \brief Cree une instance de l'objet Destroy
 */
void event_destroy (PtrEvent*);

/*!
 * \brief Initialise les fonctions virtuelle de l'objet Event
 */
void event_init (PtrEvent);

/*!
 * \brief Execute le code de l'evenement
 * A reecrire si hérité
 */
void event_execute (PtrEvent);

/*!
 * \brief Fixe le temps de declenchement de l'evenement
 */
void event_set_time (PtrEvent, int);

/*!
 * \brief Renvoie le temps de declenchement de l'evenement
 */
int event_get_time (PtrEvent);

/*!
 * \brief Renvoie l'evenement suivant dans la liste
 */
PtrEvent event_get_next_event (PtrEvent);

/*!
 * \brief Permet de fixer l'evenement suivant dans la liste
 */
void event_set_next_event (PtrEvent event, PtrEvent next_event);

/*!
 * \brief Insere un evenement dans une file en se basant sur le temps
 * 
 * La file est supposé déjà ordonné
 */
PtrEvent event_insert_sort_by_time_asc (PtrEvent file_event, PtrEvent event_to_insert);