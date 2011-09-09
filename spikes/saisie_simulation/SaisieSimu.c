#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct evenement
{ int temps;
  char type[10];
  int positionX;
  int positionY;
  double intensite;
  struct evenement *suiv;
}EVENEMENT;

typedef struct terrain
{ char info[255];
  struct terrain *suiv;
}TERRAIN;

int menu (void);
int ConfigSimu (void);
EVENEMENT* CreerEvenement (EVENEMENT *nouveau);
EVENEMENT* AjoutEvenement ( EVENEMENT *listeEvenement, EVENEMENT *nouveau);
EVENEMENT* AjoutEvenementRec ( EVENEMENT *precedent,EVENEMENT *courant, EVENEMENT *nouveau);
void AfficherEvenement (EVENEMENT *courant);
void AfficherListeEvenement (EVENEMENT *listeEvenement, int num);
EVENEMENT* SupprimerEvenement (EVENEMENT *listeEvenement);
void ChoixTerrain (char nomFichier[255]);
TERRAIN* ChargerTerrain (TERRAIN *listeTerrain, char nomFichier[255]);
void AfficherTerrain (TERRAIN *listeTerrain);
void SaveSimu (EVENEMENT *listeEvenement, TERRAIN *listeTerrain, int duree);
int OpenSimu (EVENEMENT **listeEvenement, TERRAIN **listeTerrain, int duree);


int main (void)
{
  EVENEMENT *listeEvenement = NULL;
  TERRAIN *listeTerrain = NULL;
  EVENEMENT *nouveau = NULL;
  int choix = -1;
  int duree = 0;
  char nomFichier[255];
  

  while (choix != 0)
  { 
    choix = menu();
    switch (choix)
    { case 1 :  duree = ConfigSimu();
                break;
      case 2 :  nouveau = CreerEvenement (nouveau);
                //listeEvenement = AjoutEvenement (listeEvenement, nouveau);
                listeEvenement = AjoutEvenementRec (NULL, listeEvenement, nouveau);
                break;
      case 3 :  AfficherListeEvenement (listeEvenement, 1);
                break;
      case 4 :  listeEvenement = SupprimerEvenement (listeEvenement);
                break;
      case 5 :  ChoixTerrain (nomFichier);
                listeTerrain = ChargerTerrain (listeTerrain, nomFichier);
                //AfficherTerrain (listeTerrain);
                break;
      case 6 :  SaveSimu (listeEvenement, listeTerrain, duree);
                break;
      case 7 :  duree = OpenSimu (&listeEvenement, &listeTerrain, duree);
                break;
      case 8 :  AfficherTerrain (listeTerrain);
                break;
      case 0 :  
                break;
      default : break;
    }
  }
  
  return 0;
}


int menu (void)
{
  int choix = 10;
  
  while( choix != 0 && choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && 
    choix != 6 && choix != 7 && choix != 8)
  { printf(" _______________________________ \n");
    printf("|     SIMULATEUR DE TSUNAMI     |\n");
    printf("|_______________________________|\n");
    printf("   Saisie de votre Simulation    \n\n");
    printf("MENU ;\n");
    printf("\t1- Configuration de la Simulation\n");
    printf("\t2- Ajouter un evenement\n");
    printf("\t3- Afficher les evenements\n");
    printf("\t4- Supprimer un evenement\n");
    printf("\t5- Charger un terrain\n");
    printf("\t6- Sauvegarder ce fichier Simulation\n");
    printf("\t7- Ouvrir un fichier Simulation\n");
    printf("\t8- Afficher le terrain\n");
    printf("\t0- Quitter\n\n");
    
    printf("Veuillez saisir l'identifiant de votre choix :\t");
    scanf("%d", &choix);
  }
 
  return choix;
}


int ConfigSimu (void)
{
 int duree = 0;
 
 do
 { printf("Veuillez saisir la duree de la simulation (s) :\t");
   scanf("%d", &duree);
 } while (duree < 0 );
 
 return duree; 
}


