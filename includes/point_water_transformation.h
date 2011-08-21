
/*!
 * \brief Permet de modifier l'univers de la simulation et d'appliquer une transformation
 *  en un point du liquide
 */
typedef struct point_water_transformation
{
  int water_height;
  int x;
  int y;
  void (*Apply) (struct point_water_transformation*, PtrWaterSimulationEngine);
} PointWaterTransformation;

typedef PointWaterTransformation * PtrPointWaterTransformation;

/*!
 * \brief Cree une instance pour transformer un point de la zone liquide
 */
void point_water_transformation_create (PtrPointWaterTransformation*);

/*!
 * \brief detruit l'objet
 */
void point_water_transformation_destroy (PtrPointWaterTransformation*);

/*!
 * \brief Configure la hauteur d'eau
 */
void point_water_transformation_set_water_height (PtrPointWaterTransformation, int);

/*!
 * \brief Configure le point d'application de cette transformation
 */
void point_water_transformation_set_application_point (PtrPointWaterTransformation, int x, int y);

/*!
 * \brief Applique la transformation à la Hmap courante
 */
void point_water_transformation_apply (PtrPointWaterTransformation, PtrWaterSimulationEngine);