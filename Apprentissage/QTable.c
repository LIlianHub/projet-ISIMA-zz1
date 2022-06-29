#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Config.h"
#include "Algorithme.h"
#include "QTable.h"
#include "Pile.h"

/*Fonctions sur les tableaux float*/

double ***GenereTabFloat(int nb_ligne, int nb_colonne, int nb_profondeur)
{
  double ***tab = NULL;
  tab = (double ***)malloc(nb_ligne * sizeof(double **));

  for (int i = 0; i < nb_colonne; i++)
  {
    tab[i] = (double **)malloc(nb_colonne * sizeof(double *));
    for (int j = 0; j < nb_profondeur; j++)
    {
      tab[i][j] = (double *)calloc(nb_profondeur, sizeof(double));
    }
  }

  return tab;
}

void LibererTabFloat(double ***tab, int nb_ligne, int nb_colonne)
{
  for (int i = 0; i < nb_ligne; i++)
  {
    for (int j = 0; j < nb_colonne; j++)
    {
      free(tab[i][j]);
    }
    free(tab[i]);
  }
  free(tab);
}

/*void AffichageTabFloat(double **tab, int nb_ligne, int nb_colonne)
{
  for (int i = 0; i < nb_ligne; i++)
  {
    for (int j = 0; j < nb_colonne; j++)
    {
      printf("%lf ", tab[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}*/

int EtatAutourActuel(int teteSx, int teteSy, int **serpent)
{
  int etatAutour = 0;

  if () // la case du haut est vide  (0,*,*,*)
  {
    if () // la case du bas est vide   (0,0,*,*)
    {
      if () // la case de droite est vide (0,0,0,*)
      {
        if () // la case de gauche est vide (0,0,0,0)
        {
          etatAutour = 0;
        }
        else // (0,0,0,1)
        {
          etatAutour = 1;
        }
      }
      else // (0,0,1,*)
      {
        if () // (0,0,1,0)
        {
          etatAutour = 2;
        }
        else // (0,0,1,1)
        {
          etatAutour = 3;
        }
      }
    }
    else // la case du haut est vide  (0,1,*,*)
    {
      if () // la case de droite est vide (0,1,0,*)
      {
        if () // la case de gauche est vide (0,1,0,0)
        {
          etatAutour = 4;
        }
        else // (0,1,0,1)
        {
          etatAutour = 5;
        }
      }
      else // (0,1,1,*)
      {
        if () // (0,1,1,0)
        {
          etatAutour = 6;
        }
        else // (0,1,1,1)
        {
          etatAutour = 7;
        }
      }
    }
  }
  else // la case du haut est pleine (1,*,*,*)
  {
    if () // la case du bas est vide   (1,0,*,*)
    {
      if () // la case de droite est vide (1,0,0,*)
      {
        if () // la case de gauche est vide (1,0,0,0)
        {
          etatAutour = 8;
        }
        else // (1,0,0,1)
        {
          etatAutour = 9;
        }
      }
      else // (1,0,1,*)
      {
        if () // (1,0,1,0)
        {
          etatAutour = 10;
        }
        else // (1,0,1,1)
        {
          etatAutour = 11;
        }
      }
    }
    else // la case du haut est vide  (1,1,*,*)
    {
      if () // la case de droite est vide (1,1,0,*)
      {
        if () // la case de gauche est vide (1,1,0,0)
        {
          etatAutour = 12;
        }
        else // (1,1,0,1)
        {
          etatAutour = 13;
        }
      }
      else // (1,1,1,*)
      {
        if () // (1,1,1,0)
        {
          etatAutour = 14;
        }
        else // (1,1,1,1)
        {
          etatAutour = 15;
        }
      }
    }
  }

  return etatAutour;
}

void posPommeAvecCo(int **plateau,
                    int **serpent,
                    int tailleSerpent,
                    int teteSerpent, int *posI, int *posJ)
{
  // printf("tete: %d\n", teteSerpent);
  int i, j, m;
  int compteur = 0;
  int caseVide;

  int caseDispo = ((DIMENSION_TAB_JEU - 2) * (DIMENSION_TAB_JEU - 2)) - tailleSerpent;
  // printf("caseDispo : %d\n", caseDispo);
  int placement = (rand() % caseDispo) + 1;
  // printf("placement : %d\n\n", placement);

  for (i = 1; i < DIMENSION_TAB_JEU - 1; i++)
  {

    for (j = 1; j < DIMENSION_TAB_JEU - 1; j++)
    {
      // printf("compteur : %d\n", compteur);
      caseVide = 1;
      int courant = teteSerpent;

      for (m = 0; m < tailleSerpent; m++)
      {
        if ((i == serpent[courant][0] && j == serpent[courant][1]))
        {
          caseVide = 0;
        }
        courant = courant + 1;
        courant %= DIMENSION_TAB_POS;
      }
      if (caseVide == 1)
      {
        compteur++;
      }
      if (compteur == placement)
      {

        plateau[i][j] = 1;
        *posI = i;
        *posJ = j;
        i = DIMENSION_TAB_JEU; // on incrémente i et j de sorte qu'on sorte de la boucle
        j = DIMENSION_TAB_JEU;
      }
    }
  }
}

