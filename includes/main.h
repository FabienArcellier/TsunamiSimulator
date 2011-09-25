typedef struct main_struct
{
	int argc;
	char **argv;
	PtrMainUI main_ui
} MainStruct;

typedef MainStruct * PtrMainStruct;

/*!
 * \brief Instancie un objet MainStruct
 */
void main_create (PtrMainStruct*, int argc, char **argv);

/*!
 * \brief Detruit un objet MainStruct
 */
void main_destroy (PtrMainStruct*);

/*!
 * \brief Demarre l'application et ouvre l'IHM
 */
void main_application_start (PtrMainStruct);

/*!
 * \brief Detruit les objets instanciés par main lors de la destruction de la fenetre principale
 */
void main_application_quit (PtrMainStruct, gpointer);

/*!
 * \brief Assesseur en lecture de l'attribut main_ui
 */
PtrMainUI main_get_main_ui (PtrMainStruct);