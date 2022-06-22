/*Affichage Graphique à chaque itération*/

/*void Affichage(SDL_Window *window, SDL_Renderer *renderer, int FenetreW, int FenetreH, TTF_Font *FontTitre, int masque1[9], int masque2[9], int mode, int **tab, int TabW, int TabH, int stagne)
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

    /*option*/

    /*masque*/

    SDL_Rect pos2 = {FenetreW / 5, 0, 20, 25};

    for (int i = 0; i < 9; i++)
    {
        if (masque1[i] == 1)
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        SDL_RenderFillRect(renderer, &pos2);
        pos2.x += 30;
    }

    pos2.x += 40;

    for (int i = 0; i < 9; i++)
    {
        if (masque2[i] == 1)
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        SDL_RenderFillRect(renderer, &pos2);
        pos2.x += 30;
    }

    // texte mode
    SDL_Surface *text_surface2 = NULL; // la surface  (uniquement transitoire)
    SDL_Color color = {0, 0, 0, 255};

    if (mode == 1)
    {
        text_surface2 = TTF_RenderText_Blended(FontTitre, "Mode : Tor", color); // création du texte dans la surface
    }
    else
    {
        text_surface2 = TTF_RenderText_Blended(FontTitre, "Mode : Limite", color); // création du texte dans la surface
    }

    if (text_surface2 == NULL)
        end_sdl(0, "Can't create text surface", window, renderer, FontTitre);

    SDL_Texture *text_texture2 = NULL;                                     // la texture qui contient le texte
    text_texture2 = SDL_CreateTextureFromSurface(renderer, text_surface2); // transfert de la surface à la texture
    if (text_texture2 == NULL)
        end_sdl(0, "Can't create texture from surface", window, renderer, FontTitre);
    SDL_FreeSurface(text_surface2); // la texture ne sert plus à rien

    SDL_Rect pos3 = {5, 0, 0, 0};
    SDL_QueryTexture(text_texture2, NULL, NULL, &pos3.w, &pos3.h); // récupération de la taille (w, h) du texte
    SDL_RenderCopy(renderer, text_texture2, NULL, &pos3);          // Ecriture du texte dans le renderer
    SDL_DestroyTexture(text_texture2);                             // On n'a plus besoin de la texture avec le texte

    /*tableau*/

    SDL_Rect pos4 = {0, 25, FenetreW / TabW, (FenetreH - 25) / TabH};

    for (int i = 0; i < TabH; i++)
    {
        for (int j = 0; j < TabW; j++)
        {
            if (tab[i][j] == 0)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                // printf("%d %d\n", pos4.x, pos4.y);
            }
            SDL_RenderFillRect(renderer, &pos4);

            pos4.x += FenetreW / TabW;
        }
        pos4.y += (FenetreH - 25) / TabH;
        pos4.x = 0;
    }

    /*info stagne*/

    if (stagne)
    {

        SDL_Surface *text_surface3 = NULL; // la surface  (uniquement transitoire)

        SDL_Color color2 = {255, 0, 0, 255};

        text_surface3 = TTF_RenderText_Blended(FontTitre, "On stagne !", color2); // création du texte dans la surface

        if (text_surface3 == NULL)
            end_sdl(0, "Can't create text surface", window, renderer, FontTitre);

        SDL_Texture *text_texture3 = NULL;                                     // la texture qui contient le texte
        text_texture3 = SDL_CreateTextureFromSurface(renderer, text_surface3); // transfert de la surface à la texture
        if (text_texture3 == NULL)
            end_sdl(0, "Can't create texture from surface", window, renderer, FontTitre);
        SDL_FreeSurface(text_surface3); // la texture ne sert plus à rien

        SDL_Rect pos3 = {5, 775, 0, 0};
        SDL_QueryTexture(text_texture3, NULL, NULL, &pos3.w, &pos3.h); // récupération de la taille (w, h) du texte
        SDL_RenderCopy(renderer, text_texture3, NULL, &pos3);          // Ecriture du texte dans le renderer
        SDL_DestroyTexture(text_texture3);                             // On n'a plus besoin de la texture avec le texte
    }
}

*/