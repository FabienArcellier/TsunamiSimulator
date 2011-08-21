#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "water_hmap.h"
#include "water_rendering_engine.h"

/*!
 * \brief Cree un objet de rendu à partir d'une image d'origine
 */
void water_rendering_engine_create (PtrWaterRenderingEngine* water_rendering_engine)
{
  assert(*water_rendering_engine == NULL);
  
  *water_rendering_engine = (PtrWaterRenderingEngine) malloc (sizeof (WaterRenderingEngine));
  if (*water_rendering_engine == NULL)
  {
    abort();
  }
  
  memset(*water_rendering_engine, 0, sizeof (WaterRenderingEngine));
  
  assert(*water_rendering_engine != NULL);
}

/*!
 * \brief Detruit l'objet de rendu
 */
void water_rendering_engine_destroy (PtrWaterRenderingEngine* water_rendering_engine)
{
  assert(*water_rendering_engine != NULL);
  
  g_object_unref ((*water_rendering_engine) -> frame);
  free(*water_rendering_engine);
  
  *water_rendering_engine = NULL;
}

/*!
 * \brief Vient referencer un objet de type WaterHmap pour la transformation
 */
void water_rendering_engine_set_water_hmap (PtrWaterRenderingEngine water_rendering_engine, PtrWaterHmap water_hmap)
{
  assert(water_rendering_engine != NULL);
  
  water_rendering_engine -> water_hmap = water_hmap;
  
  assert(water_rendering_engine != NULL);
}

/*!
 * \brief Calcule un nouveau rendu, le resultat va dans frame
 */
void water_rendering_engine_rendering_water (PtrWaterRenderingEngine water_rendering_engine)
{
  GdkPixbuf *frame = water_rendering_engine -> frame;
  int i = 0, j = 0;
  int channel = gdk_pixbuf_get_n_channels (frame);
  int width = water_rendering_engine -> water_hmap -> width, height = water_rendering_engine -> water_hmap -> height;
  unsigned char *pixels = gdk_pixbuf_get_pixels (frame);
  
  for (i = 1; i < width - 1; i++)
  {
    for (j = 1; j < height - 1; j++)
    {
      int offsetX = water_hmap_get_water_height(water_rendering_engine -> water_hmap, i - 1, j) -
        water_hmap_get_water_height(water_rendering_engine -> water_hmap, i + 1, j);
      int offsetY = water_hmap_get_water_height(water_rendering_engine -> water_hmap, i, j - 1) -
        water_hmap_get_water_height(water_rendering_engine -> water_hmap, i, j + 1);

      int position = j * channel * width + i * channel;
      int position_refraction = position;
      if ((j + offsetY) < height && (j + offsetY) > 0 && (i + offsetX) < width && (i + offsetX) > 0)
      {
        position_refraction = (j + offsetY) * channel  * width + (i + offsetX) * channel;
      }
      
      if (offsetX > 40) offsetX = 40;
      if (offsetX <-40) offsetX = -40;

      int pixel_red = pixels[position_refraction] + offsetX;
      if (pixel_red > 255) pixel_red = 255;
      if (pixel_red < 0) pixel_red = 0;
      
      int pixel_green = pixels[position_refraction + 1] + offsetX;
      if (pixel_green > 255) pixel_green = 255;
      if (pixel_green < 0) pixel_green = 0;
      
      int pixel_blue = pixels[position_refraction + 2] + offsetX;
      if (pixel_blue > 255) pixel_blue = 255;
      if (pixel_blue < 0) pixel_blue = 0;
      
      pixels[position] = (unsigned char) pixel_red;
      pixels[position + 1] = (unsigned char) pixel_green;
      pixels[position + 2] = (unsigned char) pixel_blue;
    }
  }
  
  water_rendering_engine -> rendering_done = 1;
}

/*!
 * \brief Enregistre un objet GdkPixbuf qui represente la frame avant le rendu
 */
void water_rendering_engine_set_frame (PtrWaterRenderingEngine water_rendering_engine, GdkPixbuf* frame_before_rendering)
{
  water_rendering_engine -> rendering_done = 0;
  water_rendering_engine -> frame = frame_before_rendering;
}

/*!
 * \brief Retourne l'attribut frame
 */
GdkPixbuf * water_rendering_engine_get_frame (PtrWaterRenderingEngine water_rendering_engine)
{
  return water_rendering_engine -> frame;
}