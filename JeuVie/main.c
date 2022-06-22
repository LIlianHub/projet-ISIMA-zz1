#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "Animation.h"
#include "Algorithme.h"

/************************************/
/*  exemple de création de fenêtres */
/************************************/

#define NB_LIGNE 25
#define NB_COLONNE 25


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

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
    int FenetreW = 800;
    int FenetreH = 825;

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

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // le render mode couleur alpha

    /*Création de la police*/

    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer, policeTitre);
    policeTitre = TTF_OpenFont("fonts/arial.ttf", 20);

    /* partie jeu de la vie*/

    int masqueVie[TAILLE_MASQUE] = {0, 0, 1, 1, 0, 0, 0, 0, 0};
    int masqueMort[TAILLE_MASQUE] = {0, 0, 0, 1, 0, 0, 0, 0, 0};
    TAB1 = creer_tableau(NB_LIGNE, NB_COLONNE);
    TAB2 = creer_tableau(NB_LIGNE, NB_COLONNE);
    TAB1[12][12] = 1;

    /*Gestion Vitesse*/

    int GestionVitesse = 50;
    int stagne = 0;
    

    /*Evenement*/

    SDL_bool
        program_on = SDL_TRUE,
        modeJeu = SDL_FALSE, // FALSE : LIMITE true tor
        enJeu = SDL_FALSE;
    SDL_Event event;

    while (program_on)
    {
        while (SDL_PollEvent(&event)) // partie event
        {
            switch (event.type)
            {              // En fonction de la valeur du type de cet évènement
            case SDL_QUIT: // ON quitte
                program_on = SDL_FALSE;
                break;
            case SDL_KEYDOWN: // Appuie touche
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    enJeu = SDL_TRUE;
                    printf("suuh\n");
                    break;
                case SDLK_c: // changement mode
                    modeJeu = !modeJeu;
                    break;
                case SDLK_w: // save config
                    if (!enJeu)
                    {
                        EcritureConfig(TAB1, NB_LIGNE, NB_COLONNE);
                    }
                    break;
                case SDLK_v: // clear
                    if (!enJeu)
                    {
                        ClearTab(TAB1, NB_LIGNE, NB_COLONNE);
                    }
                    break;
                case SDLK_x: // lecture save
                    if (!enJeu)
                    {
                        LectureFichier(TAB1, NB_LIGNE, NB_COLONNE);
                    }
                    break;
                case SDLK_LEFT: // ralentissement
                    if (enJeu)
                    {
                        GestionVitesse += 0.1 * GestionVitesse;
                    }
                    break;
                case SDLK_RIGHT: // ACCELERATION
                    if (enJeu)
                    {
                        GestionVitesse -= 0.1 * GestionVitesse;
                    }
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN: // Click souris
                if (SDL_GetMouseState(NULL, NULL) &
                    SDL_BUTTON(SDL_BUTTON_LEFT))
                { // clique droit
                    if (!enJeu)
                        ChangeEtat(TAB1, FenetreW, FenetreH, event.motion.x, event.motion.y, NB_LIGNE, NB_COLONNE, enJeu);
                }
                break;
            default: // Les évènements qu'on n'a pas envisagé
                break;
            }
        }
        // fonction
        enJeu = SDL_TRUE;
        modeJeu = SDL_TRUE;
        if (enJeu)
        {
            if (!modeJeu)
            {
                iterationReelLimite(NB_LIGNE, NB_COLONNE, masqueVie, masqueMort);
            }
            else
            {
                VieTore(masqueMort, masqueVie, NB_LIGNE, NB_COLONNE);
            }
        }

        if(!stagne){
            stagne = TestStagne(NB_LIGNE, NB_COLONNE);
            
        }

        printf("stagne = %d\n", stagne);
        Affichage(window,renderer,FenetreW, FenetreH, policeTitre, masqueVie, masqueMort, modeJeu, TAB1, NB_LIGNE, NB_COLONNE, stagne);
        SDL_RenderPresent(renderer);
        SDL_Delay(GestionVitesse); // depend pour fps avec horloge
    }

    // Fermeture
    liberer_tableau(TAB1, NB_LIGNE);
    liberer_tableau(TAB2, NB_LIGNE);
    end_sdl(1, "Normal ending", window, renderer, policeTitre);
    return EXIT_SUCCESS;

    return 0;
}