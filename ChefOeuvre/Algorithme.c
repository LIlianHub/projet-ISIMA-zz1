#include <stdio.h>
#include <stdlib.h>

#include <stdlib.h>
#include <stdio.h>

#include "Config.h"

/*Création tableau*/

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
// placement bordure
void InitPlateau(int **plateau)
{
    for (int j = 0; j < DIMENSION_TAB_JEU; j++)
    {
        plateau[0][j] = 2;
    }
    for (int i = 0; i < DIMENSION_TAB_JEU; i++)
    {
        plateau[i][0] = 2;
    }
    for (int j = 0; j < DIMENSION_TAB_JEU; j++)
    {
        plateau[DIMENSION_TAB_JEU - 1][j] = 2;
    }
    for (int i = 0; i < DIMENSION_TAB_JEU; i++)
    {
        plateau[i][DIMENSION_TAB_JEU - 1] = 2;
    }
}

/*LIberation tableau*/

void liberer_tableau(int **tableau, int nb_lignes)
{
    int i;
    for (i = 0; i < nb_lignes; i++)
    {
        free(tableau[i]);
    }
    free(tableau);
}

void afficher_tableau(int **tableau, int nb_lignes, int nb_colonnes)
{
    int i, j;
    for (i = 0; i < nb_lignes; i++)
    {

        for (j = 0; j < nb_colonnes; j++)
        {
            printf("%d ", tableau[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* Création du serpent au milieu du cadre */
void InitialisationSerpent(int **tableau)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        tableau[i][1] = (DIMENSION_TAB_JEU / 2) - 2 + i;
        tableau[i][0] = DIMENSION_TAB_JEU / 2;
    }
    for (j = 3; j < DIMENSION_TAB_POS; j++)
    {
        tableau[j][0] = -1;
        tableau[j][1] = -1;
    }
}

/* Création des probabilités de changement de place de la pomme : matrice de Markov */

void decalagedroite(int **serpent, int direction, int aManger, int *taille_serpent)
{
    int x0, y0, i;
    /*on enregistre tete serpent*/
    x0 = serpent[0][0];
    y0 = serpent[0][1];

    /* On décale a droite */
    // on enregistre fin si il a mangé pomme
    int save_finX = serpent[(*taille_serpent) - 1][0];
    int save_finY = serpent[(*taille_serpent) - 1][1];

    for (i = (*taille_serpent) - 1; i > 0; i--)
    {
        serpent[i][0] = serpent[i - 1][0];
        serpent[i][1] = serpent[i - 1][1];
    }

    switch (direction)
    {
    case 0: // Le serpent va en haut
        // printf("haut\n");
        serpent[0][0] = x0 - 1;
        serpent[0][1] = y0;

        break;
    case 1: // Le serpent va en bas
        // printf("bas\n");
        serpent[0][0] = x0 + 1;
        serpent[0][1] = y0;

        break;
    case 2: // Le serpent va à droite
        // printf("droite\n");
        serpent[0][0] = x0;
        serpent[0][1] = y0 + 1;

        break;
    case 3: // Le serpent va à gauche
        // printf("gauche\n");
        serpent[0][0] = x0;
        serpent[0][1] = y0 - 1;
        break;
    default:
        break;
    }
    if (aManger == 1)
    {
        serpent[*taille_serpent][0] = save_finX;
        serpent[*taille_serpent][1] = save_finY;
        (*taille_serpent)++;
    }
}

/* test sur serpent */
// verifie si le serpent 'sauto touche
// 2 si ok et 0 si mort

int TestCollisionSerpent(int **serpent, int TeteI, int TeteJ, int *taille_serpent)
{
    int retour = 2;
    int i = 0;
    while (i < (*taille_serpent) && retour == 2)
    {
        if (serpent[i][0] == TeteI && serpent[i][1] == TeteJ)
        {
            retour = 0;
        }
        i++;
    }
    return retour;
}

/*renvoie 2 si classique 0 si mort 1 si mange pomme*/
int TestDeplacement(int **serpent, int direction, int *taille_serpent, int **plateau)
{
    int info = 2; // tout est bon en supposition
    int TeteI = serpent[0][0];
    int TeteJ = serpent[0][1];

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
    else if (plateau[TeteI][TeteJ] == 2)
    {
        info = 0; // meurt par mur
    }
    else
    {
        info = TestCollisionSerpent(serpent, TeteI, TeteJ, taille_serpent);
    }

    decalagedroite(serpent, direction, info, taille_serpent);

    return info;
}

/*score*/

int MeilleurScore(int ScoreActuel)
{
    int bestscore;
    char PremiereLigne[10];

    FILE *score = fopen("score/score.txt", "r+");
    if (score == NULL)
    {
        printf("erreur de fichier");
        exit(1);
    }

    bestscore = atoi(fgets(PremiereLigne, 10, score));

    if (bestscore < ScoreActuel)
    {

        bestscore = ScoreActuel;
        rewind(score);
        fprintf(score, "%d", bestscore);
    }

    fclose(score);
    return bestscore;
}