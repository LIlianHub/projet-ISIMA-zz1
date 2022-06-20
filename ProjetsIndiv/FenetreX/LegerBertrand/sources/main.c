#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define NBREWINDOWS 100


int main(int argc, char **argv) {

  int i=0;
  int j;
  
  (void)argc;
  (void)argv;

  SDL_Window *windows [NBREWINDOWS*2];


  
  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", 
	    SDL_GetError());                // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }


  SDL_DisplayMode current;
  SDL_GetCurrentDisplayMode(0, &current);
  int width = current.w;
  int height = current.h;


  float position_x=0;
  float position_y=0;

  while(position_x < height/2){

    windows[i] = SDL_CreateWindow(
				  "left circle",
				  0,0,
				  70,70,
				  0
				  );

    if(windows[i] == NULL){
      SDL_Log("Erro : SDL windox %d creation - %s\n",i,SDL_GetError());    
      SDL_Quit();
      exit(EXIT_FAILURE);
    }
    position_x = position_x + 15;
    position_y = position_y + 15;
    SDL_SetWindowPosition(windows[i],position_x,position_y);

    SDL_Delay(75);
    i++;
  }
  
  SDL_Delay(300);
  for (j = 0 ; j < i-1 ; j++){
    
    SDL_DestroyWindow(windows[j]);
    SDL_Delay(200);  
  }


  SDL_SetWindowPosition(windows[j+1],cosf(position_x),sinf(position_y));
  
  SDL_Delay(5000);
  
  SDL_Quit();                                // quitte la SDL

  return 0;
}
