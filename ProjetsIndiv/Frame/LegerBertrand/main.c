#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer,
             SDL_Texture *panier,
             SDL_Texture *ciel)
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

  if (panier != NULL)
    {
      SDL_DestroyTexture(panier);
      panier = NULL;
    }

  if (ciel != NULL)
    {
      SDL_DestroyTexture(ciel);
      ciel = NULL;
    }


  SDL_Quit();

  if (!ok)
    { // On quitte si cela ne va pas
      exit(EXIT_FAILURE);
    }
}

// placement panier
void placerText(SDL_Texture *my_texture, SDL_Window *window,
                      SDL_Renderer *renderer)
{
  SDL_Rect
    source = {0},
    window_dimensions = {0},
    destination = {0};

  SDL_GetWindowSize(
		    window, (&window_dimensions.w),
		    (&window_dimensions.h)); // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
		   &source.w, &source.h); // Récupération des dimensions de l'image

  // destination = window_dimensions;  On fixe les dimensions de l'affichage à  celles de la fenêtre

  SDL_RenderCopy(renderer,
		 my_texture,
		 &source,
		 &destination); // Création de l'élément à afficher
}



void Animation(SDL_Window *window,
	       SDL_Renderer *renderer,
	       SDL_Texture *panier,
	       SDL_Texture *ciel)
{

 
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
       

      SDL_RenderClear(renderer);                                // Effacer l'image précédente
      SDL_RenderCopy(renderer, ciel, &source, &destination);    // Préparation de l'affichage
      placerText(panier, window, renderer);                  // Afficher le panier
      SDL_RenderPresent(renderer);                              // Affichage de la nouvelle image
      SDL_Delay(30);

    }
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  SDL_Window *window = NULL;
  SDL_DisplayMode screen;
  SDL_Texture *panier = NULL;
  SDL_Texture *ciel = NULL;
  SDL_Renderer *renderer = NULL;

  /*Allocation sdl*/
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    end_sdl(0, "ERROR SDL INIT", window, renderer, panier, ciel);

  SDL_GetCurrentDisplayMode(0, &screen);
  printf("Résolution écran\n\tw : %d\n\th : %d\n",
	 screen.w, screen.h);

  /* Création de la fenêtre */
  window = SDL_CreateWindow("3 POINTS !!!!!!!",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
			    screen.h * 0.66,
			    SDL_WINDOW_OPENGL);
  if (window == NULL)
    end_sdl(0, "ERROR WINDOW CREATION", window, renderer, panier, ciel);

  /* Création du renderer */

  renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL)
    end_sdl(0, "ERROR RENDERER CREATION", window, renderer, panier, ciel);

  /*Creation image panier*/

  panier = IMG_LoadTexture(renderer, "./img/panier.png");
  if (panier == NULL)
    end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer, panier, ciel);

  /*Creation image ciel*/

  ciel = IMG_LoadTexture(renderer, "./img/ciel.png");
  if (ciel == NULL)
    end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer, panier, ciel);

  /*Affichage*/

  Animation(window, renderer, panier, ciel);

  end_sdl(1, "Normal ending", window, renderer, panier, ciel);
  return EXIT_SUCCESS;
}
