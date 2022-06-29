#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Config.h"
#include "Algorithme.h"
#include "QTable.h"
#include "Pile.h"

/*Fonctions sur les tableaux float*/

float **GenereTabFloat(int nb_ligne, int nb_colonne)
{
  float **tab = NULL;
  tab = (float **)malloc(nb_ligne * sizeof(float *));
  for (int i = 0; i < nb_ligne; i++)
  {
    tab[i] = (float *)calloc(nb_colonne, sizeof(float));
  }

  return tab;
}

void LibererTabFloat(float **tab, int nb_ligne)
{
  for (int i = 0; i < nb_ligne; i++)
  {
    free(tab[i]);
  }
  free(tab);
}

void AffichageTabFloat(float **tab, int nb_ligne, int nb_colonne)
{
  for (int i = 0; i < nb_ligne; i++)
  {
    for (int j = 0; j < nb_colonne; j++)
    {
      printf("%f ", tab[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

/*Fonction sur le jeu du SNAKE  */

etat_t *genereTableauEtat()
{
  etat_t *liste_etats = (etat_t *)malloc(sizeof(etat_t) * NBRE_ETATS_APPRENTISSAGE);
  liste_etats[0].nord_sud = -1;
  liste_etats[0].ouest_est = -1;
  liste_etats[1].nord_sud = -1;
  liste_etats[1].ouest_est = 0;
  liste_etats[2].nord_sud = -1;
  liste_etats[2].ouest_est = 1;
  liste_etats[3].nord_sud = 0;
  liste_etats[3].ouest_est = -1;
  liste_etats[4].nord_sud = 0;
  liste_etats[4].ouest_est = 0;
  liste_etats[5].nord_sud = 0;
  liste_etats[5].ouest_est = 1;
  liste_etats[6].nord_sud = 1;
  liste_etats[6].ouest_est = -1;
  liste_etats[7].nord_sud = 1;
  liste_etats[7].ouest_est = 0;
  liste_etats[8].nord_sud = 1;
  liste_etats[8].ouest_est = 1;

  return liste_etats;
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
      // printf("compteurFinBoucle : %d\n", compteur);
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
    }
  }

  return etat;
}

int quelAction(etat_t etatActuel)
{
  int tmp;
  int actionActuel = 4;

  if ((abs(etatActuel.nord_sud) + abs(etatActuel.ouest_est)) == 2) // 2 directions possibles
  {
    tmp = rand() % 2; // représente notre proba aléatoire uniforme

    if (tmp == 0) // on dit que si ==0 alors on agira sur la ligne
    {
      if (etatActuel.nord_sud > 0)
      {
        actionActuel = 0;
      }
      else
      {
        actionActuel = 1;
      }
    }
    else // sinon ce sera la colonne
    {
      if (etatActuel.ouest_est > 0)
      {
        actionActuel = 3;
      }
      else
      {
        actionActuel = 2;
      }
    }
  }
  else if (abs(etatActuel.nord_sud) == 1) // bonne colonne - mauvaise ligne
  {
    if (etatActuel.nord_sud > 0)
    {
      actionActuel = 0;
    }
    else
    {
      actionActuel = 1;
    }
  }
  else if (abs(etatActuel.ouest_est) == 1) // bonne ligne - mauvaise colonne
  {
    if (etatActuel.ouest_est > 0)
    {
      actionActuel = 3;
    }
    else
    {
      actionActuel = 2;
    }
  }
  return actionActuel;
}

void EcritureQtable(float **Q, int nbLigne, int nbColonne)
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
}

void RecupQtable(float **Q, int nbLigne, int nbColonne)
{
  FILE *Save;
  int info;
  if ((Save = fopen("saveQTable/LastQtable.txt", "r")) != NULL)
  {
    for (int i = 0; i < nbLigne; i++)
    {
      for (int j = 0; j < nbColonne; j++)
      {
        info = fscanf(Save, "%f ", &Q[i][j]);
        if(info == 0){
          printf("Erreur de lecture\n");
        }
      }
    }
    fclose(Save);
  }
}

void explorationSerpent(int *pos_i_tete, int *pos_j_tete, int *pos_i_pomme, int *pos_j_pomme,
                        int *taille_serpent, int **plateau, int **serpent, float **Q_Table,
                        etat_t *liste_etats, int epsilon_Greedy, int teteSerpent)
{
  /*int listeEtats[TAILLEMAX_APPRENTISSAGE] = {0};
    int listeActions[TAILLEMAX_APPRENTISSAGE] = {0};
    int listeRecompense[TAILLEMAX_APPRENTISSAGE] = {0};*/

  pile_t *PileDonnees;
  initPile(&PileDonnees, TAILLEMAX_APPRENTISSAGE);

  int i = 0;
  int max = 0;
  int action = 0;
  int tmp, j;
  int random;

  float gamma = 0.5;
  float epsilon = 0.1;

  while (i < TAILLEMAX_APPRENTISSAGE)
  {
    donnees data = {0};
    data.etat = EtatActuel(*pos_j_tete, *pos_i_tete, *pos_j_pomme, *pos_i_pomme);
    random = rand() % 101;
    if (random > epsilon_Greedy) // EXPLOITATION
    {
      for (j = 0; j < 4; j++)
      {
        if (max < Q_Table[data.etat][j])
        {
          max = Q_Table[data.etat][j];
          action = j;
        }
        data.action = action; // On prend la plus grande valeur de la ligne de l'état
      }
    }
    else
    {
      data.action = quelAction(liste_etats[data.etat]); // EXPLORATION
    }

    tmp = TestDeplacement(serpent, data.action, taille_serpent, plateau, &teteSerpent);

    if (tmp == 2)
    {
      data.recompense = 1 / (1 + exp(-i * 0.1));
    }
    else if (tmp == 1)
    {
      data.recompense = 1;
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
  Depiler(PileDonnees, &ite); // -> ça vient de là le seg fault
  Q_Table[ite.etat][ite.action] += epsilon * (ite.recompense - Q_Table[ite.etat][ite.action]);

  // On dépile tant que la pile n'est pas vide et à chaque fois on remplis la Q_Table
  while (!PileVide(PileDonnees))
  {
    Depiler(PileDonnees, &ite);
    for (j = 1; j < 4; j++)
    {
      max = Q_Table[ite.etat][1];
      if (max < Q_Table[ite.etat][j])
      {
        max = Q_Table[ite.etat][j];
      }
      Q_Table[ite.etat][ite.action] += epsilon * (ite.recompense + (gamma * max) - Q_Table[ite.etat][ite.action]);
    }
  }

  LibererPile(PileDonnees);
}

void MainApprentissage(etat_t *listeEtat, int nbIteration, int **serpent, int **plateau)
{
  int iteration = 0;
  int epsilon_greedy = 100;
  float **QTable = NULL;
  int nbSave = nbIteration / 10;
  int updateEpsGreedy = nbIteration / 100;
  QTable = GenereTabFloat(NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE);
  //RecupQtable(QTable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE);

  for (int i = 0; i < NBRE_ETATS_APPRENTISSAGE; i++)
  {
    for (int j = 0; j < NBRE_ACTION_APPRENTISSAGE; j++)
    {
      QTable[i][j] = 0.5;
    }
  }

  while (iteration < nbIteration)

  {
    // Initilialisation simulation de partie sans interface graphique
    int taille_serpent = SERPENT_DEMARRAGE;
    InitPlateau(plateau);
    InitialisationSerpent(serpent, &taille_serpent);
    int teteSerpent = 0;
    int iPomme, jPomme;
    posPommeAvecCo(plateau, serpent, taille_serpent, teteSerpent, &iPomme, &jPomme);
    explorationSerpent(&serpent[teteSerpent][0], &serpent[teteSerpent][1], &iPomme, &jPomme, &taille_serpent, plateau, serpent, QTable, listeEtat, epsilon_greedy, teteSerpent);
    if (iteration % nbSave == 0)
    {
      EcritureQtable(QTable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE);
      AffichageTabFloat(QTable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE);
    }

    if (iteration % updateEpsGreedy == 0)
    {
      epsilon_greedy--;
    }
    iteration++;
  }

  LibererTabFloat(QTable, NBRE_ETATS_APPRENTISSAGE);
}

int UtilisationQTable(int teteSi, int teteSj, int pommeI, int pommeJ, float **Qtable)
{

  int etat = EtatActuel(teteSj, teteSi, pommeJ, pommeI);
  float max = Qtable[etat][0];
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
}