EVENEMENT* CreerEvenement (EVENEMENT *nouveau)
{
  int comp = 1;
   
  nouveau = (EVENEMENT *) malloc (sizeof(EVENEMENT));
  if(nouveau == NULL)
    printf("ERREUR d'allocation...!!!\n");
  
  do
  { printf("Veuillez saisir le temps au declenchement de l'evenement (s) :\t\t");
    scanf("%d", &(nouveau->temps));
  } while (nouveau->temps < 0);
  
  do
  { printf("Veuillez saisir le Type de la Simulation (terre ou mer) :\t\t");
    scanf("%s", nouveau->type);
    comp = comp * strcmp(nouveau->type, "terre");
    comp = comp * strcmp(nouveau->type, "mer");
  } while (comp != 0);

  do
  { printf("Veuillez saisir la position X de l'Epicentre (entre 0 et 100 000 m) :\t\t");
    scanf("%d", &(nouveau->positionX));
    nouveau->positionX = nouveau->positionX;
  } while (nouveau->positionX < 0 || nouveau->positionX > 100000);
  
  do
  { printf("Veuillez saisir la position Y de l'Epicentre (entre 0 et 100 000 m) :\t\t");
    scanf("%d", &(nouveau->positionY));
    nouveau->positionY = nouveau->positionY;
  } while (nouveau->positionY < 0 || nouveau->positionY > 100000);
  
  do
  { printf("Veuillez saisir l'Inteniste de la Simulation (Joules) :\t\t");
    scanf("%lf", &(nouveau->intensite));
  } while (nouveau->intensite < 0);

  nouveau -> suiv = NULL;
  
  return nouveau;
}


EVENEMENT* AjoutEvenement ( EVENEMENT *listeEvenement, EVENEMENT *nouveau)
{  
  EVENEMENT *courant = listeEvenement;
  EVENEMENT *precedent = NULL;
   
  if (listeEvenement == NULL)          // Liste vide
  { nouveau -> suiv = NULL;
    listeEvenement = nouveau;
  }
  else
  { while( (courant != NULL) && ((nouveau->temps) > (courant->temps)) )
    { precedent = courant;
      courant = courant->suiv;
    }
    if(courant == listeEvenement)     //Début de ListeEvenement
    { nouveau->suiv = listeEvenement;
      listeEvenement = nouveau;
    }
    else 
    { if(courant == NULL)   //Fin de ListeEvenement
      { nouveau->suiv = NULL;
        precedent->suiv = nouveau;
      }
      else                    //Milieu de ListeEvenement
      { nouveau->suiv = courant;
        precedent->suiv = nouveau;
      }
    }
  }

   return listeEvenement;
}


EVENEMENT* AjoutEvenementRec ( EVENEMENT *precedent,EVENEMENT *courant, EVENEMENT *nouveau)
{  
  if (courant == NULL)          // Liste vide ou finie
  { nouveau -> suiv = NULL;
    courant = nouveau;
    return nouveau;
  }
  else
  { if( (nouveau->temps) < (courant->temps) )
    { if( precedent == NULL)    // tete de liste
      { nouveau -> suiv = courant;
        courant = nouveau;
        return nouveau;
      }
      else   
      { nouveau -> suiv = courant;
        precedent -> suiv = nouveau;
        return nouveau;
      }
    }
    else
    {  courant -> suiv = AjoutEvenementRec (courant, courant -> suiv, nouveau);
      return courant;
    }
  }
}


void AfficherEvenement (EVENEMENT *courant)
{
  printf("\t\tTemps = %d s\n", courant->temps);
  printf("\t\tType  = %s \n", courant->type);
  printf("\t\tPosition : X = %d m\n", courant->positionX);
  printf("\t\tPosition : Y = %d m\n", courant->positionY);
  printf("\t\tIntensite = %f J\n", courant->intensite);
}


void AfficherListeEvenement (EVENEMENT *listeEvenement, int num)
{
  EVENEMENT *courant = listeEvenement;
  
  if (listeEvenement == NULL)
    printf("Il n'y plus d'evenement...\n");
  else
  {   printf("\n");
      printf(" %d- Evenement %d :\n", num, num);
      AfficherEvenement (courant);  
      AfficherListeEvenement (courant -> suiv, num+1);
  }
    
}


EVENEMENT* SupprimerEvenement (EVENEMENT *listeEvenement)
{
  EVENEMENT *courant = listeEvenement;
  EVENEMENT *precedent = NULL;
  int id = 0;
  int num = 1;
  
  do
  { printf("Veuillez saisir l'identifiant de l'evenement a supprimer :\t");
    scanf("%d", &id);
  }while (id <= 0);
  
  if(listeEvenement == NULL)
    printf("Il n'y a aucun evenement enregistre, donc rien a supprimer...\n");
  else
  { 
    while (num < id)
    { precedent = courant;
      courant = courant -> suiv;
      num++;
    }
    if(courant == listeEvenement)    //Debut de ListeEvenement
    { listeEvenement = courant -> suiv;
      courant -> suiv = NULL;
    }
    else
    { 
      if(courant -> suiv == NULL)   //Fin de ListeEvenement
      { precedent -> suiv = NULL;
      }
      else              //Milieu de listeEvenement
      { precedent -> suiv = courant -> suiv;
        courant -> suiv = NULL;
      }
    }  
    free (courant);
  }
      
  return listeEvenement;
}


