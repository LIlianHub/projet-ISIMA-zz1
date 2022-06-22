#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);
void GestionEvenement(SDL_Window * window, SDL_Renderer * renderer, TTF_Font * font, int ** position, int ** plateau);


#endif