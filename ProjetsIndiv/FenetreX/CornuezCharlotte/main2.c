#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

int main(int argc, char **argv){
    (void)argc;
    (void)argv;

    int i,j = 0, etoile = 0;

    


/* Création tableau de fenêtres */

    SDL_Window *TabWindows[100] ;

/* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", 
            SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    /* Récupération de la taille de l'écran */

    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    int width = current.w ;
    int height = current.h ;
    //printf("%d %d\n", width,height);


/* Création des fenêtres */
    for (i =0; i<14; i++){
        TabWindows[i]= SDL_CreateWindow(
            "Fenêtres U",                    // codage en utf8, donc accents possibles
            width/3, height/3 + j,                             // coin haut gauche en haut gauche de l'écran
            200, 200,                              // largeur = 400, hauteur = 300
            SDL_WINDOW_RESIZABLE); 
            j = j + height/50;

        /* Vérification de la création des fenêtres */

        if (TabWindows[i] == NULL) {
            SDL_Log("Error : SDL window 1 creation - %s\n", 
                SDL_GetError());                 // échec de la création de la fenêtre
            SDL_Quit();                              // On referme la SDL       
            exit(EXIT_FAILURE);
    }}


    int k = j - height/50;


    for (i =14; i<29; i++){
        TabWindows[i]= SDL_CreateWindow(
            "Fenêtres U",                    // codage en utf8, donc accents possibles
            width/3 + (i-15)*25 ,height/3 + k,                              // coin haut gauche en haut gauche de l'écran
            200, 200,                              // largeur = 400, hauteur = 300
            SDL_WINDOW_RESIZABLE); 
            
        /* Vérification de la création des fenêtres */

        if (TabWindows[i] == NULL) {
            SDL_Log("Error : SDL window 1 creation - %s\n", 
                SDL_GetError());                 // échec de la création de la fenêtre
            SDL_Quit();                              // On referme la SDL       
            exit(EXIT_FAILURE);
    }
    }

    for (i =29; i<44; i++){
        TabWindows[i]= SDL_CreateWindow(
            "Fenêtres U",                    // codage en utf8, donc accents possibles
            width/3 + (15*25), height/3 + k,                             // coin haut gauche en haut gauche de l'écran
            200, 200,                              // largeur = 400, hauteur = 300
            SDL_WINDOW_RESIZABLE); 
            k = k - height/50;
        
        /* Vérification de la création des fenêtres */

        if (TabWindows[i] == NULL) {
            SDL_Log("Error : SDL window 1 creation - %s\n", 
                SDL_GetError());                 // échec de la création de la fenêtre
            SDL_Quit();                              // On referme la SDL       
            exit(EXIT_FAILURE);
    }


    }
    
/*Mise en place d'une étoile*/
    for (etoile; etoile<45; etoile++){
        SDL_SetWindowPosition(TabWindows[etoile],(width-200)/2,(height-200)/2);
    }
    SDL_Delay(1000);
    for (etoile = 0; etoile<44; etoile+=4){
        for (int x = (width-200)/2; x>0; x--){
            SDL_SetWindowPosition(TabWindows[etoile],x,((width-200)/(height-200))*x);
            
            SDL_Delay(1);
        }
        for (int x = width/2; x<width; x++){
            SDL_SetWindowPosition(TabWindows[etoile+3],x,(width/height)*x);
            
            SDL_Delay(1);
        }
        for (int y = width/2; y<width; y++){
            SDL_SetWindowPosition(TabWindows[etoile+2],y,((height-2*width)/width)*y+width);

            SDL_Delay(1);
        }
        for (int y= width/2; y>0; y--){
            SDL_SetWindowPosition(TabWindows[etoile+1],y,((height-2*width)/width)*y+width);
            printf("%d \n",((height-2*width)/width)*y+width);
            SDL_Delay(1);
        }


        
        

        }
        
    
    
    SDL_Delay(2000);

/* Fermeture des fenêtres */

    for(i= 45; i>0; i--){
        SDL_DestroyWindow(TabWindows[i]); 
    }

    SDL_Quit();    //fermeture de la SDL 

    return 0 ;
}