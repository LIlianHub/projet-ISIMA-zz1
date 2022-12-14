#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


/*Principe
 *faire afficher une fenêtre, mettre le fond de la fenêtre en bleu fonçé 
 *faire apparaître des lignes, représentant la pluie, qui apparaissent aléatoirement
 *rajouter des cercles au point d'impact pour faire un effet d'eau touchant de l'eau*/


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


void drawCircle(SDL_Renderer* renderer, int centre_x, int centre_y, int rayon_x, int rayon_y){
  for( float angle = 0 ; angle < 2*M_PI; angle += M_PI / 4000){
    SDL_RenderDrawPoint(renderer,
			centre_x + rayon_x * cos(angle),
			centre_y + rayon_y * sin(angle));
  }  
}


void draw(SDL_Renderer* renderer) {                                
  SDL_Rect rectangle;                                                             
  
  SDL_SetRenderDrawColor(renderer,                                                
                         37, 25, 133,                               // mode Red, Green, Blue (tous dans 0..255)
                         255);                                      // 0 = transparent ; 255 = opaque
  rectangle.x = 0;
  // x haut gauche du rectangle
  rectangle.y = 0;                                                  // y haut gauche du rectangle
  rectangle.w = 600;                                                // sa largeur (w = width)
  rectangle.h = 600;                                                // sa hauteur (h = height)

  SDL_RenderFillRect(renderer, &rectangle);                         

  SDL_SetRenderDrawColor(renderer, 224, 222, 238, 255);                   
  

  for(int m = 0; m < 20; m++){
    int pos_x_deb = rand()% 600;
    int pos_y_deb = rand()% 600;
    int pos_x_fin = pos_x_deb - rand()%50;
    int pos_y_fin = pos_y_deb + rand()%600 ;

    
    SDL_RenderDrawLine(renderer,                                      
		       pos_x_deb, pos_y_deb,                                      // x,y du point de la première extrémité
		       pos_x_fin, pos_y_fin);                                     // x,y seconde extrémité
  
  drawCircle(renderer,pos_x_fin,pos_y_fin,35,23);
  drawCircle(renderer,pos_x_fin,pos_y_fin,20,17);
  drawCircle(renderer,pos_x_fin,pos_y_fin,7,5);
  }

}





int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  SDL_DisplayMode screen;

  /*********************************************************************************************************************/  
  /*                         Initialisation de la SDL  + gestion de l'échec possible*/
  
  if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

  SDL_GetCurrentDisplayMode(0, &screen);
  printf("Résolution écran\n\tw : %d\n\th : %d\n",
         screen.w, screen.h);

  /* Création de la fenêtre */
  window = SDL_CreateWindow("IT'S RAINING MAN",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 600,
                            600,
                            SDL_WINDOW_OPENGL);
  if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

  /* Création du renderer */
  renderer = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

  /*********************************************************************************************************************/
  /*                                     On dessine dans le renderer                                                   */
  /*********************************************************************************************************************/


  SDL_bool program_on = SDL_TRUE;               // Booléen pour dire que le programme doit continuer
  SDL_Event event;                              // c'est le type IMPORTANT !!

  printf("Pour fermer la fenêtre fermez avez la croix\n");
  
  while (program_on){                           // Voilà la boucle des évènements 


    if (SDL_PollEvent(&event)){                 // si la file d'évènements n'est pas vide : défiler l'élément en tête
      // de file dans 'event'
      switch(event.type){                       // En fonction de la valeur du type de cet évènement
      case SDL_QUIT :                           // Un évènement simple, on a cliqué sur la x de la fenêtre
	program_on = SDL_FALSE;                 // Il est temps d'arrêter le programme
	break;

      default:                                  // L'évènement défilé ne nous intéresse pas
	break;
      }
    }
    draw(renderer);
    SDL_Delay(100);// appel de la fonction qui crée l'image  
    SDL_RenderPresent(renderer);                         // affichage
  }  
  
  /* on referme proprement la SDL */
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}
