
/*!
 * \brief object responsable de la creation de la frame de resultat à partir du water_hmap et de
 *  l'image de fond
 */
typedef struct water_rendering_engine
{
  WaterHmap *water_hmap;
  GdkPixbuf *frame;
  int rendering_done;
} WaterRenderingEngine;

typedef WaterRenderingEngine * PtrWaterRenderingEngine;

/*!
 * \brief Cree un objet de rendu à partir d'une image d'origine
 */
void water_rendering_engine_create (PtrWaterRenderingEngine*);

/*!
 * \brief Detruit l'objet de rendu
 */
void water_rendering_engine_destroy (PtrWaterRenderingEngine*);

/*!
 * \brief Vient referencer un objet de type WaterHmap pour la transformation
 */
void water_rendering_engine_set_water_hmap (PtrWaterRenderingEngine, PtrWaterHmap);

/*!
 * \brief Calcule le nouveau rendu, le resultat va dans frame
 */
void water_rendering_engine_rendering_water (PtrWaterRenderingEngine);

/*!
 * \brief Enregistre un objet GdkPixbuf qui represente la frame avant le rendu
 */
void water_rendering_engine_set_frame (PtrWaterRenderingEngine, GdkPixbuf*);

/*!
 * \brief Retourne l'attribut frame
 */
GdkPixbuf * water_rendering_engine_get_frame (PtrWaterRenderingEngine);