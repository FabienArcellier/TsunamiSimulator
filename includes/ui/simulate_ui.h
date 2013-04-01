enum FrameState
{
	frame_state_play,
	frame_state_pause,
	frame_state_stop
};

typedef struct simulate_ui
{
	// Widgets
	GtkWindow *window;
	GtkMenuItem *menu_close;
	GtkMenuItem *menu_speed_normal;
	GtkMenuItem *menu_speed_lent;
	GtkDrawingArea *drawingarea;
	GtkHScale *time;
	GtkButton *button_play;
	GtkButton *button_pause;
	GtkButton *button_stop;
	GtkButton *button_previous;
	GtkButton *button_next;
	GtkAdjustment *time_adjustment;
	//Variables
	int tick_timeout;
	int tick;
	int frame_speed;
	int frame_position;
	enum FrameState frame_state;
	PtrSimulation simulation;
	GdkPixbuf *pixbuf_result;
} SimulateUI;

typedef SimulateUI* PtrSimulateUI;

/*!
 * \brief Instancie un objet SimulateUI
 */
void simulate_ui_create (PtrSimulateUI *simulate_ui, PtrSimulation simulation);

/*!
 * \brief Detruit un objet SimulateUI
 */
void simulate_ui_destroy (PtrSimulateUI*);

/*!
 * \brief Affiche la fenetre principale
 */
void simulate_ui_show (PtrSimulateUI);

/*!
 * \brief Cache la fenetre principale
 */
void simulate_ui_hide (PtrSimulateUI);

/*!
 * \brief Affecte à chaque widget les attributs qu'il doit avoir selon les etats de l'objet
 */
void simulate_ui_refresh_ihm_states (PtrSimulateUI simulate_ui);

/*!
 * \brief Retourne le handle de la fenetre principale
 */
GtkWindow* simulate_ui_get_window (PtrSimulateUI);

/* Your methods */

void simulate_ui_refresh_current_ground_area (PtrSimulateUI);

/*!
 * \brief Assesseur en lecture de l'attribut simulation
 */
PtrSimulation simulate_ui_get_simulation (PtrSimulateUI);

void simulate_ui_refresh_time (PtrSimulateUI);
