#include <stdlib.h>
#include <stdio.h>

#define TAILLE_TABLEAU 10

SDL_bool
  program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
  paused = SDL_FALSE;                             // Booléen pour dire que le programme est en pause
SDL_Event event;

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

/* Création du serpent au milieu du cadre */

void InitialisationSerpent(int ** tableau, int taille){  
    int i = taille/2,j;

    for(j = taille/2 - 2; j<3; j++){
        tableau[i][j] = 1;
    }
    tableau[i][3]=2;

}

/* Création des probabilités de changement de place de la pomme */

void MarkovPomme(int ** probapomme){
    int a,b,c,d,e,f,g,h,i;
    int j,k;

    //remplir le tableau avec les probabilités

}


int main(){

    int ** cadre = creer_tableau(TAILLE_TABLEAU, TAILLE_TABLEAU);
    int ** probapomme = creer_tableau(4,4);
    int tailleserpent = 4
    MarkovPomme(probapomme);
    InitialisationSerpent(cadre, TAILLE_TABLEAU);

    while(program_on){
        if(SDL_PollEvent(&event)) {   // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas terminé le programme Défiler l'élément en tête de file dans 'event'
            switch(event.type){
                case SDLK_UP:         //Cas flèche du haut


                case SDLK_DOWN:         //Cas flèche du bas

                case SDLK_RIGHT:        //Cas flèche droite

                case SDLK_LEFT:         //Cas flèche gauche

                

            }

    }




    return 0;
}