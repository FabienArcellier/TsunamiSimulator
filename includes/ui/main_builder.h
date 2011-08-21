
typedef struct main_builder
{
  GtkWidget* (*Build) (struct main_builder *);
  char* ui_repository_path;
} MainBuilder;

typedef MainBuilder * PtrMainBuilder;

void main_builder_create (PtrMainBuilder*);

void main_builder_destroy (PtrMainBuilder*);

/*!
 * \brief assesseur du champs ui_repository_path
 */
void main_builder_set_ui_repository_path (PtrMainBuilder, char* ui_repository_path);

/*!
 * \brief Construit une fenetre main et retourne sa reference
 */
PtrMainUI main_builder_build (PtrMainBuilder main_builder);
