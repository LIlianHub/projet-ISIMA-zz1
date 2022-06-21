#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    /*CRéation Pointeur*/

    SDL_Window *window_1 = NULL;

    /*ALlocation Element*/

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    /* Création de la fenêtre de gauche */

    SDL_DisplayMode infoEcran;
    SDL_GetCurrentDisplayMode(0, &infoEcran)

    int FenetreW = infoEcran.w * 0.7;
    int FenetreH = infoEcran.h * 0.7;


    window_1 = SDL_CreateWindow(
        "Fenêtre à gauche", // codage en utf8, donc accents possibles
        0, 0,               // coin haut gauche en haut gauche de l'écran
        400, 300,           // largeur = 400, hauteur = 300
        0);                 // redimensionnable

    if (window_1 == NULL)
    {
        SDL_Log("Error : SDL window 1 creation - %s\n",
                SDL_GetError()); // échec de la création de la fenêtre
        SDL_Quit();              // On referme la SDL
        exit(EXIT_FAILURE);
    }



    SDL_Delay(2000);


    //Fermeture

    SDL_DestroyWindow(window_1); // la fenêtre 1

    SDL_Quit(); // la SDL

    return 0;
}