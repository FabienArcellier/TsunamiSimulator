#include "test.h"
#include "debug.h"
#include "event.h"
#include "wave_signal.h"
#include "ground.h"
#include "earthquake_event.h"
#include "timeline.h"
#include "ground_area.h"

int main (void)
{
	PtrTimeline timeline = NULL;
	timeline_create (&timeline);
	timeline_set_final_time (timeline, 10);
	
	PtrGroundArea ground_area = NULL;
	ground_area_create (&ground_area, 10000, 10000);
	PtrGround epicentre_ground = ground_area_get_ground (ground_area, 10, 10);
	
	PtrEarthquakeEvent earthquake = NULL;
	earthquake_event_create (&earthquake);
	earthquake_event_set_ground (earthquake, epicentre_ground);
	earthquake_event_set_energy (earthquake, 1000000000000000.0);
	event_set_time (EVENT (earthquake), 5);
	
	timeline_insert_event (timeline, EVENT (earthquake));
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		timeline_execute_events (timeline);
		TEST (ground_get_wave_signals (epicentre_ground) == NULL);
		timeline_move_current_time (timeline, 1);
	}
	
	timeline_execute_events (timeline);
	TEST (ground_get_wave_signals (epicentre_ground) != NULL);
}