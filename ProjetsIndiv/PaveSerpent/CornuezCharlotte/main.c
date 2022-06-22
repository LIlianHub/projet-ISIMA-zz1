/********************************************************************************************************************/
/*                             Création d'un cube qui tombe                                                         */
/********************************************************************************************************************/

#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/
void end_sdl(char ok,                                               // fin normale : ok = 0 ; anormale ok = 1
             char const* msg,                                       // message à afficher
             SDL_Window* window,                                    // fenêtre à fermer
             SDL_Renderer* renderer) {                              // renderer à fermer
  char msg_formated[255];                                                         
  int l;                                                                          

  if (!ok) {                                                        // Affichage de ce qui ne va pas
    strncpy(msg_formated, msg, 250);                                              
    l = strlen(msg_formated);                                                     
    strcpy(msg_formated + l, " : %s\n");                                          

    SDL_Log(msg_formated, SDL_GetError());                                        
  }                                                                               

  if (renderer != NULL) {                                           // Destruction si nécessaire du renderer
    SDL_DestroyRenderer(renderer);                                  // Attention : on suppose que les NULL sont maintenus !!
    renderer = NULL;
  }
  if (window != NULL)   {                                           // Destruction si nécessaire de la fenêtre
    SDL_DestroyWindow(window);                                      // Attention : on suppose que les NULL sont maintenus !!
    window= NULL;
  }

  SDL_Quit();                                                                     

  if (!ok) {                                                        // On quitte si cela ne va pas                
    exit(EXIT_FAILURE);                                                           
  }                                                                               
}                                                                                 

void draw(SDL_Renderer* renderer) {                                 // Je pense que vous allez faire moins laid :)
  SDL_Rect rectangle,cube;                                                             

  SDL_SetRenderDrawColor(renderer,                                                
                         255, 255, 255,                                  // mode Red, Green, Blue (tous dans 0..255)
                         255);                                      // 0 = transparent ; 255 = opaque
  rectangle.x = 0;                                                  // x haut gauche du rectangle
  rectangle.y = 0;                                                  // y haut gauche du rectangle
  rectangle.w = 1920;                                                // sa largeur (w = width)
  rectangle.h = 1080;                                                // sa hauteur (h = height)

  SDL_RenderFillRect(renderer, &rectangle);                         


  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);                   
  SDL_RenderDrawLine(renderer,                                      
                     0, 0,                                          // x,y du point de la première extrémité
                     600, 500);                                     // x,y seconde extrémité

  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderDrawLine(renderer,
                      600,500,
                      1920, 500);

  

  SDL_SetRenderDrawColor(renderer, 253,108,58,255);
  cube.x=100;
  cube.y=37;
  cube.w=50;
  cube.h=50;
  SDL_RenderFillRect(renderer, &cube);

  SDL_RenderPresent(renderer);

  
  SDL_Delay(1000);
  
  SDL_Rect rectangle1,cube1;                                                             

  SDL_SetRenderDrawColor(renderer,                                                
                         255, 255, 255,                                  // mode Red, Green, Blue (tous dans 0..255)
                         255);                                      // 0 = transparent ; 255 = opaque
  rectangle1.x = 0;                                                  // x haut gauche du rectangle
  rectangle1.y = 0;                                                  // y haut gauche du rectangle
  rectangle1.w = 1920;                                                // sa largeur (w = width)
  rectangle1.h = 1080;                                                // sa hauteur (h = height)

  SDL_RenderFillRect(renderer, &rectangle1);                         


  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);                   
  SDL_RenderDrawLine(renderer,                                      
                     0, 0,                                          // x,y du point de la première extrémité
                     600, 500);                                     // x,y seconde extrémité

  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderDrawLine(renderer,
                      600,500,
                      1920, 500);

  

  SDL_SetRenderDrawColor(renderer, 253,108,58,255);
  cube1.x=200;
  cube1.y=115;
  cube1.w=50;
  cube1.h=50;
  SDL_RenderFillRect(renderer, &cube1);
  SDL_RenderPresent(renderer);

  
  SDL_Delay(1000);
  
  SDL_Rect rectangle2,cube2;                                                             

  SDL_SetRenderDrawColor(renderer,                                                
                         255, 255, 255,                                  // mode Red, Green, Blue (tous dans 0..255)
                         255);                                      // 0 = transparent ; 255 = opaque
  rectangle2.x = 0;                                                  // x haut gauche du rectangle
  rectangle2.y = 0;                                                  // y haut gauche du rectangle
  rectangle2.w = 1920;                                                // sa largeur (w = width)
  rectangle2.h = 1080;                                                // sa hauteur (h = height)

  SDL_RenderFillRect(renderer, &rectangle2);                         


  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);                   
  SDL_RenderDrawLine(renderer,                                      
                     0, 0,                                          // x,y du point de la première extrémité
                     600, 500);                                     // x,y seconde extrémité

  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderDrawLine(renderer,
                      600,500,
                      1920, 500);

  

  SDL_SetRenderDrawColor(renderer, 253,108,58,255);
  cube2.x=300;
  cube2.y=197;
  cube2.w=50;
  cube2.h=50;
  SDL_RenderFillRect(renderer, &cube2);
  
  SDL_RenderPresent(renderer);

  
  SDL_Delay(1000);
  
  SDL_Rect rectangle3,cube3;                                                             

  SDL_SetRenderDrawColor(renderer,                                                
                         255, 255, 255,                                  // mode Red, Green, Blue (tous dans 0..255)
                         255);                                      // 0 = transparent ; 255 = opaque
  rectangle3.x = 0;                                                  // x haut gauche du rectangle
  rectangle3.y = 0;                                                  // y haut gauche du rectangle
  rectangle3.w = 1920;                                                // sa largeur (w = width)
  rectangle3.h = 1080;                                                // sa hauteur (h = height)

  SDL_RenderFillRect(renderer, &rectangle3);                         


  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);                   
  SDL_RenderDrawLine(renderer,                                      
                     0, 0,                                          // x,y du point de la première extrémité
                     600, 500);                                     // x,y seconde extrémité

  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderDrawLine(renderer,
                      600,500,
                      1920, 500);

  

  SDL_SetRenderDrawColor(renderer, 253,108,58,255);
  cube3.x=400;
  cube3.y=280;
  cube3.w=50;
  cube3.h=50;
  SDL_RenderFillRect(renderer, &cube3);

  SDL_RenderPresent(renderer);

  
  SDL_Delay(1000);
  
  SDL_Rect rectangle4,cube4;                                                             

  SDL_SetRenderDrawColor(renderer,                                                
                         255, 255, 255,                                  // mode Red, Green, Blue (tous dans 0..255)
                         255);                                      // 0 = transparent ; 255 = opaque
  rectangle4.x = 0;                                                  // x haut gauche du rectangle
  rectangle4.y = 0;                                                  // y haut gauche du rectangle
  rectangle4.w = 1920;                                                // sa largeur (w = width)
  rectangle4.h = 1080;                                                // sa hauteur (h = height)

  SDL_RenderFillRect(renderer, &rectangle4);                         


  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);                   
  SDL_RenderDrawLine(renderer,                                      
                     0, 0,                                          // x,y du point de la première extrémité
                     600, 500);                                     // x,y seconde extrémité

  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderDrawLine(renderer,
                      600,500,
                      1920, 500);

  

  SDL_SetRenderDrawColor(renderer, 253,108,58,255);
  cube4.x=500;
  cube4.y=365;
  cube4.w=50;
  cube4.h=50;
  SDL_RenderFillRect(renderer, &cube4);

