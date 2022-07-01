#include <stdio.h>
#include <stdlib.h>

#include "Config.h"

/*MARKOV*/
/*
 *tableau de markov qui va contenir les probabilités
 *de passer entre les différents états :
 *vitesse   : indice 0
 *vitesse/2 : indice 1
 *vitesse*2 : indice 2
 *vitesse*3 : indice 3
 *endormi   : indice 4
 */

float markov[5][5] = {{0.4, 0.1, 0.3, 0.15, 0.05},
                      {0.5, 0.15, 0.25, 0, 0.1},
                      {0.14, 0.03, 0.5, 0.3, 0.03},
                      {0.08, 0.07, 0.15, 0.2, 0.6},
                      {0, 0.3, 0, 0, 0.7}};

// passer d'un état à un autre
// avec mon idée

// Passage d'un etat markov à l'autre
int passageMarkov(int EtatPrec)
{
    int i;
    int pourcent = (rand() % 101);
    // On calcul le pourcentage cumulé jusqu'a atteindre la valeur
    // du nombre random tiré
    int cumul = 0;
    for (i = 0; i < NB_ETATS_MARKOV; i++)
    {
        cumul += markov[EtatPrec][i] * 100;
        if (pourcent < cumul)
        {
            EtatPrec = i;
            i = NB_ETATS_MARKOV;
        }
    }
    return EtatPrec;
}

/*Création tableau*/
// Création d'un tableau en 2D de int avec le nombre de colonne et ligne voulu
// Utile pour le tableau du serpent et plateau
int **creer_tableau(int nb_lignes, int nb_colonnes)
{
    int **tableau = (int **)malloc(nb_lignes * sizeof(int *));
    int i;
    for (i = 0; i < nb_lignes; i++)
    {
        tableau[i] = (int *)calloc(nb_colonnes, sizeof(int));
    }
    return tableau;
}

/*INit du plateau*/
// placement bordure et on met toutes la map
// au milieu à 0
void InitPlateau(int **plateau)
{
    for (int i = 0; i < DIMENSION_TAB_JEU; i++)
    {
        for (int j = 0; j < DIMENSION_TAB_JEU; j++)
        {
            if (i == 0 || i == DIMENSION_TAB_JEU - 1 || j == 0 || j == DIMENSION_TAB_JEU - 1)
            {
                plateau[i][j] = 2;
            }
            else
            {
                plateau[i][j] = 0;
            }
        }
    }
}

/*LIberation tableau*/
// Libération d'un tableau 2D de int
void liberer_tableau(int **tableau, int nb_lignes)
{
    int i;
    for (i = 0; i < nb_lignes; i++)
    {
        free(tableau[i]);
    }
    free(tableau);
}

// Affiche un tableau en 2D de int
void afficher_tableau(int **tableau, int nb_lignes, int nb_colonnes)
{
    int i, j;
    for (i = 0; i < nb_lignes; i++)
    {

        for (j = 0; j < nb_colonnes; j++)
        {
            if (tableau[i][j])
                printf("%d ", tableau[i][j]);
            else
                printf("  ");
        }
        printf("\n");
    }
    printf("\n");
}

/* Création du serpent au milieu du cadre */
void InitialisationSerpent(int **tableau, int *tailleSerpent)
{ // on met la tete au milieu et le corps du la droite de cette tête
    int i;
    for (i = 0; i < (*tailleSerpent); i++)
    {
        tableau[i][1] = (DIMENSION_TAB_JEU / 2) - 2 + i;
        tableau[i][0] = DIMENSION_TAB_JEU / 2;
    }
}

/*on utilise un systeme de file avec à chaque itération l'enfilage de la nouvelle tête car le corps lui est inchangé
Si le serpent a mangé on ne défile pas la queue car le serpent à grandit sinon on defile la queue*/
void UpdateSerpent(int **serpent, int aManger, int *taille_serpent, int *teteSerpent, int TeteI, int TeteJ)
{
    // update de la tete
    (*teteSerpent)--;
    if (*teteSerpent < 0)
    {
        *teteSerpent = DIMENSION_TAB_POS - 1;
    }

    serpent[*teteSerpent][0] = TeteI;
    serpent[*teteSerpent][1] = TeteJ;

    // update queue si besoin
    if (aManger == 1)
    {
        (*taille_serpent)++;
    }
}

/* test sur serpent */
// verifie si le serpent s'auto touche
// 2 si ok et 0 si mort
int TestCollisionSerpent(int **serpent, int TeteI, int TeteJ, int *taille_serpent, int *teteSerpent)
{ // on parcourt tout le tableau du serpent en verifiant que la tete ne touche pas le corps
    int retour = 2;
    int cpt = 0;
    int parcours = *teteSerpent;
    while (cpt < (*taille_serpent) && retour == 2)
    {
        if (serpent[parcours][0] == TeteI && serpent[parcours][1] == TeteJ)
        {
            retour = 0;
        }
        cpt++;
        parcours = (parcours + 1);
        parcours %= DIMENSION_TAB_POS;
    }
    return retour;
}

