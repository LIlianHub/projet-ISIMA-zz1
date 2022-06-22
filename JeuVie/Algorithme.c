#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAILLE_MASQUE 9

void EcritureConfig(int **tab, int ligne, int colonne)
{
    FILE *fichier = NULL;
    if ((fichier = fopen("LastSave/save.txt", "w+")) != NULL)
    {
        for (int i = 0; i < ligne; i++)
        {
            for (int j = 0; j < colonne; j++)
            {
                char ecriture = (char)tab[i][j];
                fputc(ecriture, fichier);
            }
        }
        fclose(fichier);
    }
}

void LectureFichier(int **tab, int ligne, int colonne)
{
    FILE *fichier = NULL;
    if ((fichier = fopen("LastSave/save.txt", "r")) != NULL)
    {
        for (int i = 0; i < ligne; i++)
        {
            for (int j = 0; j < colonne; j++)
            {
                char lecture = fgetc(fichier);
                tab[i][j] = (int)lecture;
            }
        }
        fclose(fichier);
    }
}

void ClearTab(int **tab, int ligne, int colonne)
{
    for (int i = 0; i < ligne; i++)
    {
        for (int j = 0; j < colonne; j++)
        {
            tab[i][j] = 0;
        }
    }
}

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

/*Afficher un tableau*/

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

/*version fini*/

int nbvoisinsLimite(int **moment_t, int ligne, int colonne, int nb_lignes, int nb_colonnes)
{

    int i, j;
    int nbre = 0;
    for (i = ligne - 1; i < ligne + 2; i++)
    {

        for (j = colonne - 1; j < colonne + 2; j++)
        {

            if (i >= 0 && i >= 0 && i < nb_lignes && j < nb_colonnes && !(i == ligne && j == colonne) && (moment_t[i][j] == 1))
            {

                nbre += 1;
            }
        }
    }
    return nbre;
}

void iterationReelLimite(int **moment_t, int **moment_t1, int nb_lignes, int nb_colonnes,
                   int masqueVie[TAILLE_MASQUE],
                   int masqueMort[TAILLE_MASQUE])
{
    int i, j, m;
    int resultat = 0;
    for (i = 0; i < nb_lignes; i++)
    {

        for (j = 0; j < nb_colonnes; j++)
        {

            if (moment_t[i][j] == 1)
            {

                for (m = 0; m < TAILLE_MASQUE; m++)
                {

                    if (masqueVie[m] == 1 && nbvoisinsLimite(moment_t, i, j, nb_lignes, nb_colonnes) == m)
                    {

                        resultat += 1; // son nombre de voisin est dans le masque de la Vie, il survit
                    }
                }
                if (resultat != 0)
                {
                    moment_t1[i][j] = 1;
                }
            }
            else
            {
                for (m = 0; m < TAILLE_MASQUE; m++)
                {

                    if (masqueMort[m] == 1 && nbvoisinsLimite(moment_t, i, j, nb_lignes, nb_colonnes) == m)
                    {

                        resultat += 1; // son nombre de voisin est dans le masque de la Mort, il ressuscite
                    }
                }
                if (resultat != 0)
                {
                    moment_t1[i][j] = 1;
                }
            }
        }
    }
    int **tmp = moment_t;
    moment_t = moment_t1;
    moment_t1 = tmp;
}