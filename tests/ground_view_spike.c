#include "debug.h"
#include "test.h"
#include "wave_signal.h"
#include "ground.h"
#include "ground_neighbour.h"
#include "ground_area.h"

void print_ground_information();
void print_ground_neighbour_header ();
void print_ground_neighbour_information (PtrGroundNeighbour ground_neighbour);

int main (void)
{
	PtrGroundArea ground_area = NULL;
  ground_area_create (&ground_area, 1000, 1000);
	
	int i = 0, j = 0;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			PtrGround ground = ground_area_get_ground (ground_area, i, j);
			print_ground_information (ground);
			PtrGroundNeighbour ground_neighbour = ground -> ground_neighbour;
			print_ground_neighbour_header();
			while (ground_neighbour != NULL)
			{
				print_ground_neighbour_information(ground_neighbour);
				ground_neighbour = ground_neighbour_get_next (ground_neighbour);
			}
			printf("\n\n");
		}
	}
	
	return 0;
}

void print_ground_information(PtrGround ground)
{
	printf ("[%p] (%d, %d) (%d, %d)\n\n",
					ground,
				 ground_get_position_X (ground),
				 ground_get_position_Y (ground),
				 ground_get_position_X (ground) + ground_get_width (ground),
				 ground_get_position_Y (ground) + ground_get_length (ground));
}

void print_ground_neighbour_header ()
{
	printf ("\t -- Neighbours --\n");
}

void print_ground_neighbour_information (PtrGroundNeighbour ground_neighbour)
{
	printf ("\t[%p] [%.2f, %.2f]\n",
		ground_neighbour_get_neighbour (ground_neighbour),
		ground_neighbour_get_direction (ground_neighbour),
		ground_neighbour_get_distance (ground_neighbour));
}