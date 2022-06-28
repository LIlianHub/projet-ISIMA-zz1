#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Config.h"
#include "Algorithme.h"
#include "QTable.h"

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

/*etat calculEtat(int pos_x_tete, int pos_y_tete, int pos_x_pomme, int pos_y_pomme)
{
  etat etatActuel;

  if(pos_x_tete < pos_x_pomme)    //la pomme est à l'est de la la tête
    {
      etatActuel.ouest_est = -1;
    }
  else if(pos_x_tete > pos_x_pomme) // A l'ouest
    {
      etatActuel.ouest_est = 1;
    }
  else
    {
      etatActuel.ouest_est = 0; // sur la même colonne
    }


  if(pos_y_tete < pos_y_pomme) // La pomme est au sud de la tête
    {
      etatActuel.nord_sud = -1;
    }
  else if(pos_y_tete > pos_y_pomme) // Au nord
    {
      etatActuel.nord_sud = 1;
    }
  else
    {
      etatActuel.nord_sud = 0; //même ligne
    }


  return etatActuel;
}
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
    }
    fclose(Historique);

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
    }
    fclose(Last);
}

void RecupQtable(float **Q, int nbLigne, int nbColonne)
{
    FILE *Save;

    if ((Save = fopen("saveQTable/LastQtable.txt", "r")) != NULL)
    {
        for (int i = 0; i < nbLigne; i++)
        {
            for (int j = 0; j < nbColonne; j++)
            {
                fscanf(Save, "%f ", &Q[i][j]);
            }
        }
    }

    fclose(Save);
}

/*explorationSerpent(pos_tete, posPomme, listeEtat, listeAction, liste recompense, Q_Table)
 *
 *        => On calcul l'état avec la pos_tete et pos_pomme
 *                .update listeEtat        (FAIT)
 *
 *        => le serpent va dans direction aléatoire entre toutes les directions d'état = 1 et -1
 *	          .update listeAction      (FAIT)
 *		  .update pos_tete
 *
 *	 => testDéplacement pour savoir la récompense
 *	          .update listeRecompense
 *	     	  => Si recompense = - 1  : On stoppe l'épisode
 *		  => Sinon : itération suivante
 *
 *
 *
 *        ===> On update la Q_Table avec les états
 *
 *        ___________> on répète on répère on répète pour avoir une Q_table la plus représentative
 */

void explorationSerpent(int *pos_i_tete, int *pos_j_tete, int *pos_i_pomme, int *pos_j_pomme,
                        int *taille_serpent, int **plateau, int **serpent, float **Q_Table,
                        etat_t *liste_etats, float epsilon, float gamma, int teteSerpent)
{
    int listeEtats[TAILLEMAX_APPRENTISSAGE] = {0};
    int listeActions[TAILLEMAX_APPRENTISSAGE] = {0};
    int listeRecompense[TAILLEMAX_APPRENTISSAGE] = {0};

    int i = 0;
    int fin = 0;
    int max = 0;
    int tmp, j;

    while (i < TAILLEMAX_APPRENTISSAGE)
    {
        listeEtats[i] = EtatActuel(*pos_j_tete, *pos_i_tete, *pos_j_pomme, *pos_i_pomme); // on update la listeEtat
        // printf("Etat actuel : %d\n", listeEtats[i]);
        printf("Action actuelle : %d, %d\n", liste_etats[listeEtats[i]].nord_sud, liste_etats[listeEtats[i]].ouest_est);
        listeActions[i] = quelAction(liste_etats[listeEtats[i]]);                               // on update la listeAction
        tmp = TestDeplacement(serpent, listeActions[i], taille_serpent, plateau, &teteSerpent); // on bouge le serpent
        if (tmp == 2)
        {
            listeRecompense[i] = 0; // le serpent avance
        }
        else if (tmp == 1)
        {
            listeRecompense[i] = 1;
            posPommeAvecCo(plateau, serpent, *taille_serpent, teteSerpent, pos_i_pomme, pos_j_pomme);
        }
        else
        {
            listeRecompense[i] = -1;
            fin = i;
            i = TAILLEMAX_APPRENTISSAGE;
        }
        i++;
    }

    if (i == TAILLEMAX_APPRENTISSAGE)
    {
        // veut dire que l'on s'est arrété parce que on a dépassé la tailleMax d'états
        // on alloue aussi mais avec un epsilon epsilon (moins représentatif)
        fin = TAILLEMAX_APPRENTISSAGE;
        epsilon = 0.05;
    }

    //       ===> On update la Q_Table avec les états
    Q_Table[listeEtats[fin - 1]][listeActions[fin - 1]] += epsilon * (listeRecompense[fin - 1] -
                                                                      Q_Table[listeEtats[fin - 1]][listeActions[fin - 1]]);

    for (i = fin - 2; i >= 0; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (max < Q_Table[listeEtats[i + 1]][j])
            {
                max = Q_Table[listeEtats[i + 1]][j];
            }
            Q_Table[listeEtats[i]][listeActions[i]] += epsilon * (listeRecompense[i] + (gamma * max) - Q_Table[listeEtats[i]][listeActions[i]]);
        }
    }
    printf("Apprentissage Fait !\n");
}

/*exploitationSerpent(Q_table, pos_tete, posPomme)
 *
 *             => le serpent va faire l'action avec la plus grande QValue en fonction de l'état ou
 *             il est
 *                           .update pos_tete
 *             => on recalcule l'état avec la pose_tete et posPomme
 *                           .update etat
 *             => testDeplacement pour savoir la récompense
 *                     => Si pomme touchée continuer exploitation
 *                     => Si un mur est touché, perdu
 */

void MainApprentissage(etat_t *listeEtat, int nbIteration, int **serpent, int **plateau)
{
    int iteration = 0;
    float **QTable = NULL;
    QTable = GenereTabFloat(NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE);
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
         explorationSerpent(&serpent[teteSerpent][0], &serpent[teteSerpent][1], &iPomme, &jPomme, &taille_serpent, plateau, serpent, QTable, listeEtat, 0.1, GAMMA, teteSerpent);
         AffichageTabFloat(QTable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE);
     }

    LibererTabFloat(QTable, NBRE_ETATS_APPRENTISSAGE);
}