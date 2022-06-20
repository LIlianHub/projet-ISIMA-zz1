#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define NBREWINDOWS 400



int main(int argc, char **argv) {

  int i=0;
  int j;
  
  (void)argc;
  (void)argv;

  SDL_Window *windows [NBREWINDOWS];


  
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


  float position_x_left=0; //première fenêtre côté gauche au milieu de la largeur de l'écran
  float position_y_left=height/2;

  float position_x_right=width; //première fenêtre côté droit au milieu de la largeur de l'écran
  float position_y_right=height/2;

  
  /*Animation 1:
   *ligne de fenêtre de la moitié de la largeur de l'écran et de longueur = 1/3 de l'écran
   *Qui se referme une fois que la dernière est placée*/
  
  while(position_x_left < width/2 && position_x_right > width/2 ){

    windows[i] = SDL_CreateWindow(
				  "left",
				  position_x_left,position_y_left,
				  40,20,
				  0
				  );

    windows[200+i] = SDL_CreateWindow(
				      "right",
				      position_x_right,position_y_right,
				      40,20,
				      SDL_WINDOW_RESIZABLE
				      );
    
    if(windows[i] == NULL || windows[200+i] == NULL){
      SDL_Log("Error : SDL window %d creation - %s\n",i,SDL_GetError());    
      SDL_Quit();
      exit(EXIT_FAILURE);
    }
    position_x_left = position_x_left + 15;
    SDL_SetWindowPosition(windows[i],position_x_left,position_y_left);

    position_x_right = position_x_right - 15;
    SDL_SetWindowPosition(windows[i],position_x_left,position_y_left);
    
    SDL_Delay(25);
    i++;
  }
  
  SDL_Delay(300);
  
  for (j = 0 ; j < i ; j++){
    
    SDL_DestroyWindow(windows[j]);
    if(j<i-1){
      SDL_DestroyWindow(windows[200+j]);
    }
    SDL_Delay(75);  
  }

  /*Animation 2 :
   *Je fais tourner fenêtres grâce aux coordonnées du cercle trigonométrique
   *A chaque itération le rayon du cercle va grandir*/

  int b;
  
  for ( b = 0 ; b <= 100 ; b++ ){ 

    windows[b] = SDL_CreateWindow(
				  "left circle",
				  position_x_left,position_y_left,
				  40,30,
				  0
				  );

    if(windows[b] == NULL){
      SDL_Log("Error : SDL window %d creation - %s\n",b,SDL_GetError());    
      SDL_Quit();
      exit(EXIT_FAILURE);
    }


    float pos_x = cosf(b)*25*(b/4) + position_x_left;
    float pos_y = sinf(b)*25*(b/4) + position_y_left;
    
    SDL_SetWindowPosition(windows[b],pos_x,pos_y);
    SDL_Delay(75);
  }

  SDL_Delay(3000);

  for (b = 100 ; b>=0; b--){
    
    SDL_DestroyWindow(windows[b]);
    SDL_Delay(10);
    
  }
  SDL_DestroyWindow(windows[1]);

  SDL_Delay(5000);
  
  SDL_Quit();            // quitte la SDL

  return 0;
}
