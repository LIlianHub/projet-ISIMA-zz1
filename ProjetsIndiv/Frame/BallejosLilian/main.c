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
             SDL_Texture *oiseau)
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

    if (sol != NULL)
    {
        SDL_DestroyTexture(sol);
        sol = NULL;
    }

    if (ciel != NULL)
    {
        SDL_DestroyTexture(ciel);
        ciel = NULL;
    }

    if (oiseau != NULL)
    {
        SDL_DestroyTexture(oiseau);
        oiseau = NULL;
    }

    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

// placement fond
void placementTexture(SDL_Texture *my_texture, SDL_Window *window,
                      SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},
        window_dimensions = {0},
        destination = {0};

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
}

void anim(SDL_Texture *ciel,
          SDL_Window *window,
          SDL_Renderer *renderer,
          SDL_Texture *sol,
          SDL_Texture *oiseau)
{

    /* perso*/
    SDL_Rect
        source2 = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions2 = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination2 = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state2 = {0};             // Rectangle de la vignette en cours dans la planche

    SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                      &window_dimensions2.w,
                      &window_dimensions2.h);

    SDL_QueryTexture(oiseau, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &source2.w, &source2.h);

    printf("dim image %d %d\n", source2.w, source2.h);

    int nb_images = 5;
    int offset_x = source2.w / nb_images, // 5 frame par ligne
        offset_y = source2.h / 3;         // 3 lignes

    state2.x = 0;
    state2.y = 0; // premiere ligne
    state2.w = offset_x;
    state2.h = offset_y;

    printf("offeset %d %d\n", offset_x, offset_y);

    destination2.w = offset_x;
    destination2.h = offset_y;
    destination2.y = (window_dimensions2.h / 2) - destination2.h; // La course se fait en milieu d'écran (en vertical)

    printf("destination H et W %d %d\n", destination2.w, destination2.h);

    /* fond */
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre

    SDL_QueryTexture(ciel, NULL, NULL,
                     &source.w,
                     &source.h); // Récupération des dimensions de l'image

    float zoom = 1.5;                // Facteur de zoom entre l'image source et l'image affichée pour fond
    destination.w = source.w * zoom; // On applique le zoom sur la largeur
    destination.h = source.h * zoom; // On applique le zoom sur la hauteur
    destination.x = -source.w / 2;   // au depart a droite

<<<<<<< HEAD
    int speed = 12; // vitesse de déplacement
    int x = 0;      // depart oiseau
=======
    int speed = 10; // vitesse de déplacement
    int x = 0; //depart oiseau
>>>>>>> partie_graphique
    SDL_bool program_on = SDL_TRUE;
    SDL_Event event;

    while (program_on)
    {

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                program_on = SDL_FALSE;
                break;

            default:
                break;
            }
        }
        /*animation*/
        x += speed;
<<<<<<< HEAD
        if (destination.x > 0) // on atteind le bout de l'image le fond retourne a sa place
=======
        if (destination.x > 0) // on atteind le bout de l'image
>>>>>>> partie_graphique
        {
            destination.x = -source.w / 2;
        }
        else
        {
            destination.x += 10;
        }
        destination2.x = x;
        state2.x += offset_x;  // On passe à la vignette suivante dans l'image
        state2.x %= source2.w; // On réinitialise à 0 si on dépasse la largeur

        printf("etat %d %d\n", state2.x, state2.y);
        printf("destination %d %d\n", destination2.x, destination2.y);

        SDL_RenderClear(renderer);                                // Effacer l'image précédente
        SDL_RenderCopy(renderer, ciel, &source, &destination);    // Préparation de l'affichage
        placementTexture(sol, window, renderer);                  // Afficher le sol
        SDL_RenderCopy(renderer, oiseau, &state2, &destination2); // personnage
        SDL_RenderPresent(renderer);                              // Affichage de la nouvelle image
        SDL_Delay(30);
<<<<<<< HEAD
        if (x > window_dimensions.w)
=======
        if(x > window_dimensions.w)
>>>>>>> partie_graphique
            program_on = !program_on;
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
    SDL_Texture *oiseau = NULL;
    SDL_Renderer *renderer = NULL;

    /*Allocation sdl*/
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer, sol, ciel, oiseau);

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
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer, sol, ciel, oiseau);

    /* Création du renderer */

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer, sol, ciel, oiseau);

    /*Creation image sol*/

    sol = IMG_LoadTexture(renderer, "./img/terrain.png");
    if (sol == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer, sol, ciel, oiseau);

    /*Creation image ciel*/

    ciel = IMG_LoadTexture(renderer, "./img/ciel.png");
    if (ciel == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer, sol, ciel, oiseau);

    /*Creation image oiseau*/

    oiseau = IMG_LoadTexture(renderer, "./img/oiseau.png");
    if (oiseau == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer, sol, ciel, oiseau);

    /*Affichage*/

    anim(ciel, window, renderer, sol, oiseau);

    end_sdl(1, "Normal ending", window, renderer, sol, ciel, oiseau);
    return EXIT_SUCCESS;
}