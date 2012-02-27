enum CalculateWorkerState
{
	calculate_worker_state_inactive,
	calculate_worker_state_in_progress,
	calculate_worker_state_done,
	calculate_worker_state_canceled
};

typedef struct calculate_worker
{
	PtrSimulation simulation;
	pthread_t pid;
	int cancel_requested;
	enum CalculateWorkerState state;
} CalculateWorker;

typedef CalculateWorker* PtrCalculateWorker;

/*!
 * \brief Instancie un worker pour calculer la simulation
 */
void calculate_worker_create (PtrCalculateWorker*, PtrSimulation);

/*!
 * \brief Detruit le worker
 */
void calculate_worker_destroy (PtrCalculateWorker*);

/*!
 * \brief Démarre la fonction de calcul
 */
void calculate_worker_start (PtrCalculateWorker);

/*!
 * \brief Demande au worker d'interrompre son fonctionnement
 */
void calculate_worker_cancel (PtrCalculateWorker);

/*!
 * \brief Assesseur en ecriture de l'attribut simulation
 */
void calculate_worker_set_simulation (PtrCalculateWorker, PtrSimulation);

/*!
 * \brief Assesseur en lecture de l'attribut simulation
 */
PtrSimulation calculate_worker_get_simulation (PtrCalculateWorker);

/*!
 * \brief Assesseur en ecriture de l'attribut state
 */
void calculate_worker_set_state (PtrCalculateWorker, enum CalculateWorkerState);

/*!
 * \brief Assesseur en lecture de l'attribut state
 */
enum CalculateWorkerState calculate_worker_get_state (PtrCalculateWorker);