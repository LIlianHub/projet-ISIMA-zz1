#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MASQUE 3

/*Création tableau*/

int ** creer_tableau(int nb_lignes, int nb_colonnes)
{
    int ** tableau = (int**)malloc(nb_lignes * sizeof(int *));
    int i;
    for (i = 0; i < nb_lignes; i++)
    {
        tableau[i] = (int *)calloc(nb_colonnes, sizeof(int));
    }
    return tableau;
}

/*LIberation tableau*/

void liberer_tableau(int ** tableau, int nb_lignes)
{
    int i;
    for (i = 0; i < nb_lignes; i++)
    {
        free(tableau[i]);
    }
    free(tableau);
}



void afficher_tableau(int ** tableau, int nb_lignes, int nb_colonnes)
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
}



int main(){
    int masqueVie[TAILLE_MASQUE][TAILLE_MASQUE] = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}
    };

    int masqueMort[TAILLE_MASQUE][TAILLE_MASQUE] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };

    int nb_lignes = 50;
    int nb_colonnes = 80;

    int ** tableau = creer_tableau(nb_lignes, nb_colonnes);

    afficher_tableau(tableau, nb_lignes, nb_colonnes);
    liberer_tableau(tableau, nb_lignes);
    return 1;
}




