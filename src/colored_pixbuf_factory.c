#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "colored_pixbuf_factory.h"

/*!
 * \brief Cree une instance de ColoredPixbufFactory
 */
void colored_pixbuf_factory_create(PtrColoredPixbufFactory* colored_pixbuf_factory)
{
  assert (*colored_pixbuf_factory == NULL);
  
  *colored_pixbuf_factory = (PtrColoredPixbufFactory) malloc (sizeof (ColoredPixbufFactory));
  memset(*colored_pixbuf_factory, 0, sizeof (ColoredPixbufFactory));
  
  (*colored_pixbuf_factory) -> width = 10;
  (*colored_pixbuf_factory) -> height = 10;
  
  assert (*colored_pixbuf_factory != NULL);
}

/*!
 * \brief Detruit une instance de ColoredPixbufFactory
 */
void colored_pixbuf_factory_destroy(PtrColoredPixbufFactory* colored_pixbuf_factory)
{
  assert (*colored_pixbuf_factory != NULL);
  
  free(*colored_pixbuf_factory);
  * colored_pixbuf_factory = NULL;
  
  assert (*colored_pixbuf_factory == NULL);
}

/*!
 * \brief Instancie une image Pixbuf avec une couleur de fond donnee
 */
GdkPixbuf * colored_pixbuf_factory_instanciate(PtrColoredPixbufFactory colored_pixbuf_factory)
{
  assert (colored_pixbuf_factory != NULL);
  assert (colored_pixbuf_factory -> width > 0);
  assert (colored_pixbuf_factory -> height > 0);
  
  GdkPixbuf * picture = gdk_pixbuf_new (
    GDK_COLORSPACE_RGB, 
    FALSE, 
    8, 
    colored_pixbuf_factory -> width, 
    colored_pixbuf_factory -> height);
  
  int channel = gdk_pixbuf_get_n_channels (picture);
  unsigned char *pixels = gdk_pixbuf_get_pixels (picture);
  
  /* Colorie l'image */
  int i = 0, j = 0;
  for (i = 0; i < colored_pixbuf_factory -> width; i++)
  {
    for (j = 0; j < colored_pixbuf_factory -> height; j++)
    {
      int position = j * channel * colored_pixbuf_factory -> width + i * channel;
      pixels[position] = colored_pixbuf_factory -> red;
      pixels[position + 1] = colored_pixbuf_factory -> green;
      pixels[position + 2] = colored_pixbuf_factory -> blue;
    }
  }
  
  return picture;
}