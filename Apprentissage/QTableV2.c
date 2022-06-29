#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Config.h"
#include "Algorithme.h"
#include "QTableV2.h"
#include "PileV2.h"

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

/*La Q_Table :
 *elle est de la forme :                                          ACTIONS
 *                          Q_Table         |     Haut      |     Bas       |    Droite     |    Gauche     |
 *            ---------------------------------------------------------------------------------------------------
 * orientation : état0: S-E   (-1,-1)       |               |               |               |               |
 *               état1: S     (-1,0 )       |               |               |               |               |
 *               état2: S-O   (-1,1 )       |               |               |               |               |
 *    ETATS      état3: E     ( 0,-1)       |               |               |               |               |
 *   (9 états)   état4:       ( 0,0 )       |               |               |               |               |
 *               état5: O     ( 0,1 )       |               |               |               |               |
 *               état6: N-E   ( 1,-1)       |               |               |               |               |
 *               état7: N     ( 1,0 )       |               |               |               |               |
 *               état8: N-O   ( 1,1 )       |               |               |               |               |
 *
 *
 *
 *et en 3ème dimension :
 *                        16 états : (caseHaut,caseBas,caseDroite,caseGauche)  avec 0 si vide 1 si pleine
 */

/* un épisode est une partie
 *
 * les états sont composés de (nord(1)/memeHauteur(0)/sud(-1),ouest(1)/memeColonne(0)/est(-1)) = les différents composants sont des bools (ex :
 * nord =1 si la pomme est au nord par rapport à la tête du serpent et =-1 si la pomme est au sud )
 *
 * les actions sont   : Haut(0), Bas(1), Droite(2), Gauche(3)
 *
 */

void explorationSerpent(int *pos_i_tete, int *pos_j_tete, int *pos_i_pomme, int *pos_j_pomme,
						int *taille_serpent, int **plateau, int **serpent, float ***Q_Table,
						etat_t *liste_etats, int epsilon_Greedy, int teteSerpent)
{

	pile_t *PileDonnees;
	initPile(&PileDonnees, TAILLEMAX_APPRENTISSAGE);

	int i = 0;
	int action = 0;
	int tmp, j, random;

	float gamma = 0.5;
	float epsilon = 0.1;
	float max = 0;

	while (i < TAILLEMAX_APPRENTISSAGE)
	{
		donnees data = {0};
		data.etat = EtatActuel(*pos_j_tete, *pos_i_tete, *pos_j_pomme, *pos_i_pomme);
		data.etatAutour = EtatAutourActuel(*pos_j_tete, *pos_i_tete, serpent); // finir la fonction
		random = rand() % 101;
		if (random > epsilon_Greedy) // EXPLOITATION
		{
			for (j = 1; j < 4; j++)
			{
				max = Q_Table[data.etat][0][data.etatAutour];
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
			/*data.action = quelAction(liste_etats[data.etat]);   EXPLORATION   => on doit faire
		  en sorte que l'on prenne en compte l'etatAutour  creer tableau action en fonction de l'action (quelAction) */
		}

		tmp = TestDeplacement(serpent, data.action, taille_serpent, plateau, &teteSerpent);

		if (tmp == 2)
		{
			if (i > 40)
			{
				data.recompense = 1 / (1 + exp(-i * 0.1));
			}
			else
			{
				data.recompense = 0;
			}
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

	// ==> On update la Q_Table avec les états

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