/*La Q_Table :
 *elle est de la forme :                                                  ACTIONS
 *                                       Q_Table       |     Haut      |     Bas       |    Droite     |    Gauche     |
 *                   ---------------------------------------------------------------------------------------------------
 * orientation :    état0: S-E           (-1,-1)       |               |               |               |               |
 *                  état1: S             (-1,0 )       |               |               |               |               |
 *                  état2: S-O           (-1,1 )       |               |               |               |               |
 *    ETATS         état3: E             ( 0,-1)       |               |               |               |               |
 *   (9 états)      état4:               ( 0,0 )       |               |               |               |               |
 *                  état5: O             ( 0,1 )       |               |               |               |               |
 *                  état6: N-E           ( 1,-1)       |               |               |               |               |
 *                  état7: N             ( 1,0 )       |               |               |               |               |
 *                  état8: N-O           ( 1,1 )       |               |               |               |               |
 */

/* un épisode est une partie
 *
 * les états sont composés de (nord(1)/memeHauteur(0)/sud(-1),ouest(1)/memeColonne(0)/est(-1)) = les différents composants sont des bools (ex :
 * nord =1 si la pomme est au nord par rapport à la tête du serpent et =-1 si la pomme est au sud )
 *
 * les actions sont   : Haut(0), Bas(1), Droite(2), Gauche(3)
 *
 */

int EtatActuel(int teteSx, int teteSy, int pommex, int pommey)
{
  int directionX = teteSx - pommex; // si positif : ouest sinon est
  int directionY = teteSy - pommey; // si positif : nord sinon su
  int etat = 4;

  if (directionX > 0) // ouest
  {
    if (directionY > 0)
    {
      etat = 8; // nord ouest
    }
    else if (directionY < 0)
    {
      etat = 2; // sud ouest
    }
    else
    {
      etat = 5; // ouest
    }
  }
  else if (directionX < 0) // est
  {
    if (directionY > 0)
    {
      etat = 6; // nord est
    }
    else if (directionY < 0)
    {
      etat = 0; // sud est
    }
    else
    {
      etat = 3; // est
    }
  }
  else // juste nord ou sud
  {
    if (directionY > 0)
    {
      etat = 7; // nord
    }
    else if (directionY < 0)
    {
      etat = 1; // sud
    }
    else
    {
      etat = 4; // sur la pomme
      // etat impossible
    }
  }

  return etat;
}

/*void EcritureQtable(double **Q, int nbLigne, int nbColonne)
{
  FILE *Historique;
  FILE *Last;
  int i, j;

  // on ecrit l'historique dans un fichier
  if ((Historique = fopen("saveQTable/EvolutionQTable.txt", "a+")) != NULL)
  {
    for (i = 0; i < nbLigne; i++)
    {
      for (j = 0; j < nbColonne; j++)
      {
        fprintf(Historique, "%f ", Q[i][j]);
      }
      fprintf(Historique, "\n");
    }
    fprintf(Historique, "\n");
    fclose(Historique);
  }

  if ((Last = fopen("saveQTable/LastQtable.txt", "w")) != NULL)
  {
    for (int i = 0; i < nbLigne; i++)
    {
      for (int j = 0; j < nbColonne; j++)
      {
        fprintf(Last, "%f ", Q[i][j]);
      }
      fprintf(Last, "\n");
    }
    fclose(Last);
  }
}*/

/*void RecupQtable(double **Q, int nbLigne, int nbColonne)
{
  FILE *Save;
  int info;
  if ((Save = fopen("saveQTable/LastQtable.txt", "r")) != NULL)
  {
    for (int i = 0; i < nbLigne; i++)
    {
      for (int j = 0; j < nbColonne; j++)
      {
        info = fscanf(Save, "%lf ", &Q[i][j]);
        if (info == 0)
        {
          printf("Erreur de lecture\n");
        }
      }
    }
    fclose(Save);
  }
}*/

