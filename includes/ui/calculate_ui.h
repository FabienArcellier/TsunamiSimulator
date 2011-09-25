typedef struct calculate_ui
{
	// Widgets
	GtkWindow* window;
	GtkProgressBar progress_bar;
	GtkButton* cancel_button;
	
	//Variables
	PtrCalculateWorker calculate_worker;
	PtrSimulation simulation;
	int timeout_refresh_id;
} CalculateUI;

typedef CalculateUI* PtrCalculateUI;

/*!
 * \brief Instancie un objet calculate_ui
 */
void calculate_ui_create (PtrCalculateUI*);

/*!
 * \brief Detruit un objet calculate_ui
 */
void calculate_ui_destroy (PtrCalculateUI*);

/*!
 * \brief Affiche la fenetre principale
 */
void calculate_ui_show (PtrCalculateUI);

/*!
 * \brief Cache la fenetre principale
 */
void calculate_ui_hide (PtrCalculateUI);

/*!
 * \brief Retourne le handle de la fenetre principale
 */
GtkWindow* calculate_ui_get_window (PtrCalculateUI);

/*!
 * \brief Rafraichit l'etat de la fenetre
 */
void calculate_ui_refresh_ihm_states (PtrCalculateUI);

/*!
 * \brief Demarre le worker de calcul
 */
void calculate_ui_start_worker (PtrCalculateUI);