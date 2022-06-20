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
  //printf("%d %d\n", width, height);
  int milieu = height / 2 - TAILLE_FENETRE; // milieu ecran axe y
  int nbr_element = width / TAILLE_FENETRE; // nb d'element a generer

  /*PLacement et creation fenetre*/

  SDL_Window **tabWindow;
  tabWindow = (SDL_Window **)malloc(sizeof(SDL_Window *) * nbr_element);

  for (int i = 0; i < nbr_element; i++)
  {
    tabWindow[i] = SDL_CreateWindow(
        "Fenetre",                  // codage en utf8, donc accents possibles
        i * TAILLE_FENETRE, milieu, // a coté de sa voisine et au milieu de l'ecran en y
        TAILLE_FENETRE, TAILLE_FENETRE,
        0); // non redimensionnable

    if (tabWindow[i] == NULL)
    {
      SDL_Log("Error : SDL window %d creation - %s\n",
              i, SDL_GetError()); // échec de la création de la fenêtre
      SDL_Quit();                 // On referme la SDL
      exit(EXIT_FAILURE);
    }
  }

  /*ANimation 1*/
  /*on créé la courbe cosinus*/
  for (int i = 0; i < nbr_element; i++)
  {
    /*cos a chaque point "I * TAILLE_FENETRE*/
    float val_cos = cosf((i) * TAILLE_FENETRE);
    /*cos au carré pour osciller entre 0 et 1 et pas -1 et 1 puis d'amplitude de taille "hauteur ecran / 2 qu'on recentre au milieu avec + milieu /2"*/
    SDL_SetWindowPosition(tabWindow[i], i * TAILLE_FENETRE, (val_cos * val_cos * milieu) + milieu / 2);
    SDL_Delay(100);
  }

  /*Animation 2*/
  /*on fait osciller en changeant la valeur x des points avec une variante*/
  int variante = 0;
  while (variante < 100)
  {
    for (int i = 0; i < nbr_element; i++)
    {
      float val_cos = cosf((i + variante) * TAILLE_FENETRE);
      SDL_SetWindowPosition(tabWindow[i], i * TAILLE_FENETRE, (val_cos * val_cos * milieu) + milieu / 2);
    }
    variante++;
    printf("iteration n°%d\n", variante);
    SDL_Delay(100);
  }

  /*ANimation 3*/
  /*on replace au milieu*/
  for (int i = nbr_element - 1; i >= 0; i--)
  {
    SDL_SetWindowPosition(tabWindow[i], i * TAILLE_FENETRE, milieu);
    SDL_Delay(100);
  }

  /*Supression fenetre*/
  for (int i = 0; i < nbr_element; i++)
  {
    SDL_DestroyWindow(tabWindow[i]);
    printf("clear fenetre %d\n", i);
  }

  free(tabWindow);

  SDL_Quit(); // la SDL

  return 0;
}