void ChoixTerrain (char nomFichier[255])
{
  int choix = 0;
  
  do
  { printf("Voici la liste des terrains disponibles :\n");
    printf("\t1- Plage\n");
    printf("\t2- Ile\n");
    printf("\t3- Archipel\n");
    printf("\t4- Continent\n");
    printf("\t5- Cote\n");
    printf("\t6- Detroit\n");
    printf("\t7- Ground1\n");
    printf("\t8- Ground2\n");
    printf("\t0- Aucun - Sortir\n");
    printf("Veuiller saisir le numero du Terrain que vous voulez utiliser :\t");
    scanf("%d", &choix);
    printf("\n");
  } while( choix < 0 || choix > 8);
  
  switch (choix)
  { case 1 :  strcpy(nomFichier, "plage.txt");
              break;
    case 2 :  strcpy(nomFichier, "ile.txt");
              break;
    case 3 :  strcpy(nomFichier, "Archipel.txt");
              break;
    case 4 :  strcpy(nomFichier, "continents.txt");
              break;
    case 5 :  strcpy(nomFichier, "cote.txt");
              break;
    case 6 :  strcpy(nomFichier, "Detroit.txt");
              break;
    case 7 :  strcpy(nomFichier, "ground1.txt");
              break;
    case 8 :  strcpy(nomFichier, "ground2.txt");
              break;
    case 0 :  break;
    default : break;
  }
  
}


TERRAIN* ChargerTerrain (TERRAIN *listeTerrain, char nomFichier[255])
{
  FILE *fichier = NULL;
  TERRAIN *terrain = NULL;
  TERRAIN *dernier = NULL;
  char *fin = NULL;
  
  fichier = fopen( nomFichier,"r");
  if (fichier == NULL)
  { printf("Erreur a l'ouverture du fichier\n");
  }
  else
    printf("Fichier Terrain %s ouvert\n", nomFichier);
  
  do
  { terrain = (TERRAIN *) malloc (sizeof(TERRAIN));
    if(terrain == NULL)
      printf("ERREUR d'allocation...!!!\n");
    
    fin = fgets (terrain -> info, 255, fichier);
    
    if(listeTerrain == NULL)
    { terrain -> suiv = NULL;
      listeTerrain = terrain;
      dernier = terrain;
    }
    else
    { terrain -> suiv = NULL;
      dernier -> suiv = terrain;
      dernier = terrain;
    }
  }while (fin !=  NULL);
  
  fclose(fichier);
  printf("Fichier terrain %s chargé\n", nomFichier);
  return listeTerrain;
}


void AfficherTerrain (TERRAIN *listeTerrain)
{
  int nbr = 0;
  
  if (listeTerrain == NULL)
    printf("Il n'y plus de parcelles de terrain...\n");
  else
    do
    { 
      printf("%s", listeTerrain -> info);
      listeTerrain = listeTerrain -> suiv;
      nbr++;
    } while (nbr < 30);
}


void SaveSimu (EVENEMENT *listeEvenement, TERRAIN *listeTerrain, int duree)
{
  FILE *fichier = NULL;
  EVENEMENT *evenement = listeEvenement;
  TERRAIN *terrain = listeTerrain;
  char nomFichier[255];
  
  printf("veuillez saisir le nom du fichier d'enregistrement (sans extension) :\n\t\t");
  scanf("%s", nomFichier);
  strcat( nomFichier, ".simu");
  
  fichier = fopen( nomFichier, "w");
  if (fichier == NULL)
  { fichier = fopen (nomFichier, "a");
    if (fichier == NULL)
    { printf("Erreur a l'ouverture du fichier\n");
    }
    else
      printf("Fichier %s ouvert en a\n", nomFichier);
  }
  else
   printf("Fichier %s ouvert en w\n", nomFichier);
  
  fprintf( fichier, "[Configuration]\n");
  fprintf( fichier, "Duree = %d s\n\n", duree);
  
  //fprintf( fichier, "[Terrain]\n");
  if(listeTerrain == NULL)
    fprintf( fichier, "Il n'y a pas de terrain de charger dans la simulation...\n");
  else
  { while( terrain != NULL)
    { fprintf( fichier, "%s", terrain -> info );
      terrain = terrain -> suiv;
    }
  }
  
  fprintf( fichier, "\n[Evenements]\n");
  fprintf( fichier, "datatype\tearthquake_events_text_storage\tversion\t1.0.0\n");
  fprintf( fichier, "#Temps\tPositionX\tPositionY\tEnergie\n");
  if( listeEvenement == NULL)
    fprintf( fichier, "Il n'y a aucun evenement...\n");
  else
  { while( evenement != NULL)
    { fprintf( fichier, "%d\t%d\t%d\t%f\n", 
             evenement -> temps, 
             evenement -> positionX,
             evenement -> positionY,
             evenement -> intensite);
      evenement = evenement -> suiv;
    }
  }
 
  fclose(fichier);
  printf("La Simulation a ete sauvegardee dans le Fichier %s\n", nomFichier);
}


