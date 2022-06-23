/********************************************************************************************************************/
/*                      Affichage d'un jardin puis d'un nuage et enfin d'un dinosaure qui court                     */
/* J'affiche en fond un jardin avec un nuage qui traverse le haut du jardin. En bas de l'image, on peut voir un     */
/* dinosaure bleu qui traverse en courant                                                                           */
/********************************************************************************************************************/

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h> // Nécessaire pour la fonction IMG_Load
                      // Penser au flag -lsdl2_image à la compilation

#include <math.h>
#include <stdio.h>
#include <string.h>

/*********************************************************************************************************************/
/*                              Programme  de création de rendu + dessin                                    */
/*********************************************************************************************************************/
void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
{ // renderer à fermer
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
  {                                // Destruction si nécessaire du renderer
    SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
    renderer = NULL;
  }
  if (window != NULL)
  {                            // Destruction si nécessaire de la fenêtre
    SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
    window = NULL;
  }

  SDL_Quit();

  if (!ok)
  { // On quitte si cela ne va pas
    exit(EXIT_FAILURE);
  }
}

SDL_Texture *ImageEnTexture(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
  SDL_Surface *my_image = NULL;   // Variable de passage
  SDL_Texture *my_texture = NULL; // La texture

  my_image = IMG_Load(file_image_name); // Chargement de l'image dans la surface
                                        // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
                                        // uniquement possible si l'image est au format bmp */
  if (my_image == NULL)
    end_sdl(0, "Chargement de l'image impossible", window, renderer);

  my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
  SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire
  if (my_texture == NULL)
    end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

  return my_texture;
}

// IMG_Quit()

void AffichageTextureFenetreComplete(SDL_Texture *my_texture, SDL_Window *window,
                                     SDL_Renderer *renderer)
{
  SDL_Rect
      source = {0},            // Rectangle définissant la zone de la texture à récupérer
      window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
      destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h); // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h); // Récupération des dimensions de l'image

  destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

  SDL_RenderCopy(renderer, my_texture,
                 &source,
                 &destination); // Création de l'élément à afficher
}

void AnimationImage(SDL_Texture *my_texture,
                    SDL_Window *window,
                    SDL_Renderer *renderer,
                    int i)
{
  SDL_Rect
      source = {0},            // Rectangle définissant la zone de la texture à récupérer
      window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
      destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h); // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w,
                   &source.h); // Récupération des dimensions de l'image

  /* On décide de déplacer dans la fenêtre         cette image */
  float zoom = 0.25; // Facteur de zoom entre l'image source et l'image affichée

  destination.w = source.w * zoom; // On applique le zoom sur la largeur
  destination.h = source.h * zoom; // On applique le zoom sur la hauteur
  destination.y =
      (window_dimensions.w - destination.w) / 6;   // On centre en haut
  float h = (window_dimensions.h - destination.h); // largeur du déplacement à effectuer

  destination.x = h * 0.005 * i; // hauteur en fonction du numéro d'image

  SDL_RenderCopy(renderer, my_texture, &source, &destination); // Préparation de l'affichage
                                                               // Pause en ms
}

void AnimationSprite(SDL_Texture *my_texture,
                     SDL_Window *window,
                     SDL_Renderer *renderer,
                     SDL_Texture *nuage,
                     SDL_Texture *fond)
{
  SDL_Rect
      source = {0},            // Rectangle définissant la zone totale de la planche
      window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
      destination = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
      state = {0};             // Rectangle de la vignette en cours dans la planche

  SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                    &window_dimensions.w,
                    &window_dimensions.h);
  SDL_QueryTexture(my_texture, // Récupération des dimensions de l'image
                   NULL, NULL,
                   &source.w, &source.h);

  /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

  int nb_images = 9;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
  float zoom = 6;                      // zoom, car ces images sont un peu petites
  int offset_x = source.w / nb_images, // La largeur d'une vignette de l'image, marche car la planche est bien réglée
      offset_y = source.h / 4 + 1;     // La hauteur d'une vignette de l'image, marche car la planche est bien réglée

  state.x = 0;            // La première vignette est en début de ligne
  state.y = 3 * offset_y; // On s'intéresse à la 4ème ligne, le bonhomme qui court
  state.w = offset_x;     // Largeur de la vignette
  state.h = offset_y;     // Hauteur de la vignette

  destination.w = offset_x * zoom; // Largeur du sprite à l'écran
  destination.h = offset_y * zoom; // Hauteur du sprite à l'écran

  destination.y = // La course se fait en milieu d'écran (en vertical)
      (window_dimensions.h - destination.h) / 2;

  SDL_Event event;
  SDL_bool program_on = SDL_TRUE;
  int i = 0;

  while (program_on)
  {

    if (SDL_PollEvent(&event))
    { // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
      // terminé le programme Défiler l'élément en tête de file dans 'event'
      switch (event.type)
      {                         // En fonction de la valeur du type de cet évènement
      case SDL_QUIT:            // Un évènement simple, on a cliqué sur la x de la // fenêtre
        program_on = SDL_FALSE; // Il est temps d'arrêter le programme
        break;
      case SDL_KEYDOWN: // Le type de event est : une touche appuyée
                        // comme la valeur du type est SDL_Keydown, dans la partie 'union' de
                        // l'event, plusieurs champs deviennent pertinents
        switch (event.key.keysym.sym)
        {        // la touche appuyée est ...
        default: // Une touche appuyée qu'on ne traite pas
          break;
        }
        break;
      }
    }
    SDL_RenderClear(renderer);

    AffichageTextureFenetreComplete(fond, window, renderer);
    AnimationImage(nuage, window, renderer, i);
    destination.x = i * 4;   // Position en x pour l'affichage du sprite
    state.x += offset_x; // On passe à la vignette suivante dans l'image
    state.x %= source.w; // La vignette qui suit celle de fin de ligne est
    // celle de début de ligne
    SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                   &state,
                   &destination);

    SDL_RenderPresent(renderer);
    i++;

    SDL_Delay(100); // Petite pause
  }
}

int main()
{
  int LARGEUR = 1000;

  SDL_Window *fenetre = NULL;
  SDL_Renderer *renderer = NULL;

  SDL_Texture *fond = NULL;
  SDL_Texture *nuage = NULL;
  SDL_Texture *dino = NULL;

  fenetre = SDL_CreateWindow("Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR, LARGEUR, SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
  dino = ImageEnTexture("./img/dino.png", fenetre, renderer);
  fond = ImageEnTexture("./img/jardin.bmp", fenetre, renderer);
  nuage = ImageEnTexture("./img/nuage.bmp", fenetre, renderer);


  AnimationSprite(dino, fenetre, renderer, nuage, fond);
}

