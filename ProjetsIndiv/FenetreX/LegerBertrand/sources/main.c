#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/

int i;
int j;

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  SDL_Window *windows [100];


  
  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", 
	    SDL_GetError());                // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }

  for (i = 0 ; i<100 ; i++){

    windows[i] = SDL_CreateWindow(
				  "Top to right",
				  0+ 10*i ,0 + 10*i,
				  400,300,
				  0
				  );
    if(windows[i] == NULL) {
      SDL_Log("Error : SDL window %d ceation - %s\n",i,SDL_GetError());
      SDL_Quit();
      exit(EXIT_FAILURE);
    }
    
  }

  for (i = 0 ; i < 100 ; i++){
    
    SDL_DestroyWindow(windows[i]);
    
  }
  
  SDL_Quit();                                // la SDL

  return 0;
}
