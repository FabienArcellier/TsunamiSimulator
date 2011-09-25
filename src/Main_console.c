#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>
#include "wave_signal.h"
#include "debug.h"
#include "ground.h"
#include "ground_area.h"
#include "ground_area_text_storage.h"
#include "ground_area_energy_map.h"
#include "ground_area_energy_map_navigator.h"
#include "ground_area_energy_text_storage.h"
#include "event.h"
#include "earthquake_event.h"
#include "earthquake_events_text_storage.h"
#include "timeline.h"
#include "propagation_timeline_processings.h"
#include "simulation.h"
#include "simulation_text_storage.h"
#include "ground_area_to_pixbuf_factory.h"


int menu (int SimuChargee, int SimuCalculee);
PtrSimulation LoadSimu (int *SimuChargee);
void AfficherEvenements (void);
void CalculerSimu (PtrSimulation);
void SaveImage (PtrSimulation simulation);
void PrintReport (PtrSimulation simulation);

int main (int argc, char *argv[])
{
  int choix = -1;
  int SimuChargee = 0;
  int SimuCalculee = 0;
  PtrSimulation simulation = NULL;
	
	gtk_init (&argc, &argv);
  
  
  while (choix != 0)
  { 
    choix = menu (SimuChargee, SimuCalculee);
    switch (choix)
    { case 1 :  simulation = LoadSimu (&SimuChargee);
                SimuCalculee = 0;
                break;
      case 2 :  CalculerSimu (simulation);
                SimuCalculee = 1;
                break;
      case 3 :  if(SimuCalculee == 1)
                  SaveImage (simulation);
                break;
			case 4:
							if(SimuCalculee == 1)
								PrintReport (simulation);
      case 0 :  break;
      default : break;
    }
  }
  
  return 0;
}


int menu (int SimuChargee, int SimuCalculee)
{
  int choix = 10;
  
  while( choix != 0 && choix != 1 && choix != 2 && choix != 3 && choix != 4)
  { printf(" _______________________________ \n");
    printf("|     SIMULATEUR DE TSUNAMI     |\n");
    printf("|_______________________________|\n");
    printf("\nSimuChargee = %d  SimuCalculee = %d\n", SimuChargee, SimuCalculee);
    printf("\nMENU ;\n");
    printf("\t1- Charger une Simulation\n");
    if (SimuChargee == 1)
    {  
      printf("\t2- Calculer la Simulation\n");
      if (SimuCalculee == 1)
      { 
        printf("\t3- Enregistrer les Images\n");
				printf("\t4- Enregistrer un report test\n");
      }
    }
    printf("\t0- Quitter\n\n");
    
    printf("Veuillez saisir l'identifiant de votre choix :\t");
    scanf("%d", &choix);
  }
  
  return choix;
}


PtrSimulation LoadSimu (int *SimuChargee)
{
  FILE *fichierSimu = NULL;
  PtrSimulationTextStorage simulationTextStorage = NULL;
  PtrSimulation simulation = NULL;
  char nomFichier[255];
  
  printf("Veuillez saisir le chemin et le nom du fichier Simu a charger  :\n\t");
  scanf("%s", nomFichier);
  
  fichierSimu = fopen( nomFichier, "r");
  if (fichierSimu == NULL)
    printf("Erreur a l'ouverture du fichier Simu\n");
  else
    printf("Fichier Simu %s ouvert\n", nomFichier);
  
  simulation_text_storage_create (&simulationTextStorage);
  simulation_text_storage_set_file (simulationTextStorage, fichierSimu);
  simulation = simulation_text_storage_read_file (simulationTextStorage);
  simulation_text_storage_destroy (&simulationTextStorage);
  
  if (simulation == NULL)
  { 
    *SimuChargee = 0;
    printf("Simulation non chargee.\n");
  }
  else
  { 
    *SimuChargee = 1;
    printf("Simulation chargee.\n");
  }
  
  fclose (fichierSimu);
  return simulation;
}

void CalculerSimu (PtrSimulation simulation)
{
	PtrTimeline timeline = simulation_get_timeline (simulation);
	PtrGroundArea ground_area = simulation_get_ground_area (simulation);
	PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator = simulation_get_energy_map_navigator (simulation);
	
	int final_time = timeline_get_final_time (timeline);
	int i = 0;
	while (timeline_get_current_time (timeline) < final_time)
	{
		printf("Temps : %d / %d\n", i, final_time);
		register_events_for_propagation_on_timeline_from_ground_area (timeline,
																																	ground_area);
		timeline_execute_events (timeline);
		simplify_wave_signals_after_propagation_on_ground_area (ground_area);
		
		PtrGroundAreaEnergyMap ground_area_energy_map = NULL;
		ground_area_energy_map_create (&ground_area_energy_map, ground_area);
		timeline_move_current_time (timeline, 1);
		
		ground_area_energy_map_navigator_add (ground_area_energy_map_navigator, ground_area_energy_map);
		i++;
	}

	printf("Simulation calculee.\n");
}


void SaveImage (PtrSimulation simulation)
{
	printf ("Entrez le prefixe des fichiers images :\n");
	char prefix[250];
	scanf ("%s", prefix);
	
	PtrGroundArea ground_area = simulation_get_ground_area (simulation);
	PtrGroundAreaEnergyMapNavigator ground_area_energy_map_navigator = simulation_get_energy_map_navigator (simulation);
	
	assert (ground_area != NULL);
	assert (ground_area_energy_map_navigator != NULL);
	
	ground_area_energy_map_navigator_move_position (ground_area_energy_map_navigator, 0);
	int count_energy_map = ground_area_energy_map_navigator_get_count (ground_area_energy_map_navigator);
	
	int i = 0;
	for (i = 0; i < count_energy_map; i++)
	{
		char filename[255];
		sprintf (filename, "%s_%d.png", prefix, i);
		
		
		GdkPixbuf* picture = ground_area_to_pixbuf (ground_area);
		PtrGroundAreaEnergyMap ground_area_energy_map = ground_area_energy_map_navigator_get_current (ground_area_energy_map_navigator);
		picture = ground_area_energy_map_to_pixbuf (picture, ground_area_energy_map);
		gdk_pixbuf_save (picture, filename, "png", NULL, NULL);
		
		ground_area_energy_map_navigator_move_next (ground_area_energy_map_navigator);
	}
	
	ground_area_energy_map_navigator_move_position (ground_area_energy_map_navigator, 0);
	
	printf("Images sauvegardee.\n");
}

void PrintReport (PtrSimulation simulation)
{
	/*printf ("Entrez le nom du fichier report :\n");
	char prefix[250];
	scanf ("%s", prefix);
	
	char filename[255];
	sprintf (filename, "%s.png", prefix);
	FILE* file = fopen (filename, "r");
	if (file != NULL)
	{
		PtrGroundAreaEnergyTextStorage ground_area_energy_storage = NULL;
		ground_area_energy_text_storage_create (&ground_area_energy_storage);
		ground_area_energy_text_storage_set_file (ground_area_energy_storage, file);
		ground_area_energy_text_storage_write_file (ground_area_energy_storage, simulation -> file_ground_area_energy_map);
		ground_area_energy_text_storage_destroy (&ground_area_energy_storage);
		fclose (file);
	}
	else
	{
		fprintf (stderr, "PrintReport, impossible d'ouvrir %s.\n", filename);
	}*/
}