/*renvoie 2 si classique 0 si mort 1 si mange pomme*/
int TestDeplacement(int **serpent, int direction, int *taille_serpent, int **plateau, int *teteSerpent)
{
    int info = 2; // tout est bon en supposition
    // on recupere la tete du serpent
    int TeteI = serpent[*teteSerpent][0];
    int TeteJ = serpent[*teteSerpent][1];

    /*on simule le mouvement calcul la futur position de la tete*/
    switch (direction)
    {
    case 0: // haut
        TeteI -= 1;
        break;
    case 1: // Le serpent va en bas
        TeteI += 1;
        break;
    case 2: // Le serpent va à droite
        TeteJ += 1;
        break;
    case 3: // Le serpent va à gauche
        TeteJ -= 1;
        break;
    default:
        break;
    }

    if (plateau[TeteI][TeteJ] == 1)
    {
        info = 1; // MANGE POMME
    }
    else if (plateau[TeteI][TeteJ] == 2 || plateau[TeteI][TeteJ] == 3)
    {
        info = 0; // meurt par mur ou cactus
    }
    else
    { // renvoie 0 si il se touche 2 si non
        info = TestCollisionSerpent(serpent, TeteI, TeteJ, taille_serpent, teteSerpent);
    }
    // dans tous les cas on deplace la serpent pour avoir l'animation de mort sur l'endroit de la collision
    UpdateSerpent(serpent, info, taille_serpent, teteSerpent, TeteI, TeteJ);

    return info;
}

// change le meilleur score dans le fichier si le score actuel est meilleur et renvoie le plus grand dans tt les cas
int MeilleurScore(int ScoreActuel)
{
    int bestscore;
    char PremiereLigne[40];
    // on ouvre le fichier de score
    FILE *score = NULL;
    if ((score = fopen("score/score.txt", "r+")) != NULL)
    {
        bestscore = atoi(fgets(PremiereLigne, 40, score));
        // si le nouveau score est mieux on ecrase le contenu
        if (bestscore < ScoreActuel)
        {
            bestscore = ScoreActuel;
            rewind(score);
            fprintf(score, "%d", bestscore);
        }
        else
        {
            // pour le retour
            ScoreActuel = bestscore;
        }

        fclose(score);
    }
    return ScoreActuel;
}

/*GestionMuret*/
// Placement des cactus pour gener l'utilisateur et l'obliger à jouer la pomme
void posMuret(int **plateau,
              int **serpent,
              int tailleSerpent,
              int teteSerpent)
{

    int i, j, m;
    int compteur = 0;
    int caseVide;
    // case ou on peut poser la pomme
    int caseDispo = ((DIMENSION_TAB_JEU - 2) * (DIMENSION_TAB_JEU - 2)) - tailleSerpent - 1;
    int placement = (rand() % caseDispo) + 1;

    for (i = 1; i < DIMENSION_TAB_JEU - 1; i++)
    {
        for (j = 1; j < DIMENSION_TAB_JEU - 1; j++)
        {
            caseVide = 1;

            if (plateau[i][j] == 1) // on vérifie si la case est occupé par la pomme
            {
                caseVide = 0;
            }
            else
            {
                int courant = teteSerpent;
                for (m = 0; m < tailleSerpent; m++)
                {
                    if ((i == serpent[courant][0] && j == serpent[courant][1])) /* on vérifie si la case est
                                               occupé par le serpent*/
                    {
                        caseVide = 0;
                    }
                    courant = courant + 1;
                    courant %= DIMENSION_TAB_POS;
                }
            }
            if (caseVide == 1)
            {
                compteur++;
            }
            if (compteur == placement)
            {
                plateau[i][j] = 3;     // en partant du principe qu'un muret au milieu du plateau = 10
                i = DIMENSION_TAB_JEU; // on incrémente i et j de sorte qu'on sorte de la boucle
                j = DIMENSION_TAB_JEU;
            }
        }
    }
}

/*Gestion Pomme*/
// on pose une Pomme dans un endroit vide et on récupère ses coordonnées
void posPommeAvecCo(int **plateau,
					int **serpent,
					int tailleSerpent,
					int teteSerpent, int *posI, int *posJ)
{
	int i, j, m;
	int compteur = 0;
	int caseVide;
	// Le nombre de case de disponible
	int caseDispo = ((DIMENSION_TAB_JEU - 2) * (DIMENSION_TAB_JEU - 2)) - tailleSerpent;
	// On va placer la pomme dans la n-ème case
	int placement = (rand() % caseDispo) + 1;
	for (i = 1; i < DIMENSION_TAB_JEU - 1; i++)
	{
		for (j = 1; j < DIMENSION_TAB_JEU - 1; j++)
		{
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
			if (compteur == placement) // on est dans la n-ème case
			{

				plateau[i][j] = 1;
				*posI = i; // on donne les positons de où la pomme a été posé
				*posJ = j;
				i = DIMENSION_TAB_JEU; // on incrémente i et j de sorte qu'on sorte de la boucle
				j = DIMENSION_TAB_JEU;
			}
		}
	}
}

//on nettoie toute la map de muret et pomme (on touche pas les bordures)
void ClearMap(int **plateau)
{
    for (int i = 1; i < DIMENSION_TAB_JEU - 1; i++)
    { // on compte pas les bordures
        for (int j = 1; j < DIMENSION_TAB_JEU - 1; j++)
        {
            plateau[i][j] = 0;
        }
    }
}