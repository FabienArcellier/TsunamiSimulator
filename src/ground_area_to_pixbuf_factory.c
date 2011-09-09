#include "debug.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "wave_signal.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_energy_map.h"
#include "ground_area_to_pixbuf_factory.h"

/*!
* \brief Renvoie une image GdkPixbuf pour ground_area
*/
GdkPixbuf* ground_area_to_pixbuf (PtrGroundArea ground_area)
{
	assert (ground_area != NULL);
	
	// Constante
	const int profondeur_max = -10000;
	const int hauteur_max = 4000;
	const int water_red_min = 0;
	const int water_red_max = 0;
	const int water_green_min = 0;
	const int water_green_max = 0;
	const int water_blue_min = 255;
	const int water_blue_max = 0;
	
	const int ground_red_min = 222;
	const int ground_red_max = 144;
	const int ground_green_min = 181;
	const int ground_green_max = 118;
	const int ground_blue_min = 99;
	const int ground_blue_max = 64;
	
	int width = ground_area -> array_width;
	int length = ground_area -> array_length;
	
	GdkPixbuf *picture = gdk_pixbuf_new (
		GDK_COLORSPACE_RGB, 
		FALSE, 
		8, 
		width, 
		length);
	
	int channel = gdk_pixbuf_get_n_channels (picture);
  unsigned char *pixels = gdk_pixbuf_get_pixels (picture);
	
	int i = 0, j = 0;
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < length; j++)
		{
			PtrGround ground = ground_area_get_ground (ground_area, i, j);
			int height = ground_get_height (ground);
			
			int red = 0, green = 0, blue = 0;
			if (height < 0)
			{
				
				red = water_red_max - (double)(height - profondeur_max)/(double)(0 - profondeur_max) * (water_red_max - water_red_min);
				green = water_green_max - (double)(height - profondeur_max)/(double)(0 - profondeur_max) * (water_green_max - water_green_min);
				blue = water_blue_max - (double)(height - profondeur_max)/(double)(0 - profondeur_max) * (water_blue_max - water_blue_min);
				
// 				DEBUG_IF (1, "%d", height);
// 				DEBUG_IF (1, "%d", red);
// 				DEBUG_IF (1, "%d", green);
// 				DEBUG_IF (1, "%d", blue);
			}
			else
			{
				red = ground_red_max - (double)(height - hauteur_max)/(double)(hauteur_max - 0) * (ground_red_max - ground_red_min);
				green = ground_green_max - (double)(height - hauteur_max)/(double)(hauteur_max - 0) * (ground_green_max - ground_green_min);
				blue = ground_blue_max - (double)(height - hauteur_max)/(double)(hauteur_max - 0) * (ground_blue_max - ground_blue_min);
			}
			
			int position = j * channel * width + i * channel;
			pixels[position] = red;
      pixels[position + 1] = green;
      pixels[position + 2] = blue;
		}
	}
	
	return picture;
}

/*!
 * \brief Rajoute la representation
 */
GdkPixbuf* ground_area_energy_map_to_pixbuf (GdkPixbuf *picture, PtrGroundAreaEnergyMap ground_area_energy_map)
{
	assert (picture != NULL);
	assert (ground_area_energy_map != NULL);
	
	// Constante
	const double energy_max = 10000000000000000.0;
	
	const int red_min = 0;
	const int red_max = 0;
	const int green_min = 200;
	const int green_max = 255;
	const int blue_min = 0;
	const int blue_max = 0;
	
	int width = ground_area_energy_map -> array_width;
	int length = ground_area_energy_map -> array_length;
	
	int channel = gdk_pixbuf_get_n_channels (picture);
  unsigned char *pixels = gdk_pixbuf_get_pixels (picture);
	
	int i = 0, j = 0;
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < length; j++)
		{
			double energy = ground_area_energy_map_get_energy (ground_area_energy_map, i, j);
			
			if (energy != 0.0)
			{
				
				int red = 0, green = 0, blue = 0;
				red = red_max - (double)(energy_max - energy)/(double)(energy_max - 0) * (red_max - red_min);
				green = green_max - (double)(energy_max - energy)/(double)(energy_max - 0) * (green_max - green_min);
				blue = blue_max - (double)(energy_max - energy)/(double)(energy_max - 0) * (blue_max - blue_min);

// 				DEBUG_IF (1, "%f", energy);
// 				DEBUG_IF (1, "%d", red);
// 				DEBUG_IF (1, "%d", green);
// 				DEBUG_IF (1, "%d", blue);
				
				int position = j * channel * width + i * channel;
				pixels[position] = red;
				pixels[position + 1] = green;
				pixels[position + 2] = blue;
			}
		}
	}
	
	return picture;
}