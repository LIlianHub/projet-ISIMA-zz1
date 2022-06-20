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
✔️| BALLEJOS Lilian | Jeu de la vie
❌| BALLEJOS Lilian | Frame



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

## CORNUEZ Charlotte

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