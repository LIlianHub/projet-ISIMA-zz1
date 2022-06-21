#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
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

    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    /*CRéation Pointeur*/

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

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
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /*Evenement*/

    int ChoixMenu = 0; // Menu

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
        SDL_Delay(10); // depend pour fps avec horloge
    }

    // Fermeture

    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;

    return 0;
}