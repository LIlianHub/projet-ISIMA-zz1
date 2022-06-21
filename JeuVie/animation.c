#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer,
             TTF_Font *font)
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


    TTF_Quit();
    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

/*Menu*/

void GenereMenu(SDL_Window *window, SDL_Renderer *renderer, int FenetreW, int FenetreH, TTF_Font *FontTitre)
{
    SDL_RenderClear(renderer);

    /*FOnd blanc*/
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect fond;
    fond.x = 0;        // x haut gauche du rectangle
    fond.y = 0;        // y haut gauche du rectangle
    fond.w = FenetreW; // sa largeur (w = width)
    fond.h = FenetreH;
    SDL_RenderFillRect(renderer, &fond);

    /*Texte*/
    SDL_Color color = {0, 0, 0, 255};                                              // la couleur du texte
    SDL_Surface *text_surface = NULL;                                              // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(FontTitre, "Menu Jeu de la Vie", color); // création du texte dans la surface
    if (text_surface == NULL)
        end_sdl(0, "Can't create text surface", window, renderer, FontTitre);

    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL)
        end_sdl(0, "Can't create texture from surface", window, renderer, FontTitre);
    SDL_FreeSurface(text_surface); // la texture ne sert plus à rien

    SDL_Rect pos = {FenetreW / 10, 0, 0, 0};     // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);         // Ecriture du texte dans le renderer
    SDL_DestroyTexture(text_texture);                           // On n'a plus besoin de la texture avec le texte

    /* Boutons */



}