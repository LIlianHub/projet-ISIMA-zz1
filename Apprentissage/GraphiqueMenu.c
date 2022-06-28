#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Config.h"
#include "Graphique.h"

/*Iter menu*/

void IterMenu(SDL_Renderer *renderer, SDL_Texture *menu)
{
    SDL_Rect posMenu = {0, 0, FENETREWIDTH, FENETREHEIGHT};
    SDL_RenderCopy(renderer, menu, NULL, &posMenu);
}

int DetectBoutonMenu(float x, float y)
{
    float echelleW = ((float)FENETREWIDTH / 800);
    float echelleH = ((float)FENETREHEIGHT / 860) / 800;
    int retour = 0;
    if (x >= 60 * echelleW && x <= 360 * echelleW && y >= 470 * echelleH && y <= 620 * echelleH)
    {
        retour = 1;
    }

    if (x >= FENETREWIDTH - 360 * echelleW && x <= FENETREWIDTH - (60 * echelleW) && y >= 470 * echelleH && y <= 620 * echelleH)
    {
        retour = 2;
    }

    return retour;
}

void OverBoutonMenu(SDL_Renderer *renderer, float x, float y)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
    int info = DetectBoutonMenu(x, y);
    if (info == 1)
    {
        SDL_Rect posMenu = {60, 470, 300, 150};
        SDL_RenderFillRect(renderer, &posMenu);
    }

    if (info == 2)
    {
        SDL_Rect posMenu2 = {FENETREWIDTH - (60 + 300), 470, 300, 150};
        SDL_RenderFillRect(renderer, &posMenu2);
    }
}

void ChoixMenu(float x, float y, SDL_bool *dansJeu, SDL_bool *dansMenu, SDL_bool *enJeu, SDL_bool *depart, int *iter_explo, int **serpent, int **plateau, int *taille_serpent,
               int *direction, int *infoIter, int *etat_markov, int *vitesse_markov, int *score, int *multiplicateur, long *lastTick, int *teteSerpent, int *nbItePosMur)
{
    int info = DetectBoutonMenu(x, y);
    if (info == 1)
    {
        Initialisation(enJeu, depart, iter_explo, serpent, plateau, taille_serpent, direction, infoIter, etat_markov, vitesse_markov, score,
                       multiplicateur, lastTick, teteSerpent, nbItePosMur, dansJeu, dansMenu);
        *dansJeu = SDL_TRUE;
        *dansMenu = SDL_FALSE;
    }

    if (info == 2)
    {
        printf("AI\n");
    }
}