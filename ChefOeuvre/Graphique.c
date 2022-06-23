#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Config.h"
#include "Algorithme.h"

/*LIbération Propre de la SDL*/

void end_sdl(char ok,
             char const *msg,
             SDL_Window *window,
             SDL_Renderer *renderer,
             TTF_Font *font,
             SDL_Texture *logo,
             SDL_Texture *pomme,
             SDL_Texture *explosion)
{
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
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    if (font != NULL)
    {
        TTF_CloseFont(font);
        font = NULL;
    }
    if (logo != NULL)
    {
        SDL_DestroyTexture(logo);
        logo = NULL;
    }

    if (pomme != NULL)
    {
        SDL_DestroyTexture(pomme);
        pomme = NULL;
    }

    if (explosion != NULL)
    {
        SDL_DestroyTexture(explosion);
        explosion = NULL;
    }

    TTF_Quit();
    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

/*passage indice du plateau au coordonnées de la fenetre*/
void PassageTableauCoor(int i, int j, int *x, int *y)
{
    *x = j * (FENETREWIDTH / DIMENSION_TAB_JEU);
    *y = i * ((FENETREHEIGHT - TAILLE_MENU) / DIMENSION_TAB_JEU) + TAILLE_MENU;
}

/*AffichageLogoMenu*/

void AffichageLogo(SDL_Renderer *renderer, SDL_Texture *my_texture)
{
    SDL_Rect boite_logo, image;

    boite_logo.x = 0;
    boite_logo.y = 0;
    boite_logo.w = FENETREWIDTH / 3;
    boite_logo.h = TAILLE_MENU;

    image.x = 0;
    image.y = 0;
    SDL_QueryTexture(my_texture, NULL, NULL, &image.w, &image.h);

    SDL_RenderCopy(renderer, my_texture, &image, &boite_logo);
}

/*voir les tests*/
void AffichageScore(SDL_Renderer *renderer, TTF_Font *police, int score, int meilleurScore)
{
    SDL_Color colorBest = {255, 0, 0, 255};
    SDL_Color colorScore = {255, 255, 255, 255};
    SDL_Surface *surfaceBest = NULL;
    SDL_Surface *surfaceScore = NULL;
    SDL_Texture *text_best = NULL;
    SDL_Texture *text_score = NULL;

    char score_formated[255];
    char best_formated[255];

    sprintf(score_formated, "%d", score);
    sprintf(best_formated, "%d", meilleurScore);

    surfaceBest = TTF_RenderText_Blended(police, best_formated, colorBest);
    surfaceScore = TTF_RenderText_Blended(police, score_formated, colorScore);

    text_best = SDL_CreateTextureFromSurface(renderer, surfaceBest);
    text_score = SDL_CreateTextureFromSurface(renderer, surfaceScore);

    SDL_FreeSurface(surfaceBest);
    SDL_FreeSurface(surfaceScore);

    SDL_Rect posBest = {0};
    SDL_Rect posScore = {0};

    SDL_QueryTexture(text_best, NULL, NULL, &posBest.w, &posBest.h);
    SDL_QueryTexture(text_score, NULL, NULL, &posScore.w, &posScore.h);

    posBest.x = 5 * (FENETREWIDTH / 6) - posBest.w / 2;
    posScore.x = FENETREWIDTH / 2 - posScore.w / 2;

    SDL_RenderCopy(renderer, text_best, NULL, &posBest);
    SDL_RenderCopy(renderer, text_score, NULL, &posScore);

    SDL_DestroyTexture(text_best);
    SDL_DestroyTexture(text_score);
}

/*Menu en haut*/
void AffichageMenu(SDL_Renderer *renderer, TTF_Font *police, SDL_Texture *logo, int meilleurScore, int score)
{
    SDL_Rect fond_menu;
    fond_menu.x = 0;
    fond_menu.y = 0;
    fond_menu.w = FENETREWIDTH;
    fond_menu.h = TAILLE_MENU;
    SDL_SetRenderDrawColor(renderer, 183, 170, 119, 255);
    SDL_RenderFillRect(renderer, &fond_menu);
    AffichageLogo(renderer, logo);
    AffichageScore(renderer, police, score, meilleurScore);
}

/*Grille*/

void AffichagePomme(SDL_Renderer *renderer, SDL_Texture *pomme, SDL_Rect pos)
{
    SDL_Rect image = {0};
    SDL_QueryTexture(pomme, NULL, NULL, &image.w, &image.h);
    SDL_RenderCopy(renderer, pomme, &image, &pos);
}

void AffichageGrillage(SDL_Renderer *renderer, SDL_Texture *pomme, int **plateau)
{
    SDL_Rect element_grillage;
    element_grillage.x = 0;
    element_grillage.y = TAILLE_MENU;
    element_grillage.w = FENETREWIDTH / DIMENSION_TAB_JEU;
    element_grillage.h = (FENETREHEIGHT - TAILLE_MENU) / DIMENSION_TAB_JEU;

    SDL_bool variation = SDL_FALSE;
    for (int i = 0; i < DIMENSION_TAB_JEU; i++)
    {
        for (int j = 0; j < DIMENSION_TAB_JEU; j++)
        {
            if (variation)
            {
                SDL_SetRenderDrawColor(renderer, 67, 99, 7, 255);
                variation = SDL_FALSE;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 181, 223, 103, 255);
                variation = SDL_TRUE;
            }

            // si bordure
            if (plateau[i][j] == 2)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }

            SDL_RenderFillRect(renderer, &element_grillage);

            if (plateau[i][j] == 1)
            {
                AffichagePomme(renderer, pomme, element_grillage);
            }
            element_grillage.x += element_grillage.w;
        }
        element_grillage.x = 0;
        element_grillage.y += element_grillage.h;
        variation = !variation;
    }
}

