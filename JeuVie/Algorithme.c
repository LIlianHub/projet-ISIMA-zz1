#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Algorithme.h"

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

/*tor*/

// ecrit le contenu d'un tableau dans un autre
void copyTab(int **src, int **dest, int ligne, int colonne)
{
    for (int i = 0; i < ligne; i++)
    {
        for (int j = 0; j < colonne; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}

int nbVoisinVivantTor(int **tab, int i, int j, int ligne, int colonne)
{
    int cpt = 0;
    for (int k = -1; k <= 1; k++)
    {
        for (int l = -1; l <= 1; l++)
        {
            if (k != 0 || l != 0)
            {
                if (tab[(i + k + ligne) % ligne][(j + l + colonne) % colonne] == '1')
                {
                    cpt++;
                }
            }
        }
    }
    return cpt;
}

void VieTore(int **tab, int **cpyTab, int vie[TAILLE_MASQUE], int mort[TAILLE_MASQUE], int ligne, int colonne)
{
    copyTab(tab, cpyTab, ligne, colonne);

    for (int i = 0; i < ligne; i++)
    {
        for (int j = 0; j < colonne; j++)
        {
            if (cpyTab[i][j] == 1 && vie[nbVoisinVivantTor(cpyTab, i, j, ligne, colonne)] == 0)
            {
                tab[i][j] = 0;
            }
            if (cpyTab[i][j] == 1 && mort[nbVoisinVivantTor(cpyTab, i, j, ligne, colonne)] == 1)
            {
                tab[i][j] = 1;
            }
        }
    }
}

/*Itération reel*/
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

/* 1 Itération du jeu de la vie */

void iterationLimite(int **moment_t, int **tmp, int nb_lignes, int nb_colonnes,
                   int masqueVie[TAILLE_MASQUE],
                   int masqueMort[TAILLE_MASQUE])
{

    copyTab(moment_t, tmp, nb_lignes, nb_colonnes);

    int i, j, m;
    for (i = 0; i < nb_lignes; i++)
    {

        for (j = 0; j < nb_colonnes; j++)
        {

            m = nbvoisinsLimite(tmp, i, j, nb_lignes, nb_colonnes);

            if (tmp[i][j] == 1)
            {

                moment_t[i][j] = masqueVie[m];
            }
            else
            {

                moment_t[i][j] = masqueMort[m];
            }
        }
    }
}

/*Test stagne*/

int TestStagne(int **tab1, int **tab2, int ligne, int colonne)
{
    int retour = 1;
    for (int i = 0; i < ligne; i++)
    {
        for (int j = 0; j < colonne; j++)
        {
            if (tab1[i][j] != tab2[i][j])
                retour = 0;
        }
    }
    return retour;
}
