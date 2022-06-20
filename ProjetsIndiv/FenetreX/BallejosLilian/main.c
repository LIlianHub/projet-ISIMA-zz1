#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define TAILLE_FENETRE 25

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

  /*Taille ecran*/

  SDL_DisplayMode current;
  SDL_GetCurrentDisplayMode(0, &current);
  int width = current.w;
  int height = current.h;
  printf("%d %d\n", width, height);
  int milieu = height / 2 - TAILLE_FENETRE;
  int nbr_element = width / TAILLE_FENETRE;

  /*Fenetre*/

  SDL_Window *tabWindow[nbr_element];
  for (int i = 0; i < nbr_element; i++)
  {
    tabWindow[i] = SDL_CreateWindow(
        "Fenetre",                  // codage en utf8, donc accents possibles
        i * TAILLE_FENETRE, milieu, // coin haut gauche en haut gauche de l'écran
        TAILLE_FENETRE, TAILLE_FENETRE,
        0); // redimensionnable

    if (tabWindow[i] == NULL)
    {
      SDL_Log("Error : SDL window %d creation - %s\n",
              i, SDL_GetError()); // échec de la création de la fenêtre
      SDL_Quit();                 // On referme la SDL
      exit(EXIT_FAILURE);
    }
  }

  /*ANimation 1*/

  for (int i = 0; i < nbr_element; i++)
  {
    float val_cos = cosf((i) * TAILLE_FENETRE);
    SDL_SetWindowPosition(tabWindow[i], i * TAILLE_FENETRE, val_cos * val_cos * height);
    SDL_Delay(100);
  }

  /*Animation 2*/
  int variante = 0;
  while (variante < 100)
  {
    for (int i = 0; i < nbr_element; i++)
    {
      float val_cos = cosf((i + variante) * TAILLE_FENETRE);
      SDL_SetWindowPosition(tabWindow[i], i * TAILLE_FENETRE, val_cos * val_cos * height);
    }
    variante++;
    printf("iteration n°%d\n", variante);
    SDL_Delay(100);
  }

  /*ANimation 3*/

  for (int i = nbr_element - 1; i >= 0; i--)
  {
    SDL_SetWindowPosition(tabWindow[i], i * TAILLE_FENETRE, milieu);
    SDL_Delay(100);
  }


  for (int i = 0; i < nbr_element; i++)
  {
    SDL_DestroyWindow(tabWindow[i]);
    printf("clear fenetre %d\n",i);
  }

  SDL_Quit(); // la SDL

  return 0;
}