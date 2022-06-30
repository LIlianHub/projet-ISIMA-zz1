#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Config.h"
#include "Algorithme.h"
#include "QTable.h"
#include "Pile.h"

int EtatAutourActuel(int teteSy, int teteSx, int **serpent, int **plateau, int *tailleSerpent, int *teteSerpent)
{
	int etatAutour = 0; // etat 0 impossible car toujours son corps à proximité
	int ValeurDessus = TestCollisionSerpent(serpent, teteSy - 1, teteSx, tailleSerpent, teteSerpent);
	int ValeurDessous = TestCollisionSerpent(serpent, teteSy + 1, teteSx, tailleSerpent, teteSerpent);
	int ValeurGauche = TestCollisionSerpent(serpent, teteSy, teteSx - 1, tailleSerpent, teteSerpent);
	int ValeurDroite = TestCollisionSerpent(serpent, teteSy, teteSx + 1, tailleSerpent, teteSerpent);
	// >= 2 car bordure 2 et cactus 3

	if (plateau[teteSx][teteSy - 1] < 2 && ValeurDessus == 2) // la case du haut est vide  (0,*,*,*)
	{
		if (plateau[teteSx][teteSy + 1] < 2 && ValeurDessous == 2) // la case du bas est vide   (0,0,*,*)
		{
			if (plateau[teteSx + 1][teteSy] < 2 && ValeurDroite == 2) // la case de droite est vide (0,0,0,*)
			{
				if (plateau[teteSx - 1][teteSy] < 2 && ValeurGauche == 2) // la case de gauche est vide (0,0,0,0)
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
				if (plateau[teteSx - 1][teteSy] < 2 && ValeurGauche == 2) // (0,0,1,0)
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
			if (plateau[teteSx + 1][teteSy] < 2 && ValeurDroite == 2) // la case de droite est vide (0,1,0,*)
			{
				if (plateau[teteSx - 1][teteSy] < 2 && ValeurGauche == 2) // la case de gauche est vide (0,1,0,0)
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
				if (plateau[teteSx - 1][teteSy] < 2 && ValeurGauche == 2) // (0,1,1,0)
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
		if (plateau[teteSx][teteSy + 1] < 2 && ValeurDessous == 2) // la case du bas est vide   (1,0,*,*)
		{
			if (plateau[teteSx + 1][teteSy] < 2 && ValeurDroite == 2) // la case de droite est vide (1,0,0,*)
			{
				if (plateau[teteSx - 1][teteSy] < 2 && ValeurGauche == 2) // la case de gauche est vide (1,0,0,0)
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
				if (plateau[teteSx - 1][teteSy] < 2 && ValeurGauche == 2) // (1,0,1,0)
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
			if (plateau[teteSx + 1][teteSy] < 2 && ValeurDroite == 2) // la case de droite est vide (1,1,0,*)
			{
				if (plateau[teteSx - 1][teteSy] < 2 && ValeurGauche == 2) // la case de gauche est vide (1,1,0,0)
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
				if (plateau[teteSx - 1][teteSy] < 2 && ValeurGauche == 2) // (1,1,1,0)
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

// On récupére l'orientation de la pomme par rapport à la tête du serpent
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

// on ecrit la Qtable dans un fichier
void EcritureQtable(double Q[NBRE_ETATS_APPRENTISSAGE][NBRE_ACTION_APPRENTISSAGE][NBRE_ETAT_AUTOUR], int nbLigne, int nbColonne, int profondeur)
{
	FILE *Last;
	// la Q table est affichée dans un fichier avec 16 matrices d'états les une en dessous des autres
	if ((Last = fopen("saveQTable/LastQtable.txt", "w")) != NULL)
	{
		for (int i = 0; i < profondeur; i++)
		{
			for (int j = 0; j < nbLigne; j++)
			{
				for (int k = 0; k < nbColonne; k++)
				{
					fprintf(Last, "%lf ", Q[j][k][i]);
				}
				fprintf(Last, "\n");
			}
			fprintf(Last, "\n");
		}
		fclose(Last);
	}
}

// on lit la Qtable dans un fichier
void RecupQtable(double Q[NBRE_ETATS_APPRENTISSAGE][NBRE_ACTION_APPRENTISSAGE][NBRE_ETAT_AUTOUR], int nbLigne, int nbColonne, int profondeur)
{
	FILE *Save;
	int info;
	if ((Save = fopen("saveQTable/LastQtable.txt", "r")) != NULL)
	{
		for (int i = 0; i < profondeur; i++)
		{
			for (int j = 0; j < nbLigne; j++)
			{
				for (int k = 0; k < nbColonne; k++)
				{
					info = fscanf(Save, "%lf ", &Q[j][k][i]);
					if (info == 0)
					{
						printf("Erreur de lecture\n");
					}
				}
			}
		}
		fclose(Save);
	}
}

// on affiche la Qtable dans un terminal
void AfficherQTAble(double Q[NBRE_ETATS_APPRENTISSAGE][NBRE_ACTION_APPRENTISSAGE][NBRE_ETAT_AUTOUR], int ligne, int colonne, int profondeur)
{
	for (int i = 0; i < profondeur; i++)
	{
		for (int j = 0; j < ligne; j++)
		{
			for (int k = 0; k < colonne; k++)
			{
				printf("%lf ", Q[j][k][i]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

void ApprentissageSerpent(int *pos_i_pomme, int *pos_j_pomme,
						  int *taille_serpent, int **plateau, int **serpent, double Q_Table[NBRE_ETATS_APPRENTISSAGE][NBRE_ACTION_APPRENTISSAGE][NBRE_ETAT_AUTOUR],
						  int epsilon_Greedy, int *teteSerpent, double gamma)
{
	pile_t *PileDonnees;
	initPile(&PileDonnees, TAILLEMAX_APPRENTISSAGE);

	int i = 0;
	double max;
	int action;
	int tmp, j, random;
	float epsilon = 0.01;
	int sigmo = 0;
	int nbIterationCactus = 0;

	while (i < TAILLEMAX_APPRENTISSAGE)
	{
		donnees data = {0};
		data.etat = EtatActuel(serpent[*teteSerpent][1], serpent[*teteSerpent][0], *pos_j_pomme, *pos_i_pomme);
		data.etatAutour = EtatAutourActuel(serpent[*teteSerpent][0], serpent[*teteSerpent][1], serpent, plateau, taille_serpent, teteSerpent); // finir la fonction

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

		tmp = TestDeplacement(serpent, data.action, taille_serpent, plateau, teteSerpent);

		if (tmp == 2)
		{
			data.recompense = -(1 / (1 + exp(-sigmo * 0.1)));
			// data.recompense = 0;
			sigmo++;
			// gestion cactus
			if (AVEC_CACTUS)
			{
				nbIterationCactus++;
				if (nbIterationCactus == ITER_POUR_MUR)
				{
					nbIterationCactus = 0;
					posMuret(plateau, serpent, *taille_serpent, *teteSerpent);
				}
			}
		}
		else if (tmp == 1)
		{
			data.recompense = 10;
			sigmo = 0;
			nbIterationCactus = 0;
			ClearMap(plateau);
			posPommeAvecCo(plateau, serpent, *taille_serpent, *teteSerpent, pos_i_pomme, pos_j_pomme);
		}
		else
		{
			data.recompense = -10;
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
	double gamma = GAMMA;
	int nbSave = nbIteration / 10;
	int updateEpsGreedyGamma = nbIteration / 100;
	double QTable[NBRE_ETATS_APPRENTISSAGE][NBRE_ACTION_APPRENTISSAGE][NBRE_ETAT_AUTOUR] = {{{0.0}}};

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

	// RecupQtable(QTable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE, NBRE_ETAT_AUTOUR);

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

		ApprentissageSerpent(&iPomme, &jPomme, &taille_serpent, plateau, serpent, QTable, epsilon_greedy, &teteSerpent, gamma);

		if (iteration % nbSave == 0)
		{
			EcritureQtable(QTable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE, NBRE_ETAT_AUTOUR);
			// AfficherQTAble(QTable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE, NBRE_ETAT_AUTOUR);
		}

		if (iteration % updateEpsGreedyGamma == 0)
		{
			epsilon_greedy--;
			gamma -= 0.001;
			printf("Execution: %d / %d \n", iteration, nbIteration);
			printf("gamma : %lf\n\n", gamma);
		}
		iteration++;
	}
}

// On utilise la Qtable pour decider les mouvements à faire (la valeur max de l'état autour et l'état lié à la pomme actuel)
int UtilisationQTable(int teteSi, int teteSj, int pommeI, int pommeJ, double QTable[NBRE_ETATS_APPRENTISSAGE][NBRE_ACTION_APPRENTISSAGE][NBRE_ETAT_AUTOUR],
					  int **serpent, int **plateau, int *taille_serpent, int *teteSerpent)
{
	int etat = EtatActuel(teteSj, teteSi, pommeJ, pommeI);
	int etat_autour = EtatAutourActuel(teteSi, teteSj, serpent, plateau, taille_serpent, teteSerpent);
	double max = QTable[etat][0][etat_autour];
	int action = 0;
	for (int i = 0; i < NBRE_ACTION_APPRENTISSAGE; i++)
	{
		if (QTable[etat][i][etat_autour] > max)
		{
			max = QTable[etat][i][etat_autour];
			action = i;
		}
	}

	return action;
}


// Trace de la fonction etat autour non concluante
/*if (ValeurDessous == 2 && ValeurDessus == 2 && ValeurDroite == 2 && ValeurGauche == 0 &&
	plateau[teteSi - 1][teteSj] < 2 && plateau[teteSi + 1][teteSj] < 2 && plateau[teteSi][teteSj - 1] >= 2 &&
	plateau[teteSi][teteSj + 1] < 2)
{
	etatAutour = 1; // un element problèmatique à gauche
}
if (ValeurDessous == 2 && ValeurDessus == 2 && ValeurDroite == 0 && ValeurGauche == 2 &&
		 plateau[teteSi - 1][teteSj] < 2 && plateau[teteSi + 1][teteSj] < 2 && plateau[teteSi][teteSj - 1] < 2 &&
		 plateau[teteSi][teteSj + 1] >= 2)
{
	etatAutour = 2; // un element problèmatique à droite
}
if (ValeurDessous == 2 && ValeurDessus == 2 && ValeurDroite == 0 && ValeurGauche == 0 &&
		 plateau[teteSi - 1][teteSj] < 2 && plateau[teteSi + 1][teteSj] < 2 && plateau[teteSi][teteSj - 1] >= 2 &&
		 plateau[teteSi][teteSj + 1] >= 2)
{
	etatAutour = 3; // un element problèmatique à droite et à gauche
}
if (ValeurDessous == 0 && ValeurDessus == 2 && ValeurDroite == 2 && ValeurGauche == 2 &&
		 plateau[teteSi - 1][teteSj] < 2 && plateau[teteSi + 1][teteSj] >= 2 && plateau[teteSi][teteSj - 1] < 2 &&
		 plateau[teteSi][teteSj + 1] < 2)
{
	etatAutour = 4; // un element problèmatique en bas
}
if (ValeurDessous == 0 && ValeurDessus == 2 && ValeurDroite == 2 && ValeurGauche == 0 &&
		 plateau[teteSi - 1][teteSj] < 2 && plateau[teteSi + 1][teteSj] >= 2 && plateau[teteSi][teteSj - 1] >= 2 &&
		 plateau[teteSi][teteSj + 1] < 2)
{
	etatAutour = 5; // un element problèmatique en bas et à gauche
}
if (ValeurDessous == 0 && ValeurDessus == 2 && ValeurDroite == 0 && ValeurGauche == 2 &&
		 plateau[teteSi - 1][teteSj] < 2 && plateau[teteSi + 1][teteSj] >= 2 && plateau[teteSi][teteSj - 1] < 2 &&
		 plateau[teteSi][teteSj + 1] >= 2)
{
	etatAutour = 6; // un element problèmatique en bas et à droite
}
if (ValeurDessous == 0 && ValeurDessus == 2 && ValeurDroite == 0 && ValeurGauche == 0 &&
		 plateau[teteSi - 1][teteSj] < 2 && plateau[teteSi + 1][teteSj] >= 2 && plateau[teteSi][teteSj - 1] >= 2 &&
		 plateau[teteSi][teteSj + 1] >= 2)
{
	etatAutour = 7; // un element problèmatique en bas et à droite et à gauche
}
if (ValeurDessous == 2 && ValeurDessus == 0 && ValeurDroite == 2 && ValeurGauche == 2 &&
		 plateau[teteSi - 1][teteSj] >= 2 && plateau[teteSi + 1][teteSj] < 2 && plateau[teteSi][teteSj - 1] < 2 &&
		 plateau[teteSi][teteSj + 1] < 2)
{
	etatAutour = 8; // un element problèmatique en haut
}
if (ValeurDessous == 2 && ValeurDessus == 0 && ValeurDroite == 2 && ValeurGauche == 0 &&
		 plateau[teteSi - 1][teteSj] >= 2 && plateau[teteSi + 1][teteSj] < 2 && plateau[teteSi][teteSj - 1] >= 2 &&
		 plateau[teteSi][teteSj + 1] < 2)
{
	etatAutour = 9; // un element problèmatique en haut et à gauche
}
if (ValeurDessous == 2 && ValeurDessus == 0 && ValeurDroite == 0 && ValeurGauche == 2 &&
		 plateau[teteSi - 1][teteSj] >= 2 && plateau[teteSi + 1][teteSj] < 2 && plateau[teteSi][teteSj - 1] < 2 &&
		 plateau[teteSi][teteSj + 1] >= 2)
{
	etatAutour = 10; // un element problèmatique en haut et à droite
}
if (ValeurDessous == 2 && ValeurDessus == 0 && ValeurDroite == 0 && ValeurGauche == 0 &&
		 plateau[teteSi - 1][teteSj] >= 2 && plateau[teteSi + 1][teteSj] < 2 && plateau[teteSi][teteSj - 1] >= 2 &&
		 plateau[teteSi][teteSj + 1] >= 2)
{
	etatAutour = 11; // un element problèmatique en haut et à droite et a gauche
}
if (ValeurDessous == 0 && ValeurDessus == 0 && ValeurDroite == 2 && ValeurGauche == 2 &&
		 plateau[teteSi - 1][teteSj] >= 2 && plateau[teteSi + 1][teteSj] >= 2 && plateau[teteSi][teteSj - 1] < 2 &&
		 plateau[teteSi][teteSj + 1] < 2)
{
	etatAutour = 12; // un element problèmatique en haut et en bas
}
if (ValeurDessous == 0 && ValeurDessus == 0 && ValeurDroite == 2 && ValeurGauche == 0 &&
		 plateau[teteSi - 1][teteSj] >= 2 && plateau[teteSi + 1][teteSj] >= 2 && plateau[teteSi][teteSj - 1] >= 2 &&
		 plateau[teteSi][teteSj + 1] < 2)
{
	etatAutour = 13; // un element problèmatique en haut et en bas et a gauche
}
if (ValeurDessous == 0 && ValeurDessus == 0 && ValeurDroite == 0 && ValeurGauche == 2 &&
		 plateau[teteSi - 1][teteSj] >= 2 && plateau[teteSi + 1][teteSj] >= 2 && plateau[teteSi][teteSj - 1] < 2 &&
		 plateau[teteSi][teteSj + 1] >= 2)
{
	etatAutour = 14; // un element problèmatique en haut et en bas et a droite
}
if (ValeurDessous == 0 && ValeurDessus == 0 && ValeurDroite == 0 && ValeurGauche == 0 &&
		 plateau[teteSi - 1][teteSj] >= 2 && plateau[teteSi + 1][teteSj] >= 2 && plateau[teteSi][teteSj - 1] >= 2 &&
		 plateau[teteSi][teteSj + 1] >= 2)
{
	etatAutour = 15; // un element problèmatique en haut et en bas et a droite et a gauche
}*/