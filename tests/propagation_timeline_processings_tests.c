#include "test.h"
#include "event.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_neighbour.h"
#include "ground_area.h"
#include "ground_neighbour.h"
#include "wave_propagation_event.h"
#include "timeline.h"
#include "propagation_timeline_processings.h"

/* Prototypes des fonctions de test */
void register_events_for_propagation_on_timeline_from_ground_area_test ();

int main (void)
{
	register_events_for_propagation_on_timeline_from_ground_area_test();
}

void register_events_for_propagation_on_timeline_from_ground_area_test ()
{
	TEST_TITLE ("register_events_for_propagation_on_timeline_from_ground_area_test");
	PtrTimeline timeline = NULL;
	timeline_create (&timeline);
	timeline_set_final_time (timeline, 15); 
	timeline_move_current_time (timeline, 3);

	PtrGroundArea ground_area = NULL;
	ground_area_create (&ground_area, 10000, 10000);
	
	PtrGround ground = ground_area_get_ground (ground_area, 5, 5);
	
	PtrWaveSignal wave_signal = NULL;
	wave_signal_create (&wave_signal);
	
	ground_insert_signal (ground, wave_signal);
	
	register_events_for_propagation_on_timeline_from_ground_area (timeline, ground_area);
	
	PtrEvent event = timeline_get_events (timeline);
	TEST (event != NULL);
	TEST (event_get_time (event) == 3);
}