SDL_RenderPresent(renderer);

  
  SDL_Delay(1000);
  
  SDL_Rect rectangle5,cube5;                                                             

  SDL_SetRenderDrawColor(renderer,                                                
                         255, 255, 255,                                  // mode Red, Green, Blue (tous dans 0..255)
                         255);                                      // 0 = transparent ; 255 = opaque
  rectangle5.x = 0;                                                  // x haut gauche du rectangle
  rectangle5.y = 0;                                                  // y haut gauche du rectangle
  rectangle5.w = 1920;                                                // sa largeur (w = width)
  rectangle5.h = 1080;                                                // sa hauteur (h = height)

  SDL_RenderFillRect(renderer, &rectangle5);                         


  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);                   
  SDL_RenderDrawLine(renderer,                                      
                     0, 0,                                          // x,y du point de la première extrémité
                     600, 500);                                     // x,y seconde extrémité

  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderDrawLine(renderer,
                      600,500,
                      1920, 500);

  

  SDL_SetRenderDrawColor(renderer, 253,108,58,255);
  cube5.x=600;
  cube5.y=450;
  cube5.w=50;
  cube5.h=50;
  SDL_RenderFillRect(renderer, &cube5);

  SDL_RenderPresent(renderer);

  
  SDL_Delay(1000);
  
  SDL_Rect rectangle6,cube6;                                                             

  SDL_SetRenderDrawColor(renderer,                                                
                         255, 255, 255,                                  // mode Red, Green, Blue (tous dans 0..255)
                         255);                                      // 0 = transparent ; 255 = opaque
  rectangle6.x = 0;                                                  // x haut gauche du rectangle
  rectangle6.y = 0;                                                  // y haut gauche du rectangle
  rectangle6.w = 1920;                                                // sa largeur (w = width)
  rectangle6.h = 1080;                                                // sa hauteur (h = height)

  SDL_RenderFillRect(renderer, &rectangle6);                         


  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);                   
  SDL_RenderDrawLine(renderer,                                      
                     0, 0,                                          // x,y du point de la première extrémité
                     600, 500);                                     // x,y seconde extrémité

  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderDrawLine(renderer,
                      600,500,
                      1920, 500);

  

  SDL_SetRenderDrawColor(renderer, 253,108,58,255);
  cube6.x=700;
  cube6.y=450;
  cube6.w=50;
  cube6.h=50;
  SDL_RenderFillRect(renderer, &cube6);

  
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  SDL_DisplayMode screen;

  /*********************************************************************************************************************/  
  /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

  SDL_GetCurrentDisplayMode(0, &screen);
  printf("Résolution écran\n\tw : %d\n\th : %d\n",
         screen.w, screen.h);

  /* Création de la fenêtre */
  window = SDL_CreateWindow("Premier dessin",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
                            screen.h * 0.66,
                            SDL_WINDOW_OPENGL);
  if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

  /* Création du renderer */
  renderer = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

  /*********************************************************************************************************************/
  /*                                     On dessine dans le renderer                                                   */
  /*********************************************************************************************************************/
  /*             Cette partie pourrait avantageusement être remplacée par la boucle évènementielle                     */ 
  draw(renderer);                                      // appel de la fonction qui crée l'image  
  SDL_RenderPresent(renderer);                         // affichage
  SDL_Delay(1000);                                     // Pause exprimée en ms


  /* on referme proprement la SDL */
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}