#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window *GenereTabWindow(int nb)
{
  SDL_Window *tabWindow = (SDL_Window *)malloc(nb * sizeof(SDL_Window));
  int espace = 100;
  for (int i = 0; i < nb; i++)
  {
    tabWindow[i] = SDL_CreateWindow(
        "Fenetre",             // codage en utf8, donc accents possibles
        0 + i * espace, 0,     // coin haut gauche en haut gauche de l'écran
        espace, espace,        // largeur = 400, hauteur = 300
        SDL_WINDOW_RESIZABLE); // redimensionnable

    if (tabWindow[i] == NULL)
    {
      SDL_Log("Error : SDL window 1 creation - %s\n",
              SDL_GetError()); // échec de la création de la fenêtre
      SDL_Quit();              // On referme la SDL
      exit(EXIT_FAILURE);
    }
  }
}

void clearFenetre(SDL_Window *tab, int nb)
{
  for (int i = 0; i < nb; i++)
  {
    SDL_DestroyWindow(tab[i]);
  }
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    SDL_Log("Error : SDL initialisation - %s\n",
            SDL_GetError()); // l'initialisation de la SDL a échoué
    exit(EXIT_FAILURE);
  }

  SDL_Window *tab = NULL;
  int nb = 5;
  tab = GenereTabWindow(nb);

  SDL_Delay(300000); // Pause exprimée  en ms

  clearFenetre(tab, nb);

  SDL_Quit(); // la SDL

  return 0;
}