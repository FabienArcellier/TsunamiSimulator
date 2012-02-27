
/*!
 * \brief contient la definition des fonctions propres à l'ui main.glade
 */
typedef struct main_ui
{
  // Widgets
  GtkWindow* window;
  GtkButton* configure_button;
  GtkButton* calculate_button;
	GtkButton* simulate_button;
	GtkMenuItem* new_menu;
	GtkMenuItem* open_menu;
	GtkMenuItem* save_menu;
	GtkMenuItem* quit_menu;
	//
	// States
	int simulation_loaded;
	int ihm_active;
	//
	// Data
	PtrCalculateUI calculate_ui;
	PtrSimulateUI simulate_ui;
	PtrSimulation simulation;
} MainUI;

typedef MainUI * PtrMainUI;

/*!
 * \brief Cree une instance MainUI
 */
void main_ui_create (PtrMainUI*);

/*!
 * \brief Detruit une instance MainUI
 */
void main_ui_destroy (PtrMainUI*);

/*!
 * \brief Affiche la fenetre de l'IHM
 */
void main_ui_show (PtrMainUI);

/*!
 * \brief Cache la fenetre de l'IHM
 */
void main_ui_hide (PtrMainUI);

/*!
 * \brief Affecte à chaque widget les attributs qu'il doit avoir selon les etats de l'objet
 */
void main_ui_refresh_ihm_states (PtrMainUI);

/*!
 * \brief Assesseur en lecture de l'attribut window
 */
GtkWindow* main_ui_get_window (PtrMainUI);

/*!
 * \brief Assesseur en ecriture de l'attribut simulation_loaded
 */
void main_ui_set_simulation_loaded (PtrMainUI, int);

/*!
 * \brief Assesseur en lecture de l'attribut simulation_loaded
 */
int main_ui_get_simulation_loaded (PtrMainUI);

/*!
 * \brief Assesseur en ecriture de l'attribut ihm_active
 */
void main_ui_set_ihm_active (PtrMainUI, int);

/*!
 * \brief Assesseur en lecture de l'attribut ihm_active
 */
int main_ui_get_ihm_active (PtrMainUI);

/*!
 * \brief Assesseur en ecriture de l'attribut simulation
 */
void main_ui_set_simulation (PtrMainUI, PtrSimulation);

/*!
 * \brief Assesseur en lecture de l'attribut simulation
 */
PtrSimulation main_ui_get_simulation (PtrMainUI);

/*!
 * \brief Assesseur en ecriture de l'attribut calculate_ui
 */
void main_ui_set_calculate_ui (PtrMainUI, PtrCalculateUI);

/*!
 * \brief Assesseur en lecture de l'attribut calculate_ui
 */
PtrCalculateUI main_ui_get_calculate_ui (PtrMainUI);

/*!
 * \brief Assesseur en ecriture de l'attribut simulate_ui
 */
void main_ui_set_simulate_ui (PtrMainUI, PtrSimulateUI);

/*!
 * \brief Assesseur en lecture de l'attribut simulate_ui
 */
PtrSimulateUI main_ui_get_simulate_ui (PtrMainUI);