int OpenSimu (EVENEMENT **listeEvenement, TERRAIN **listeTerrain, int duree)
{ 
  FILE *fichier = NULL;
  EVENEMENT *evenement = *listeEvenement;
  EVENEMENT *dernierEvenement = NULL;
  TERRAIN *terrain = NULL;
  TERRAIN *dernier = NULL;
  int fin = 1;
  char nomFichier[250];
  char poubelle[255];
  
  printf("veuillez saisir le nom du fichier a ouvrir (sans extension) :\n\t\t");
  scanf("%s", nomFichier);
  strcat( nomFichier, ".simu");
  
  fichier = fopen( nomFichier, "r");
  if (fichier == NULL)
  { printf("Erreur a l'ouverture du fichier\n");
  }
  else
    printf("Fichier Simu %s ouvert\n", nomFichier);
  
  
  fgets( poubelle, 255, fichier);     //[Configuration]
  printf("\n%s", poubelle);
  fscanf(fichier, "Duree = %d s\n", &duree);
  printf("Duree de la Simulation : %d s\n", duree);

  
  fgets( poubelle, 255, fichier);     //[Terrain]
  printf("\n%s", poubelle);
  
  do
  { terrain = (TERRAIN *) malloc (sizeof(TERRAIN));
    if(terrain == NULL)
      printf("ERREUR d'allocation...!!!\n");
    
    fgets (terrain -> info, 255, fichier);
    if( strcmp( terrain -> info, "\n") == 0)
      fin = 0;
    else
    { fin++;
      if(*listeTerrain == NULL)
      { terrain -> suiv = NULL;
        *listeTerrain = terrain;
        dernier = terrain;
      }
      else
      { terrain -> suiv = NULL;
        dernier -> suiv = terrain;
        dernier = terrain;
      }
    }
  }while (fin != 0);
  
  fin = 0;
  
  fgets( poubelle, 255, fichier);     //[Evenement]
  printf("\n%s", poubelle);
  fgets( poubelle, 255, fichier);
  printf("\n%s", poubelle);
  fgets( poubelle, 255, fichier);     //Temps  PositionX PositionY Energie
  printf("%s", poubelle);
  do
  { evenement = (EVENEMENT *) malloc (sizeof(EVENEMENT));
    if(evenement == NULL)
      printf("ERREUR d'allocation...!!!\n");
    
    fin = fscanf( fichier, "%d\t%d\t%d\t%lf\n",
                  &(evenement -> temps),
                  &(evenement -> positionX),
                  &(evenement -> positionY),
                  &(evenement -> intensite) );
    printf(" %d\t%s\t%d\t%d\t%lf \n",
           evenement -> temps,
           evenement -> type,
           evenement -> positionX,
           evenement -> positionY,
           evenement -> intensite );
        
    if( fin > 0)
    { if( *listeEvenement == NULL)       //ListeEvenement vide
      { evenement -> suiv = NULL;
        *listeEvenement = evenement;
        dernierEvenement = evenement;
      }
      else
      { evenement -> suiv = NULL;
        dernierEvenement -> suiv = evenement;
        dernierEvenement = evenement;
      }
    }

  } while( fin > 0 );

  printf("\nFichier Simu %s chargé\n", nomFichier);
  if(*listeEvenement == NULL)
    printf("Aucun Evenement n'a ete charge\n");
  if(*listeTerrain == NULL)
    printf("Aucun Terrain n'a ete charge\n");
  fclose(fichier);
  return duree;
}

