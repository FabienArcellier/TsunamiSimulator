void simulate_ui_on_window_destroy (GtkWidget*, gpointer);
void simulate_ui_on_menu_close_activate (GtkWidget*, gpointer);
void simulate_ui_on_menu_speed_normal_activate (GtkWidget*, gpointer);
void simulate_ui_on_menu_speed_lent_activate (GtkWidget*, gpointer);
void simulate_ui_on_button_play_activate (GtkWidget*, gpointer);
void simulate_ui_on_button_pause_activate (GtkWidget*, gpointer);
void simulate_ui_on_button_stop_activate (GtkWidget*, gpointer);
void simulate_ui_on_button_previous_activate (GtkWidget*, gpointer);
void simulate_ui_on_button_next_activate (GtkWidget*, gpointer);
void simulate_ui_on_time_value_changed (GtkWidget*, gpointer);
gint simulate_ui_tick_timeout (gpointer);
gint simulate_ui_expose_drawingarea (GtkWidget*, GdkEventExpose*, gpointer);