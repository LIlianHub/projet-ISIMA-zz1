#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <string.h>

#include "Config.h"
#include "Graphique.h"
#include "Algorithme.h"
#include "QTable.h"

/*PARTIE MAIN*/
/* Uniquement les libérations et allocations de structures*/

int main(int argc, char **argv)
{
    // commun au mode graphique et apprentissage

    /*random*/
    srand(time(NULL));

    /* PARTIE ALLOCATION*/

    // Allocation des Tableaux
    int **position_snake = NULL;
    int **plateau = NULL;

    plateau = creer_tableau(DIMENSION_TAB_JEU, DIMENSION_TAB_JEU);
    position_snake = creer_tableau(DIMENSION_TAB_POS, 2);

    // mode apprentissage
    if (argc == 3 && !strcmp(argv[1], "apprend"))
    {
        printf("Mode Apprentissage\n");
        //init liste etat possible apprentissage
        int nbIteration;
        sscanf(argv[2],"%d",&nbIteration);
        MainApprentissage(nbIteration, position_snake, plateau);
    }

    // mode graphique
    else
    {
        // Création Pointeur

        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
        TTF_Font *policeTitre = NULL;
        SDL_Texture *logoMenu = NULL;
        SDL_Texture *pomme = NULL;
        SDL_Texture *explosion = NULL;
        SDL_Texture *table_serpent = NULL;
        SDL_Texture *menu = NULL;

        // Initialisation de la SDL  + gestion de l'échec possible
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            SDL_Log("Error : SDL initialisation - %s\n",
                    SDL_GetError()); // l'initialisation de la SDL a échoué
            exit(EXIT_FAILURE);
        }

        // Création de la fenêtre de gauche
        window = SDL_CreateWindow("Serpent",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  FENETREWIDTH,
                                  FENETREHEIGHT,
                                  SDL_WINDOW_OPENGL);

        if (window == NULL)
            end_sdl(0, "ERROR WINDOW CREATION", window, renderer, policeTitre, logoMenu, pomme, explosion, table_serpent, menu);

        // Création du renderer
        renderer = SDL_CreateRenderer(window, -1,
                                      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL)
            end_sdl(0, "ERROR RENDERER CREATION", window, renderer, policeTitre, logoMenu, pomme, explosion, table_serpent, menu);

        // Le render mode couleur alpha pour la transparence
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        // Création police
        if (TTF_Init() < 0)
            end_sdl(0, "Couldn't initialize SDL TTF", window, renderer, policeTitre, logoMenu, pomme, explosion, table_serpent, menu);
        policeTitre = TTF_OpenFont("fonts/arial.ttf", TAILLE_MENU);

        // Image

        logoMenu = IMG_LoadTexture(renderer, "./img/logo.png");
        if (logoMenu == NULL)
            end_sdl(0, "Erreur chargement logo", window, renderer, policeTitre, logoMenu, pomme, explosion, table_serpent, menu);

        pomme = IMG_LoadTexture(renderer, "./img/pomme.png");
        if (pomme == NULL)
            end_sdl(0, "Erreur chargement pomme", window, renderer, policeTitre, logoMenu, pomme, explosion, table_serpent, menu);

        explosion = IMG_LoadTexture(renderer, "./img/explosion.png");
        if (pomme == NULL)
            end_sdl(0, "Erreur chargement explosion", window, renderer, policeTitre, logoMenu, pomme, explosion, table_serpent, menu);

        table_serpent = IMG_LoadTexture(renderer, "./img/serpent.png");
        if (pomme == NULL)
            end_sdl(0, "Erreur chargement serpent", window, renderer, policeTitre, logoMenu, pomme, explosion, table_serpent, menu);

        menu = IMG_LoadTexture(renderer, "./img/menu.png");
        if (menu == NULL)
            end_sdl(0, "Erreur chargement menu", window, renderer, policeTitre, logoMenu, pomme, explosion, table_serpent, menu);

        /* Mode couleur pour transparence*/
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        /*Recupération meilleur score*/
        int meilleurScore = MeilleurScore(0);

        /*Appel de la fonction qui gère les événments*/

        GestionEvenement(renderer, policeTitre, position_snake, plateau, meilleurScore, logoMenu, pomme, explosion, table_serpent, menu);

        // LIbération SDL
        end_sdl(1, "Normal ending", window, renderer, policeTitre, logoMenu, pomme, explosion, table_serpent, menu);
        return EXIT_SUCCESS;
    }

    /* LIBERATION*/

    // Liberation des tableaux
    liberer_tableau(plateau, DIMENSION_TAB_JEU);
    liberer_tableau(position_snake, DIMENSION_TAB_POS);
}