void AffichageSerpent(int **serpent, SDL_Renderer *renderer, int taille_serpent)
{
    SDL_Rect element_serpent = {0};
    element_serpent.w = FENETREWIDTH / DIMENSION_TAB_JEU;
    element_serpent.h = (FENETREHEIGHT - TAILLE_MENU) / DIMENSION_TAB_JEU;
    int x, y;
    for (int j = 0; j < taille_serpent; j++)
    {
        PassageTableauCoor(serpent[j][0], serpent[j][1], &x, &y);
        element_serpent.x = x;
        element_serpent.y = y;
        SDL_SetRenderDrawColor(renderer, 90, 175, 237, 255);
        SDL_RenderFillRect(renderer, &element_serpent);
    }
}

/*explosion de defaite*/
void GenereTabExplosion(SDL_Rect etats[25], SDL_Texture *explosion)
{
    SDL_Rect planche = {0};
    SDL_QueryTexture(explosion, NULL, NULL, &planche.w, &planche.h);
    int offsetX = planche.w / 5;
    int offsetY = planche.h / 5; // 5 lignes et 5 colonnes
    int indice = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            etats[indice].w = offsetX;
            etats[indice].h = offsetY;
            etats[indice].x = j * offsetX;
            etats[indice].y = i * offsetY;
            indice++;
        }
    }
}

void Explosion(SDL_Renderer *renderer, SDL_Texture *explosion, SDL_Rect pos, int etat, SDL_Rect etats[25])
{
    /*recentrage explosion car coordonnées en haut a gauche*/
    pos.x -= pos.w / 2;
    pos.y -= pos.h / 2;
    SDL_RenderCopy(renderer, explosion, &etats[etat], &pos);
}

/*Boucle Principale de Gestion d'événement*/

void GestionEvenement(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font,
                      int **position, int **plateau,
                      int meilleurScore, SDL_Texture *logoMenu,
                      SDL_Texture *pomme, SDL_Texture *explosion)
{
    /*Variable utile*/
    SDL_bool activation = SDL_TRUE;
    SDL_Event event;

    /*Gestion animation explosion*/
    SDL_Rect etats[25];
    GenereTabExplosion(etats, explosion);
    int iter_explo = 0;
    SDL_Rect pos_explosion = {0, 0, FENETREWIDTH * TAILLE_EXPLOSION / DIMENSION_TAB_JEU, (FENETREHEIGHT - TAILLE_MENU) * TAILLE_EXPLOSION / DIMENSION_TAB_JEU};

    /*Gestion PLateau*/
    InitPlateau(plateau);

    /*Gestion Serpent*/
    InitialisationSerpent(position);
    int taille_serpent = 3;

    /*direction initiale va a droite*/
    int direction = 3;

    /*info sur le deplacement*/
    int infoIter = 2; // tout va bien

    // score en fonction du temps qui passe
    int score = 0;
    long timeDebut = SDL_GetTicks();

    while (activation)
    {
        while (SDL_PollEvent(&event)) // on vide la pile d'evenement
        {
            switch (event.type)
            {
            case SDL_QUIT: // ON quitte
                activation = SDL_FALSE;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    direction = 3;
                    break;
                case SDLK_RIGHT:
                    direction = 2;
                    break;
                case SDLK_UP:
                    direction = 0;
                    break;
                case SDLK_DOWN:
                    direction = 1;
                    break;
                default:
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN: // Click souris
                if (SDL_GetMouseState(NULL, NULL) &
                    SDL_BUTTON(SDL_BUTTON_LEFT))
                { // clique droit
                }
                break;
            default: // poubelle à événement inutile
                break;
            }
        }

        // Nettoyage render
        SDL_RenderClear(renderer);

        /*Affichage*/
        AffichageGrillage(renderer, pomme, plateau);
        AffichageMenu(renderer, font, logoMenu, meilleurScore, score);

        /*Mort serpent*/
        if (infoIter == 0) // fin de jeu
        {
            if (iter_explo == 0)
            { // premiere frame on calcul position
                int x_explo, y_explo;
                PassageTableauCoor(position[0][0], position[0][1], &x_explo, &y_explo);
                pos_explosion.x = x_explo;
                pos_explosion.y = y_explo;
            }
            if (iter_explo < 25)
            {
                Explosion(renderer, explosion, pos_explosion, iter_explo, etats);
                iter_explo++;
            }
        }

        else // on continue
        {
            // Calcul du score en fonction du temps ecoulé
            score = (SDL_GetTicks() - timeDebut) / 1000; // en mili sec donc /1000 pour sec
            infoIter = TestDeplacement(position, direction, &taille_serpent, plateau);
            AffichageSerpent(position, renderer, taille_serpent);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(100); // depend pour fps avec horloge
    }
}
