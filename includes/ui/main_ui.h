
/*!
 * \brief contient la definition des fonctions propres à l'ui main.glade
 */
typedef struct main_ui
{
  // Widgets
  GtkWidget* window;
  GtkDrawingArea* drawing_area;
  GtkStatusbar* status_bar;
  // Variables
  GdkPixbuf* frame_before_water_rendering;
  GdkPixbuf* frame_to_display;
  // Objects
  PtrWaterRenderingEngine water_rendering_engine;
  PtrWaterSimulationEngine water_simulation_engine;
} MainUI;

typedef MainUI* PtrMainUI;

/*!
 * \brief Cree une instance MainUI
 */
void main_ui_create (PtrMainUI*);

/*!
 * \brief Detruit une instance MainUI
 */
void main_ui_destroy (PtrMainUI*);

/*
 * Fonctions callback pour les signaux de la fenetre principale
 */
void on_main_destroy (GtkWidget*);
void on_menu_file_action_quit_activate (GtkMenuItem* menu_file_action_quit, PtrMainUI main_ui);
gboolean on_drawing_area_button_press_event (GtkDrawingArea* drawing_area, GdkEventButton *event, PtrMainUI main_ui);
gboolean on_drawing_area_expose_event (GtkDrawingArea*, GdkEventExpose*, PtrMainUI);

/* Assesseurs
 */ 

/*!
 * \brief Retourne la frame avant le rendu de l'eau
 */
GdkPixbuf* main_ui_get_frame_before_water_rendering (PtrMainUI);

/*!
 * \brief Enregistre la frame avant le rendu de l'eau
 */
void main_ui_set_frame_before_water_rendering (PtrMainUI, GdkPixbuf* frame);

/*!
 * \brief Retourne la frame a afficher
 */
GdkPixbuf* main_ui_get_frame_to_display (PtrMainUI);

/*!
 * \brief Permet d'enregistrer la frame a afficher
 */
void main_ui_set_frame_to_display (PtrMainUI, GdkPixbuf* frame);

/*!
 * \brief Retourne le moteur de rendu de l'eau
 */
PtrWaterRenderingEngine main_ui_get_water_rendering_engine (PtrMainUI);

/*!
 * \brief Set le moteur de rendu de l'eau
 */
void main_ui_set_water_rendering_engine (PtrMainUI, PtrWaterRenderingEngine);

/*!
 * \brief Retourne le moteur de simulation
 */
PtrWaterSimulationEngine main_ui_get_water_simulation_engine (PtrMainUI);

/*!
 * \brief Set le moteur de simulation de l'eau
 */
void main_ui_set_water_simulation_engine (PtrMainUI, PtrWaterSimulationEngine);