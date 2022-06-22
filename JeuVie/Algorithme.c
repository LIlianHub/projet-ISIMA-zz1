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

void iterationReelLimite(int nb_lignes, int nb_colonnes,
                         int masqueVie[TAILLE_MASQUE],
                         int masqueMort[TAILLE_MASQUE])
{
    int i, j, m;
    int resultat = 0;
    for (i = 0; i < nb_lignes; i++)
    {

        for (j = 0; j < nb_colonnes; j++)
        {

            if (TAB1[i][j] == 1)
            {

                for (m = 0; m < TAILLE_MASQUE; m++)
                {

                    if (masqueVie[m] == 1 && nbvoisinsLimite(TAB1, i, j, nb_lignes, nb_colonnes) == m)
                    {

                        resultat += 1; // son nombre de voisin est dans le masque de la Vie, il survit
                    }
                }
                if (resultat != 0)
                {
                    TAB2[i][j] = 1;
                }
            }
            else
            {
                for (m = 0; m < TAILLE_MASQUE; m++)
                {

                    if (masqueMort[m] == 1 && nbvoisinsLimite(TAB1, i, j, nb_lignes, nb_colonnes) == m)
                    {

                        resultat += 1; // son nombre de voisin est dans le masque de la Mort, il ressuscite
                    }
                }
                if (resultat != 0)
                {
                    TAB2[i][j] = 1;
                }
            }
        }
    }
    int **tmp = TAB1;
    TAB1 = TAB2;
    TAB2 = tmp;
}

/*tor*/

int NbVoisinsTor(int **TabT1, int nbLignes, int nbColonnes, int i, int j)
{
    int nbV;

    if (i == 0)
    {
        if (j == 0)
        {
            nbV = TabT1[i + 1][j] + TabT1[i + 1][j + 1] + TabT1[i][j + 1] + TabT1[nbLignes - 1][0] + TabT1[nbLignes - 1][1] + TabT1[nbLignes - 1][nbColonnes - 1] + TabT1[0][nbColonnes - 1] + TabT1[1][nbColonnes - 1];
        }
        else
        {
            if (j == nbColonnes - 1)
            {
                nbV = TabT1[0][j - 1] + TabT1[1][j - 1] + TabT1[1][j] + TabT1[nbLignes - 1][j - 1] + TabT1[nbLignes - 1][j] + TabT1[0][0] + TabT1[1][0] + TabT1[nbLignes - 1][nbColonnes - 1];
            }
            else
            {
                nbV = TabT1[i][j - 1] + TabT1[i][j + 1] + TabT1[i + 1][j - 1] + TabT1[i + 1][j] + TabT1[i + 1][j + 1] + TabT1[nbLignes - 1][j] + TabT1[nbLignes - 1][j - 1] + TabT1[nbLignes - 1][j + 1];
            }
        }
    }
    else
    {
        if (i == nbLignes - 1)
        {
            if (j == 0)
            {
                nbV = TabT1[i - 1][j] + TabT1[i - 1][j + 1] + TabT1[i][j + 1] + TabT1[0][j] + TabT1[0][j + 1] + TabT1[i][nbColonnes - 1] + TabT1[i - 1][nbColonnes - 1] + TabT1[0][nbColonnes - 1];
            }
            else
            {
                if (j == nbColonnes - 1)
                {

                    nbV = TabT1[i][j - 1] + TabT1[i - 1][j - 1] + TabT1[i - 1][j] + TabT1[i - 1][0] + TabT1[i][0] + TabT1[0][j - 1] + TabT1[0][j] + TabT1[0][0];
                }
                else
                {
                    nbV = TabT1[i][j - 1] + TabT1[i][j + 1] + TabT1[i - 1][j - 1] + TabT1[i - 1][j] + TabT1[i - 1][j + 1] + TabT1[0][j - 1] + TabT1[0][j] + TabT1[0][j + 1];
                }
            }
        }
        else
        {
            if (j == 0)
            {
                nbV = TabT1[i][j - 1] + TabT1[i][j + 1] + TabT1[i + 1][j - 1] + TabT1[i + 1][j] + TabT1[i + 1][j + 1] + TabT1[i][nbColonnes - 1] + TabT1[i + 1][nbColonnes - 1] + TabT1[i - 1][nbColonnes - 1];
            }
            else
            {
                if (j == nbColonnes - 1)
                {
                    nbV = TabT1[i][j - 1] + TabT1[i][j + 1] + TabT1[i - 1][j - 1] + TabT1[i - 1][j] + TabT1[i - 1][j + 1] + TabT1[i][0] + TabT1[i + 1][0] + TabT1[i - 1][0];
                }
                else
                {
                    nbV = TabT1[i][j - 1] + TabT1[i][j + 1] + TabT1[i - 1][j - 1] + TabT1[i - 1][j] + TabT1[i - 1][j + 1] + TabT1[i + 1][j - 1] + TabT1[i + 1][j] + TabT1[i - 1][j + 1];
                }
            }
        }
    }
    return nbV;
}

void VieTore(int B[TAILLE_MASQUE], int S[TAILLE_MASQUE], int NbLignes, int NbColonnes)
{
    int i, j, NbV;
    int **TabInt;

    for (i = 0; i < NbLignes; i++)
    {
        for (j = 0; j < NbColonnes; j++)
        {
            NbV = NbVoisinsTor(TAB1, NbLignes, NbColonnes, i, j);
            // printf("%d hhhh\n", NbV);
            if (TAB1[i][j] == 1)
            { // Cas où la cellule est vivante donc masque de mort
                if (NbV == B[NbV])
                {
                    TAB2[i][j] = 0;
                }
            }

            else
            { // Cas où la cellule est morte donc masque de vie
                if (NbV == S[NbV])
                {
                    TAB2[i][j] = 1;
                }
            }
        }
    }
    TabInt = TAB1;
    TAB1 = TAB2;
    TAB1 = TabInt;
}


int TestStagne(int ligne, int colonne){
    int retour = 1;
    for(int i = 0; i < ligne; i++){
        for(int j = 0; j < colonne; j++){
            if(TAB1[i][j] != TAB2[i][j])
                retour = 0;
        }
    }
    return retour;
}