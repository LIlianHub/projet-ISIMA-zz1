#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

void GestionEvenement(SDL_Renderer *renderer, TTF_Font *font,
                      int **position, int **plateau,
                      int meilleurScore, SDL_Texture *logoMenu,
                      SDL_Texture *pomme, SDL_Texture *explosion, SDL_Texture *table_serpent, SDL_Texture *menu);
void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer,
             TTF_Font *font, SDL_Texture *logo,
             SDL_Texture *pomme, SDL_Texture *explosion, SDL_Texture *table_serpent, SDL_Texture *menu);
#endif