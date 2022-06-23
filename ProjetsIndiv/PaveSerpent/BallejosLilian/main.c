#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/*Modifiable pour plus de rectangle ou des formes plus grosses*/
#define NBR_RECTANGLE 100
#define TAILLE_RECT 10

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
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

    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

/*Fonction de dessin*/
void draw(SDL_Renderer *renderer, int largeur, int hauteur)
{
    /*Tableau de rectangle*/
    SDL_Rect *rectangles = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NBR_RECTANGLE);
    SDL_Rect *rectangles2 = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NBR_RECTANGLE);
    int cercleTailleX = 100;
    int cercleTailleY = 200; /*taille des cercles pas la même pour avoir alternance ellispse et cercle*/
    int couleurR = 0;
    int couleurG = 20; /*couleur varie*/
    int couleurB = 10;

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
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);                // fond blanc
        SDL_RenderClear(renderer);                                           // efface le rendu précédent
        SDL_SetRenderDrawColor(renderer, couleurR, couleurG, couleurB, 255); // couleur rectangle
        for (int i = 0; i < NBR_RECTANGLE; i++)
        {
            float valCos = cosf(i);
            float valSin = sinf(i);
            rectangles[i].x = cercleTailleX * valCos + largeur / 2;
            rectangles[i].y = cercleTailleY * valSin + hauteur / 2;
            rectangles[i].w = TAILLE_RECT;
            rectangles[i].h = TAILLE_RECT;
            SDL_RenderFillRect(renderer, &rectangles[i]); // on applique le rectangle
        }
        for (int i = 0; i < NBR_RECTANGLE; i++)
        {
            float valCos = cosf(i);
            float valSin = sinf(i); /*on inverse les largeur x et y avec le premier pour avoir une belle forme*/
            rectangles[i].x = cercleTailleY * valCos + largeur / 2;
            rectangles[i].y = cercleTailleX * valSin + hauteur / 2;
            rectangles[i].w = TAILLE_RECT;
            rectangles[i].h = TAILLE_RECT;
            SDL_RenderFillRect(renderer, &rectangles[i]); // on applique le rectangle
        }

        cercleTailleX = (cercleTailleX + 10) % 300;
        cercleTailleY = (cercleTailleY + 10) % 400;
        couleurR = (couleurR + 5) % 200;
        couleurG = (couleurG + 5) % 200; // modulo 200 pour eviter le blanc en 255
        couleurB = (couleurB + 5) % 200;
        SDL_RenderPresent(renderer); // on charge le rendu
        SDL_Delay(75);
    }
    free(rectangles);
    free(rectangles2);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;

    /*Allocation SDL*/

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
                              screen.h * 0.66,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /*Appel de la fonction de dessin*/
    draw(renderer, screen.w * 0.66, screen.h * 0.66);

    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}