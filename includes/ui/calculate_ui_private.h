void calculate_ui_on_window_destroy_event (GtkWidget*, gpointer);
void calculate_ui_on_cancel_button_clicked (GtkWidget*, gpointer);

/*!
 * \brief Mis a jour de l'IHM a intervalle regulier
 */
gint calculate_ui_timeout (gpointer data);