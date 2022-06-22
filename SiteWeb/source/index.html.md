---
title: Projet ZZ1 Groupe 31

toc_footers:
  - Projet ZZ1
  - BALLEJOS Lilian
  - CORNUEZ Charlotte
  - LEGER Bertrand


language_tabs:
  - c

includes:

search: false

code_clipboard: false

meta:
  - name: Projet ZZ1 BALLEJOS CORNUEZ LEGER
    content: Documentation for the Kittn API
---

# Accueil
## Membres du Groupe 31

Bienvenue sur le site web des membres du groupe 31 du Projet ZZ1 2022, nous sommes

* BALLEJOS Lilian
* CORNUEZ Charlotte
* LEGER Bertrand

# Hébergement du projet

## Les programmes

Les programmes se trouvent tous dans le GitLab ISIMA de BALLEJOS Lilian à ce lien: [ici](https://gitlab.isima.fr/liballejos/projetzz1)

# TODO List
## Fonctionnement

Vous trouverez ici le programme de tout ce que l'on va faire durant ces 2 semaines jour par jour

### 20/06/22 (Lundi)
Avancé | Membre | Tâche
-------------- | -------------- | --------------
✔️| BALLEJOS Lilian | Mise en place du site
✔️| Commun | Mise en place d'un GitLab organisé
✔️| BALLEJOS Lilian | Xfenetré
✔️| LEGER BERTRAND  | Xfenetré
✔️| CORNUEZ Charlotte | Xfenetré
✔️| BALLEJOS Lilian | Animation Forme

### 21/06/22 (Mardi)

Avancé | Membre | Tâche
-------------- | -------------- | --------------
✔️| Commun | Répartition tâches jeu de la vie
✔️| BALLEJOS Lilian | Animation avec Texture
✔️| LEGER Bertrand | Animation Forme
✔️| CORNUEZ Charlotte | Animation Forme
✔️| CORNUEZ CHarlotte | Animation avec Texture
✔️| LEGER Bertrand | Animation avec Texture
✔️| Commun | Commencement du Jeu de la vie

### 21/06/22 (Mercredi)

Avancé | Membre | Tâche
-------------- | -------------- | --------------
✔️| Commun | Finalisation du Jeu de la vie
✔️| Commun | Répartition des tâches du "Premier Chef d'Oeuvre"
✔️| Commun | Commencement du premier chef d'oeuvre
✔️| BALLEJOS Lilian | Mise à jour du Site en prévision de Vendredi


# Xfenetré

## BALLEJOS Lilian

### Explication et Code

Mise en place d'un programme qui récupère les dimensions de l'écran principal et crée une animation de sinusoïde avec les fenêtres générées.

```c
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
```

### Vidéo

<p align="center"><iframe width="80%" height="315" src="https://www.youtube.com/embed/PmCJ4XlQqXs" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></p>

## LEGER Bertrand

### Explication et Code

Principe :
J'ouvre des fenêtres sur les côtés de l'écran en partant du milieu de la hauteur et du côté gauche et droit puis elles disparaissent. Puis j'ouvre des fenêtres et je les fais "spiraler" grâce au cosinus et
en augmentant le rayon du cercle à chaque itération, je finis par fermer toutes mes fenêtres une à une.

```c
SDL_Window *windows[NBREWINDOWS];

  SDL_DisplayMode current;
  SDL_GetCurrentDisplayMode(0, &current);
  int width = current.w;
  int height = current.h;

  float position_x_left = 0; // première fenêtre côté gauche au milieu de la largeur de l'écran
  float position_y_left = height / 2;

  float position_x_right = width; // première fenêtre côté droit au milieu de la largeur de l'écran
  float position_y_right = height / 2;

  /*Animation 1:
   *ligne de fenêtre de la moitié de la largeur de l'écran et de longueur = 1/3 de l'écran
   *Qui se referme une fois que la dernière est placée*/

  while (position_x_left < width / 2 && position_x_right > width / 2)
  {

    windows[i] = SDL_CreateWindow(
        "left",
        position_x_left, position_y_left,
        40, 20,
        0);

    windows[200 + i] = SDL_CreateWindow(
        "right",
        position_x_right, position_y_right,
        40, 20,
        SDL_WINDOW_RESIZABLE);

    if (windows[i] == NULL || windows[200 + i] == NULL)
    {
      SDL_Log("Error : SDL window %d creation - %s\n", i, SDL_GetError());
      SDL_Quit();
      exit(EXIT_FAILURE);
    }
    position_x_left = position_x_left + 15;
    SDL_SetWindowPosition(windows[i], position_x_left, position_y_left);

    position_x_right = position_x_right - 15;
    SDL_SetWindowPosition(windows[i], position_x_left, position_y_left);

    SDL_Delay(25);
    i++;
  }

  SDL_Delay(300);

  /*Animation 2 :
   *Je fais tourner fenêtres grâce aux coordonnées du cercle trigonométrique
   *A chaque itération le rayon du cercle va grandir*/

  int b;

  for (b = 0; b <= 100; b++)
  {

    if (b == 0)
    {

      for (j = 0; j < i; j++)
      {

        SDL_DestroyWindow(windows[j]);
        SDL_DestroyWindow(windows[200 + j]);
        SDL_Delay(75);
      }
    }
    windows[b] = SDL_CreateWindow(
        "left circle",
        position_x_left, position_y_left,
        40, 30,
        0);

    if (windows[b] == NULL)
    {
      SDL_Log("Error : SDL window %d creation - %s\n", b, SDL_GetError());
      SDL_Quit();
      exit(EXIT_FAILURE);
    }

    float pos_x = cosf(b) * 25 * (b / 4) + position_x_left;
    float pos_y = sinf(b) * 25 * (b / 4) + position_y_left;

    SDL_SetWindowPosition(windows[b], pos_x, pos_y);

    SDL_Delay(75);
  }

  SDL_Delay(3000);

  for (b = 100; b >= 0; b--)
  {

    SDL_DestroyWindow(windows[b]);
    SDL_Delay(20);
  }
```

### Vidéo

<p style="texte-align: center;"><iframe width="80%" height="315" src="https://www.youtube.com/embed/j7vuU87j4RA" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></p>

## CORNUEZ Charlotte

### Explication et Code
           
Les fenêtres s'affichent petit à petit pour former un U. Puis elles se rassemblent au milieu avant de partir chacune leur tour dans un des coins de l'écran.             

```c
/* Récupération de la taille de l'écran */

    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    int width = current.w;
    int height = current.h;
    // printf("%d %d\n", width,height);

    /* Création des fenêtres */
    for (i = 0; i < 14; i++)
    {
        TabWindows[i] = SDL_CreateWindow(
            "Fenêtres U",              // codage en utf8, donc accents possibles
            width / 3, height / 3 + j, // coin haut gauche en haut gauche de l'écran
            200, 200,                  // largeur = 400, hauteur = 300
            SDL_WINDOW_RESIZABLE);
        j = j + height / 50;

        /* Vérification de la création des fenêtres */

        if (TabWindows[i] == NULL)
        {
            SDL_Log("Error : SDL window 1 creation - %s\n",
                    SDL_GetError()); // échec de la création de la fenêtre
            SDL_Quit();              // On referme la SDL
            exit(EXIT_FAILURE);
        }
    }

    int k = j - height / 50;

    for (i = 14; i < 29; i++)
    {
        TabWindows[i] = SDL_CreateWindow(
            "Fenêtres U",                              // codage en utf8, donc accents possibles
            width / 3 + (i - 14) * 25, height / 3 + k, // coin haut gauche en haut gauche de l'écran
            200, 200,                                  // largeur = 400, hauteur = 300
            SDL_WINDOW_RESIZABLE);

        /* Vérification de la création des fenêtres */

        if (TabWindows[i] == NULL)
        {
            SDL_Log("Error : SDL window 1 creation - %s\n",
                    SDL_GetError()); // échec de la création de la fenêtre
            SDL_Quit();              // On referme la SDL
            exit(EXIT_FAILURE);
        }
    }

    for (i = 29; i < 44; i++)
    {
        TabWindows[i] = SDL_CreateWindow(
            "Fenêtres U",                          // codage en utf8, donc accents possibles
            width / 3 + (14 * 25), height / 3 + k, // coin haut gauche en haut gauche de l'écran
            200, 200,                              // largeur = 400, hauteur = 300
            SDL_WINDOW_RESIZABLE);
        k = k - height / 50;

        /* Vérification de la création des fenêtres */

        if (TabWindows[i] == NULL)
        {
            SDL_Log("Error : SDL window 1 creation - %s\n",
                    SDL_GetError()); // échec de la création de la fenêtre
            SDL_Quit();              // On referme la SDL
            exit(EXIT_FAILURE);
        }
    }
    SDL_Delay(100);
    /*Mise en place d'une étoile : les points vont aux quatres coins*/
    for (etoile; etoile < 45; etoile++)
    {
        SDL_SetWindowPosition(TabWindows[etoile], (width - 200) / 2, (height - 200) / 2);
    }
    SDL_Delay(100);
    for (etoile = 0; etoile < 44; etoile += 4)
    {
        for (int x = (width - 200) / 2; x > 0; x--)
        {
            SDL_SetWindowPosition(TabWindows[etoile], x, ((width - 200) / (height - 200)) * x);

            SDL_Delay(1);
        }
        for (int x = width / 2; x < width; x++)
        {
            SDL_SetWindowPosition(TabWindows[etoile + 3], x, (width / height) * x);

            SDL_Delay(1);
        }
        for (int y = width / 2; y < width; y++)
        {
            SDL_SetWindowPosition(TabWindows[etoile + 2], y, ((height - 2 * width) / width) * y + width);

            SDL_Delay(1);
        }
        for (int y = width / 2; y > 0; y--)
        {
            SDL_SetWindowPosition(TabWindows[etoile + 1], y, ((height - 2 * width) / width) * y + width);
            printf("%d \n", ((height - 2 * width) / width) * y + width);
            SDL_Delay(1);
        }
    }

    SDL_Delay(200);

    /* Fermeture des fenêtres */

    for (i = 45; i > 0; i--)
    {
        SDL_DestroyWindow(TabWindows[i]);
    }

```

### Vidéo

<p style="text-align: center;"><iframe width="80%" height="315" src="https://www.youtube.com/embed/CKo6G8Bd3j0" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></p>


# Animation Forme

## BALLEJOS Lilian

### Explication et Code

Mise en place d'un programme qui créée une fenêtre blanche et fais apparaitre deux ellipses qui se croisent à intervales réguliers et forment des ronds.
Pour faire cela il a suffit de changer le rayon des cercles sur la composantes X et Y en le décalant de 10 de taille. Ensuite on inverse le rayon de la composante X et Y entre les deux ellipses afin de les inverser entre elles ! De plus on joue avec les composantes de couleur pour changer la couleur des carrés qui forment les ellipses.

```c
void draw(SDL_Renderer *renderer, int largeur, int hauteur)
{
    /*Tableau de rectangle assez petit pour sembler etre des points*/
    SDL_Rect *rectangles = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NBR_RECTANGLE);
    SDL_Rect *rectangles2 = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NBR_RECTANGLE);
    int cercleTailleX = 100;
    int cercleTailleY = 200; /*taille des cercles pas la même pour avoir alternance ellispse et cercle*/
    int couleurR = 0;
    int couleurG = 20; /*couleur varie*/
    int couleurB = 10;
    float interation = 0;
    while (interation < 1000)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);                // fond blanc
        SDL_RenderClear(renderer);                                           // efface le rendu précédent
        SDL_SetRenderDrawColor(renderer, couleurR, couleurG, couleurB, 255); // couleur rectangle
        for (int i = 0; i < NBR_RECTANGLE; i++)
        {
            float valCos = cosf(i);
            float valSin = sinf(i);
            rectangles[i].x = cercleTailleX * valCos + largeur / 2;
            rectangles[i].y = cercleTailleY * valSin + hauteur / 2;
            rectangles[i].w = TAILLE_RECT;
            rectangles[i].h = TAILLE_RECT;
            SDL_RenderFillRect(renderer, &rectangles[i]); // on applique le rectangle
        }
        for (int i = 0; i < NBR_RECTANGLE; i++)
        {
            float valCos = cosf(i);
            float valSin = sinf(i); /*on inverse les largeur x et y avec le premier pour avoir une belle forme*/
            rectangles[i].x = cercleTailleY * valCos + largeur / 2;
            rectangles[i].y = cercleTailleX * valSin + hauteur / 2;
            rectangles[i].w = TAILLE_RECT;
            rectangles[i].h = TAILLE_RECT;
            SDL_RenderFillRect(renderer, &rectangles[i]); // on applique le rectangle
        }

        cercleTailleX = (cercleTailleX + 10) % 300;
        cercleTailleY = (cercleTailleY + 10) % 400;
        couleurR = (couleurR + 5) % 200;
        couleurG = (couleurG + 5) % 200; // modulo 200 pour eviter le blanc en 255
        couleurB = (couleurB + 5) % 200;
        SDL_RenderPresent(renderer); // on charge le rendu
        SDL_Delay(75);
        interation++;
    }

    free(rectangles);
    free(rectangles2);
}

```

### Vidéo

<p align="center"><iframe width="80%" height="315" src="https://www.youtube.com/embed/9enCd_bTOAw" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></p>


## CORNUEZ Charlotte

### Explication et Code

Le but de ce programme est de créer un cube qui tombe sur une pente.                               
Pour cela, on crée d'abord un rectangle de taille 1920*1080 dans lequel on crée une pente à l'aide d'une droite.
Un cube orange descend petit à petit la pente pour arriver sur le plat.                 

```c

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
```
### Vidéo

<p style="text-align: center;"><iframe width="80%" height="315" src="https://www.youtube.com/embed/0oiR6EIlI3Q" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></p>

## LEGER Bertrand

### Explication et Code

Principe
Faire afficher une fenêtre, mettre le fond de la fenêtre en bleu fonçé 
Faire apparaître des lignes, représentant la pluie, qui apparaissent aléatoirement
Rajouter des cercles au point d'impact pour faire un effet d'eau touchant de l'eau

```c
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
```

### Vidéo

<p style="text-align: center;"><iframe width="80%" height="315" src="https://www.youtube.com/embed/3bOyuSg8Ctk" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></p>


# Animation avec Texture

## BALLEJOS Lilian

### Explication et Code

Placement d'une image de fond de nuage en mouvement qui va de gauche à droite et se replace à gauche quand elle va déborder !
J'ai ensuite posé une texture de sol **très** inspirée de l'univers d'un plombier Italien rouge.
Ensuite j'affiche frame par frame un oiseau qui traverse l'écran de gauche à droite !

```c
// placement fond
void placementTexture(SDL_Texture *my_texture, SDL_Window *window,
                      SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},
        window_dimensions = {0},
        destination = {0};

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

void anim(SDL_Texture *ciel,
          SDL_Window *window,
          SDL_Renderer *renderer,
          SDL_Texture *sol,
          SDL_Texture *oiseau)
{

    /* perso*/
    SDL_Rect
        source2 = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions2 = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination2 = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state2 = {0};             // Rectangle de la vignette en cours dans la planche

    SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                      &window_dimensions2.w,
                      &window_dimensions2.h);

    SDL_QueryTexture(oiseau, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &source2.w, &source2.h);

    printf("dim image %d %d\n", source2.w, source2.h);

    int nb_images = 5;
    int offset_x = source2.w / nb_images, // 5 frame par ligne
        offset_y = source2.h / 3;         // 3 lignes

    state2.x = 0;
    state2.y = 0; // premiere ligne
    state2.w = offset_x;
    state2.h = offset_y;

    printf("offeset %d %d\n", offset_x, offset_y);

    destination2.w = offset_x;
    destination2.h = offset_y;
    destination2.y = (window_dimensions2.h / 2) - destination2.h; // La course se fait en milieu d'écran (en vertical)

    printf("destination H et W %d %d\n", destination2.w, destination2.h);

    /* fond */
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre

    SDL_QueryTexture(ciel, NULL, NULL,
                     &source.w,
                     &source.h); // Récupération des dimensions de l'image

    float zoom = 1.5;                // Facteur de zoom entre l'image source et l'image affichée pour fond
    destination.w = source.w * zoom; // On applique le zoom sur la largeur
    destination.h = source.h * zoom; // On applique le zoom sur la hauteur
    destination.x = -source.w / 2;   // au depart a droite

    int speed = 12; // vitesse de déplacement
    int x = 0;      // depart oiseau
    SDL_bool program_on = SDL_TRUE;
    SDL_Event event;

    while (program_on)
    {

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                program_on = SDL_FALSE;
                break;

            default:
                break;
            }
        }
        /*animation*/
        x += speed;
        if (destination.x > 0) // on atteind le bout de l'image le fond retourne a sa place
        {
            destination.x = -source.w / 2;
        }
        else
        {
            destination.x += 10;
        }
        destination2.x = x;
        state2.x += offset_x;  // On passe à la vignette suivante dans l'image
        state2.x %= source2.w; // On réinitialise à 0 si on dépasse la largeur

        printf("etat %d %d\n", state2.x, state2.y);
        printf("destination %d %d\n", destination2.x, destination2.y);

        SDL_RenderClear(renderer);                                // Effacer l'image précédente
        SDL_RenderCopy(renderer, ciel, &source, &destination);    // Préparation de l'affichage
        placementTexture(sol, window, renderer);                  // Afficher le sol
        SDL_RenderCopy(renderer, oiseau, &state2, &destination2); // personnage
        SDL_RenderPresent(renderer);                              // Affichage de la nouvelle image
        SDL_Delay(30);
        if(x > window_dimensions.w)
            program_on = !program_on;
    }
}
```

### Vidéo

<p style="text-align: center;"><iframe width="80%" height="315" src="https://www.youtube.com/embed/XjAD57nNzGw" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></p>

## LEGER Bertrand

### Explication et Code

Principe  : afficher le ciel en fond, le panier à droite et faire arriver le ballon de basket (en le faisant tourner) dans le panier avec un arc parabolique typique d'un tir de basketball.

### Vidéo