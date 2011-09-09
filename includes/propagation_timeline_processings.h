
/*!
 * \brief Parcours une aire et pour chaque onde, enregistre un evenement
 * 	de propagation (wave_propagation_event)
 */
void register_events_for_propagation_on_timeline_from_ground_area (
	PtrTimeline, 
	PtrGroundArea);

/*!
 * \brief Rassemble les waves signals qui ont la meme direction et la meme longueur d'onde
 */
void simplify_wave_signals_after_propagation_on_ground_area (PtrGroundArea);
