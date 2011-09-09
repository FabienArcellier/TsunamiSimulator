typedef enum ground_area_builder_ground_type {
	Island,
	Continent
} GroundAreaBuilderGroundType;

typedef struct ground_area_builder
{
	PtrGroundArea ground_area_result;
	int width;
	int height;
	double water_position;
	GroundAreaBuilderGroundType type;
} GroundAreaBuilder;

typedef GroundAreaBuilder* PtrGroundAreaBuilder;

/*!
 * \brief Cree une instance de type GroundAreaBuilder
 */
void ground_area_builder_create (PtrGroundAreaBuilder*);

/*!
 * \brief Detruit une instance de type GroundAreaBuilder
 */
void ground_area_builder_destroy (PtrGroundAreaBuilder*);

/*!
 * \brief Renvoie le terrain genere
 * Si le terrain n'a pas ete genere alors renvoie NULL
 */
PtrGroundAreaBuilder ground_area_builder_get_ground_area (PtrGroundAreaBuilder);

/*!
 * \brief Renvoie la largeur en m
 */
int ground_area_builder_get_width (PtrGroundAreaBuilder);

/*!
 * \brief Definit la largeur en m
 */
void ground_area_builder_set_width (PtrGroundAreaBuilder, int);

/*!
 * \brief Renvoie la hauteur en m
 */
int ground_area_builder_get_height (PtrGroundAreaBuilder);

/*!
 * \brief Definit la largeur de la carte en m
 */
void ground_area_builder_set_height (PtrGroundAreaBuilder, int);

/*!
 * \brief Position de l'eau entre 0 et 1
 */
double ground_area_builder_get_water_position (PtrGroundAreaBuilder);

/*!
 * \brief Assesseur en ecriture de la position de l'eau, defini entre 0 et 1
 */
void ground_area_builder_set_water_position (PtrGroundAreaBuilder, double);

/*!
 * \brief Renvoie le type de la carte a generer
 */
GroundAreaBuilderGroundType ground_area_builder_get_type (PtrGroundAreaBuilder);

/*!
 * \brief Definit le type de la carte a generer
 */
void ground_area_builder_set_type (PtrGroundAreaBuilder, GroundAreaBuilderGroundType);