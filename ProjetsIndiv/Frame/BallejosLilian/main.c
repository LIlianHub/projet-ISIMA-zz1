#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer,
             SDL_Texture *sol,
             SDL_Texture *ciel,
             SDL_Texture *mario)
{ // renderer à fermer
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
    {                                  // Destruction si nécessaire du renderer
        SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
    }
    if (window != NULL)
    {                              // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
        window = NULL;
    }

    if (sol != NULL)
    {                            // Destruction si nécessaire de la fenêtre
        SDL_DestroyTexture(sol); // Attention : on suppose que les NULL sont maintenus !!
        sol = NULL;
    }

    if (ciel != NULL)
    {                             // Destruction si nécessaire de la fenêtre
        SDL_DestroyTexture(ciel); // Attention : on suppose que les NULL sont maintenus !!
        ciel = NULL;
    }

    if (mario != NULL)
    {                              // Destruction si nécessaire de la fenêtre
        SDL_DestroyTexture(mario); // Attention : on suppose que les NULL sont maintenus !!
        mario = NULL;
    }

    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

void placementTexture(SDL_Texture *my_texture, SDL_Window *window,
                      SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture,
                   &source,
                   &destination); // Création de l'élément à afficher
    SDL_RenderPresent(renderer);  // Affichage
}

void anim(SDL_Texture *my_texture,
          SDL_Window *window,
          SDL_Renderer *renderer,
          SDL_Texture *sol,
          SDL_Texture *mario)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_Rect
        source2 = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions2 = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination2 = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state2 = {0};             // Rectangle de la vignette en cours dans la planche

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre

    SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                      &window_dimensions2.w,
                      &window_dimensions2.h);

    SDL_QueryTexture(my_texture, NULL, NULL,
                     &source.w,
                     &source.h); // Récupération des dimensions de l'image

    SDL_QueryTexture(mario, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &source2.w, &source2.h);

    int nb_images = 3;                        // Il y a 3 vignette dans la ligne de l'image qui nous intéresse
    int offset_x = source2.w / 6,             // 6 frame par ligne
        offset_y = source2.h / 4 + source2.h; // on se place sur la deuxieme ligne de l'image

    /* fond */
    float zoom = 1.5;                // Facteur de zoom entre l'image source et l'image affichée pour fond
    destination.w = source.w * zoom; // On applique le zoom sur la largeur
    destination.h = source.h * zoom; // On applique le zoom sur la hauteur
    destination.x = -source.w / 2;   // au depart a droite

    /*sprite mario*/

    float zoom2 = 2;                   // zoom, car ces images sont un peu petites
    destination2.w = offset_x * zoom2; // Largeur du sprite à l'écran
    destination2.h = offset_y * zoom2; // Hauteur du sprite à l'écran
    destination2.y =                   // La course se fait en milieu d'écran (en vertical)
        (window_dimensions.h - destination2.h) / 2;
    destination2.x = 100;

    /*animation*/
    int nb_it = 300; // Nombre d'iteration

    for (int i = 0; i < nb_it; ++i)
    {
        if (destination.x > 0) // on atteind le bout de l'image
        {
            destination.x = -source.w / 2;
        }
        else
        {
            destination.x += 10;
        }
        destination2.x += offset_x;
        state2.x += offset_x;                    // On passe à la vignette suivante dans l'image
        state2.x %= (source2.w / 6) * nb_images; // La vignette suivante sur 3 cases

        SDL_RenderClear(renderer);                                   // Effacer l'image précédente
        SDL_RenderCopy(renderer, my_texture, &source, &destination); // Préparation de l'affichage
        placementTexture(sol, window, renderer);                     // Afficher le sol
        SDL_RenderCopy(renderer, mario, &state2, &destination2);      // mario
        SDL_RenderPresent(renderer);                                 // Affichage de la nouvelle image
        SDL_Delay(30);                                               // Pause en ms
    }
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    SDL_Window *window = NULL;
    SDL_DisplayMode screen;
    SDL_Texture *sol = NULL;
    SDL_Texture *ciel = NULL;
    SDL_Texture *mario = NULL;
    SDL_Renderer *renderer = NULL;

    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer, sol, ciel, mario);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
           screen.w, screen.h);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
                              screen.h * 0.66,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer, sol, ciel, mario);

    /* Création du renderer */

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer, sol, ciel, mario);

    /*Creation image sol*/

    sol = IMG_LoadTexture(renderer, "./img/terrain.png");
    if (sol == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer, sol, ciel, mario);

    /*Creation image ciel*/

    ciel = IMG_LoadTexture(renderer, "./img/ciel.png");
    if (ciel == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer, sol, ciel, mario);

    /*Creation image mario*/

    mario = IMG_LoadTexture(renderer, "./img/frame-mario.png");
    if (mario == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer, sol, ciel, mario);

    /*Affichage*/

    anim(ciel, window, renderer, sol, mario);
    SDL_Delay(2000);

    SDL_RenderClear(renderer); // Effacer la fenêtre

    SDL_Delay(2000);

    /* on referme proprement la SDL */

    end_sdl(1, "Normal ending", window, renderer, sol, ciel, mario);
    return EXIT_SUCCESS;
}