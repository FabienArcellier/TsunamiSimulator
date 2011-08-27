#include "test.h"
#include "event.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_neighbour.h"
#include "wave_propagation_event.h"
#include "timeline.h"

/* Prototypes des fonctions de test */
void register_events_for_propagation_on_timeline_from_ground_area_test ();

int main (void)
{
	
}

void register_events_for_propagation_on_timeline_from_ground_area_test ()
{
	register_events_for_propagation_on_timeline_from_ground_area (timeline, ground_area);
}
