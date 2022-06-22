#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

#include "Config.h"

/*Boucle Principale de Gestion d'événement*/

void GestionEvenement(SDL_Window * window, SDL_Renderer * renderer, TTF_Font * font, int ** position, int ** plateau)
{
    /*Variable utile*/
    SDL_bool activation = SDL_TRUE;
    SDL_Event event;

    while (activation)
    {
        while (SDL_PollEvent(&event)) // on vide la pile d'evenement
        {
            switch (event.type)
            {
            case SDL_QUIT: // ON quitte
                activation = SDL_FALSE;
                break;

            case SDL_KEYDOWN: 
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    enJeu = SDL_TRUE;
                    break;
                case SDLK_LEFT: 
                    break;
                case SDLK_RIGHT: 
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN: // Click souris
                if (SDL_GetMouseState(NULL, NULL) &
                    SDL_BUTTON(SDL_BUTTON_LEFT))
                { // clique droit
                }
                break;
            default: // poubelle à événement
                break;
            }
        }
        //fonction
        SDL_RenderPresent(renderer);
        SDL_Delay(50); // depend pour fps avec horloge
    }

    return 0;
}

/*LIbération Propre de la SDL*/

void end_sdl(char ok,
             char const *msg,
             SDL_Window *window,
             SDL_Renderer *renderer,
             TTF_Font *font)
{
    char msg_formated[255];
    int l;

    if (!ok)
    { // Affichage de ce qui ne va pas
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    if (font != NULL)
    {
        TTF_CloseFont(font);
        font = NULL;
    }

    TTF_Quit();
    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

/*void ChangeEtat(int **tab, int FenetreW, int FenetreH, int x, int y, int nbLigne, int nbColonne, SDL_bool enJeu)
{
    if (x > 0 && x < FenetreW && y > 25 && y < FenetreH)
    {

        int colonneTab = x / (FenetreW / nbColonne);
        int ligneTab = (y - 25) / (FenetreH / nbLigne);
        if (!enJeu)
        {
            if (tab[ligneTab][colonneTab] == 1)
                tab[ligneTab][colonneTab] = 0;
            else
                tab[ligneTab][colonneTab] = 1;
        }
    }
}*/
