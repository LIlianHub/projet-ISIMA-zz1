#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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


