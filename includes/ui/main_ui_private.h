//
// Gestion des events
//
void on_window_destroy_event (GtkWidget* widget, gpointer data);
void on_configure_button_clicked (GtkWidget* widget, gpointer data);
void on_calculate_button_clicked (GtkWidget* widget, gpointer data);
void on_simulate_button_clicked (GtkWidget* widget, gpointer data);
void on_simulate_button_clicked (GtkWidget* widget, gpointer data);
void on_new_menu_activate (GtkWidget* widget, gpointer data);
void on_open_menu_activate (GtkWidget* widget, gpointer data);
void on_save_menu_activate (GtkWidget* widget, gpointer data);
void on_quit_menu_activate (GtkWidget* widget, gpointer data);

/*!
 * \brief Methode appellée a l'issue du processus de calcul
 */
void main_ui_calculate_ui_on_window_destroy (GtkWidget* widget, gpointer data);
void main_ui_simulate_ui_on_window_destroy (GtkWidget* widget, gpointer data);