void explorationSerpent(int *pos_i_pomme, int *pos_j_pomme,
                        int *taille_serpent, int **plateau, int **serpent, double ***Q_Table,
                        int epsilon_Greedy, int teteSerpent)
{
  pile_t *PileDonnees;
  initPile(&PileDonnees, TAILLEMAX_APPRENTISSAGE);

  int i = 0;
  double max;
  int action;
  int tmp, j, random;
  float gamma = GAMMA;
  float epsilon = 0.1;

  while (i < TAILLEMAX_APPRENTISSAGE)
  {
    donnees data = {0};
    data.etat = EtatActuel(serpent[teteSerpent][1], serpent[teteSerpent][0], *pos_j_pomme, *pos_i_pomme);
    data.etatAutour = EtatAutourActuel(serpent[teteSerpent][1], serpent[teteSerpent][0], serpent); // finir la fonction

    random = rand() % 101;
    if (random > epsilon_Greedy) // EXPLOITATION
    {
      max = Q_Table[data.etat][0][data.etatAutour];
      action = 0;
      for (j = 1; j < 4; j++)
      {
        if (max < Q_Table[data.etat][j][data.etatAutour])
        {
          max = Q_Table[data.etat][j][data.etatAutour];
          action = j;
        }
      }
      data.action = action; // On prend la plus grande valeur de la ligne de l'état
    }

    else
    {
      data.action = rand() % 4; // EXPLORATION
    }

    tmp = TestDeplacement(serpent, data.action, taille_serpent, plateau, &teteSerpent);

    if (tmp == 2)
    {
      data.recompense = 1 / (1 + exp(-i * 0.1));
    }
    else if (tmp == 1)
    {
      data.recompense = 1;
      ClearMap(plateau);
      posPommeAvecCo(plateau, serpent, *taille_serpent, teteSerpent, pos_i_pomme, pos_j_pomme);
    }
    else
    {
      data.recompense = -1;
      i = TAILLEMAX_APPRENTISSAGE;
    }
    Empiler(PileDonnees, data);
    i++;
  }

  //       ===> On update la Q_Table avec les états

  // on met le dernier état dans la Q_Table
  donnees ite;
  Depiler(PileDonnees, &ite);
  Q_Table[ite.etat][ite.action][ite.etatAutour] += epsilon * (ite.recompense -
                                                              Q_Table[ite.etat][ite.action][ite.etatAutour]);

  // On dépile tant que la pile n'est pas vide et à chaque fois on remplis la Q_Table
  while (!PileVide(PileDonnees))
  {
    Depiler(PileDonnees, &ite);
    max = Q_Table[ite.etat][0][ite.etatAutour];
    for (j = 1; j < 4; j++)
    {
      if (max < Q_Table[ite.etat][j][ite.etatAutour])
      {
        max = Q_Table[ite.etat][j][ite.etatAutour];
      }
      Q_Table[ite.etat][ite.action][ite.etatAutour] += epsilon * (ite.recompense + (gamma * max) - Q_Table[ite.etat][ite.action][ite.etatAutour]);
    }
  }
  LibererPile(PileDonnees);
}

void MainApprentissage(int nbIteration, int **serpent, int **plateau)
{
  int iteration = 0;
  int epsilon_greedy = 100;
  double ***QTable = NULL;
  int nbSave = nbIteration / 10;
  int updateEpsGreedy = nbIteration / 100;
  QTable = GenereTabFloat(NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE, NBRE_ETAT_AUTOUR);
  // RecupQtable(QTable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE);

  for (int i = 0; i < NBRE_ETATS_APPRENTISSAGE; i++)
  {
    for (int j = 0; j < NBRE_ACTION_APPRENTISSAGE; j++)
    {
      for (int k = 0; k < NBRE_ETAT_AUTOUR; k++)
      {
        QTable[i][j][k] = 0;
      }
    }
  }

  while (iteration <= nbIteration)

  {
    // Initilialisation simulation de partie sans interface graphique

    InitPlateau(plateau);
    ClearMap(plateau);

    int taille_serpent = SERPENT_DEMARRAGE;
    int teteSerpent = 0;
    InitialisationSerpent(serpent, &taille_serpent);

    int iPomme, jPomme;
    posPommeAvecCo(plateau, serpent, taille_serpent, teteSerpent, &iPomme, &jPomme);

    explorationSerpent(&iPomme, &jPomme, &taille_serpent, plateau, serpent, QTable, epsilon_greedy, teteSerpent);

    if (iteration % nbSave == 0)
    {
      // EcritureQtable(QTable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE);
      // AffichageTabFloat(QTable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE);
    }

    if (iteration % updateEpsGreedy == 0)
    {
      epsilon_greedy--;
    }
    iteration++;
  }

  LibererTabFloat(QTable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE);
}

/*int UtilisationQTable(int teteSi, int teteSj, int pommeI, int pommeJ, double **Qtable)
{

  int etat = EtatActuel(teteSj, teteSi, pommeJ, pommeI);
  double max = Qtable[etat][0];
  int direction = 0;
  for (int i = 1; i < NBRE_ACTION_APPRENTISSAGE; i++)
  {
    if (max < Qtable[etat][i])
    {
      max = Qtable[etat][i];
      direction = i;
    }
  }

  return direction;
}*/
