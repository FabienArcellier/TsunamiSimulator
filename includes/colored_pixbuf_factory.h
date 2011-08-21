
/*!
 * \brief Permet de fabriquer des objets de type Pixbuf avec une couleur de fond
 */
typedef struct colored_pixbuf_factory
{
  int width;
  int height;
  unsigned char red;
  unsigned char blue;
  unsigned char green;
} ColoredPixbufFactory;

typedef ColoredPixbufFactory * PtrColoredPixbufFactory;

/*!
 * \brief Cree une instance de ColoredPixbufFactory
 */
void colored_pixbuf_factory_create(PtrColoredPixbufFactory*);

/*!
 * \brief Detruit une instance de ColoredPixbufFactory
 */
void colored_pixbuf_factory_destroy(PtrColoredPixbufFactory*);

/*!
 * \brief Instancie une image Pixbuf avec une couleur de fond donnee
 */
GdkPixbuf * colored_pixbuf_factory_instanciate(PtrColoredPixbufFactory);
