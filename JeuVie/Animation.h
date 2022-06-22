#ifndef ANIMATION_H
#define ANINMATION_H


void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);
void Affichage(SDL_Window *window, SDL_Renderer *renderer, int FenetreW, int FenetreH, TTF_Font *FontTitre, int masque1[9], int masque2[9], int mode, int **tab, int TabW, int TabH, int stagne);
void ChangeEtat(int **tab, int FenetreW, int FenetreH, int x, int y, int nbLigne, int nbColonne, SDL_bool enJeu);

#endif