#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Config.h"

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

/*void ChangeEtat(int **tab, int FenetreW, int FenetreH, int x, int y, int nbLigne, int nbColonne, SDL_bool enJeu)
{
    if (x > 0 && x < FenetreW && y > 25 && y < FenetreH)
    {

        int colonneTab = x / (FenetreW / nbColonne);
        int ligneTab = (y - 25) / (FenetreH / nbLigne);
        if (!enJeu)
        {
            if (tab[ligneTab][colonneTab] == 1)
                tab[ligneTab][colonneTab] = 0;
            else
                tab[ligneTab][colonneTab] = 1;
        }
    }
}*/

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
            SDL_RenderFillRect(renderer, &element_grillage);

            if (plateau[i][j])
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

/*explosion de defaite*/
void GenereTabExplosion(SDL_Rect etats[25], SDL_Texture *explosion){
    SDL_Rect planche = {0};
    SDL_QueryTexture(explosion, NULL, NULL, &planche.w, &planche.h);
    int offsetX = planche.w / 5;
    int offsetY = planche.h / 5; //5 lignes et 5 colonnes
    int indice = 0;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
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
    int score = 0;
    SDL_Rect etats[25]; //les explosions pour la mort
    GenereTabExplosion(etats, explosion);

    int test_explo = 0;
    SDL_Rect test = {400, 440, FENETREWIDTH * TAILLE_EXPLOSION / DIMENSION_TAB_JEU, (FENETREHEIGHT - TAILLE_MENU) * TAILLE_EXPLOSION / DIMENSION_TAB_JEU};

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
                case SDLK_SPACE:
                    break;
                case SDLK_LEFT:
                    break;
                case SDLK_RIGHT:
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN: // Click souris
                if (SDL_GetMouseState(NULL, NULL) &
                    SDL_BUTTON(SDL_BUTTON_LEFT))
                { // clique droit
                    printf("%d %d\n", event.button.x, event.button.y);
                }
                break;
            default: // poubelle à événement inutile
                break;
            }
        }
        // fonction
        score++;
        AffichageGrillage(renderer, pomme, plateau);
        AffichageMenu(renderer, font, logoMenu, meilleurScore, score);
        if(test_explo < 25){
            Explosion(renderer, explosion,test , test_explo, etats);
            printf("%d\n", test_explo);
            test_explo++;
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(50); // depend pour fps avec horloge
    }
}
