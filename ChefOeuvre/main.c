#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

#include "Config.h"
#include "Graphique.h"


/*PARTIE MAIN*/
/* Uniquement les libérations et allocations de structures*/

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    /* PARTIE ALLOCATION*/

    //Création Pointeur

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *policeTitre = NULL;


    //Initialisation de la SDL  + gestion de l'échec possible
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    //Création de la fenêtre de gauche
    window = SDL_CreateWindow("Jeu de la Vie",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              FENETREWIDTH,
                              FENETREHEIGHT,
                              SDL_WINDOW_OPENGL);

    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer, policeTitre);

    //Création du renderer
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer, policeTitre);

    //Le render mode couleur alpha pour la transparence
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    //Création police
    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer, policeTitre);
    policeTitre = TTF_OpenFont("fonts/arial.ttf", 20);

    //Allocation des Tableaux

    int ** position = NULL;
    int ** plateau = NULL;


    /*Appel de la fonction qui gère les événments*/

    GestionEvenement(window, renderer, policeTitre, &position, &plateau);


    /* LIBERATION*/

    //Liberation des tableaux

    //LIbération SDL
    end_sdl(1, "Normal ending", window, renderer, policeTitre);
    return EXIT_SUCCESS;
}