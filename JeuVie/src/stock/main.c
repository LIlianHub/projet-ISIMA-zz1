#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;


    SDL_bool
        program_on = SDL_TRUE, // Booléen pour dire que le programme doit continuer
        paused = SDL_FALSE;    // Booléen pour dire que le programme est en pause
    SDL_Event event;           // Evènement à traiter

    while (program_on)
    { // La boucle des évènements
        if (SDL_PollEvent(&event))
        { // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
          // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la // fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYDOWN: // Le type de event est : une touche appuyée
                              // comme la valeur du type est SDL_Keydown, dans la partie 'union' de
                              // l'event, plusieurs champs deviennent pertinents
                switch (event.key.keysym.sym)
                {                     // la touche appuyée est ...
                case SDLK_p:          // 'p'
                case SDLK_SPACE:      // ou 'SPC'
                    paused = !paused; // basculement pause/unpause
                    break;
                case SDLK_ESCAPE:   // 'ESCAPE'
                case SDLK_q:        // ou 'q'
                    program_on = 0; // 'escape' ou 'q', d'autres façons de quitter le programme
                    break;
                default: // Une touche appuyée qu'on ne traite pas
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN: // Click souris
                if (SDL_GetMouseState(NULL, NULL) &
                    SDL_BUTTON(SDL_BUTTON_LEFT))
                {                                   // Si c'est un click gauche
                    change_state(state, 1, window); // Fonction à éxécuter lors d'un click gauche
                }
                else if (SDL_GetMouseState(NULL, NULL) &
                         SDL_BUTTON(SDL_BUTTON_RIGHT))
                {                                   // Si c'est un click droit
                    change_state(state, 2, window); // Fonction à éxécuter lors d'un click droit
                }
                break;
            default: // Les évènements qu'on n'a pas envisagé
                break;
            }
        }
        draw(state, &color, renderer, window); // On redessine
        if (!paused)
        {                                     // Si on n'est pas en pause
            next_state(state, survive, born); // la vie continue...
        }
        SDL_Delay(50); // Petite pause
    }
}