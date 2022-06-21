#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "animation.h"

/************************************/
/*  exemple de création de fenêtres */
/************************************/

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    /*A suppimer*/

    int **tab = malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; i++)
    {
        tab[i] = calloc(10, sizeof(int));
    }

    tab[5][5] = 1;

    /*Création Pointeur*/

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *policeTitre = NULL;

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
    SDL_GetCurrentDisplayMode(0, &infoEcran);
    int FenetreW = infoEcran.w * 0.7;
    int FenetreH = infoEcran.h * 0.7;

    window = SDL_CreateWindow("Jeu de la Vie",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              FenetreW,
                              FenetreH,
                              SDL_WINDOW_OPENGL);

    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer, policeTitre);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer, policeTitre);

    /*Création de la police*/

    
    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer, policeTitre);
    policeTitre = TTF_OpenFont("fonts/arial.ttf", FenetreW/20); //police responsive

    /*Evenement*/

    int ChoixMenu = 0;

    SDL_bool
        program_on = SDL_TRUE, // Booléen pour dire que le programme doit continuer
        paused = SDL_FALSE;    // Booléen pour dire que le programme est en pause
    SDL_Event event;           // Evènement à traiter

    while (program_on)
    {
        if (SDL_PollEvent(&event)) // partie event
        {
            switch (event.type)
            {              // En fonction de la valeur du type de cet évènement
            case SDL_QUIT: // ON quitte
                program_on = SDL_FALSE;
                break;
            case SDL_KEYDOWN: // Appuie touche
                switch (event.key.keysym.sym)
                {                     // la touche appuyée est ...
                case SDLK_p:          // 'p'
                case SDLK_SPACE:      // ou 'SPC'
                    paused = !paused; // basculement pause/unpause
                    break;
                default: // Une touche appuyée qu'on ne traite pas
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN: // Click souris
                if (SDL_GetMouseState(NULL, NULL) &
                    SDL_BUTTON(SDL_BUTTON_LEFT))
                { // Si c'est un click gauche
                    printf("clique gauche\n");
                }
                else if (SDL_GetMouseState(NULL, NULL) &
                         SDL_BUTTON(SDL_BUTTON_RIGHT))
                { // Si c'est un click droit
                    printf("clique droit\n");
                }
                break;
            default: // Les évènements qu'on n'a pas envisagé
                break;
            }
        }

        // fonction
        GenereMenu(window, renderer, FenetreW, FenetreH, policeTitre);
        SDL_RenderPresent(renderer);
        SDL_Delay(10); // depend pour fps avec horloge
    }

    // Fermeture

    end_sdl(1, "Normal ending", window, renderer, policeTitre);
    return EXIT_SUCCESS;

    return 0;
}