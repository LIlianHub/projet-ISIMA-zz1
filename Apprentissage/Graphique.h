#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

void GestionEvenement(SDL_Renderer *renderer, TTF_Font *font,
                      int **position, int **plateau,
                      int meilleurScore, SDL_Texture *logoMenu,
                      SDL_Texture *pomme, SDL_Texture *explosion, SDL_Texture *table_serpent, SDL_Texture *menu);
void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer,
             TTF_Font *font, SDL_Texture *logo,
             SDL_Texture *pomme, SDL_Texture *explosion, SDL_Texture *table_serpent, SDL_Texture *menu);

void Initialisation(SDL_bool *enJeu, SDL_bool *depart, int *iter_explo, int **serpent, int **plateau, int *taille_serpent,
                    int *direction, int *infoIter, int *etat_markov, int *vitesse_markov, int *score, int *multiplicateur, long *lastTick,
                    int *teteSerpent, int *nbItePosMur, SDL_bool *dansJeu, SDL_bool *dansMenu);
void PassageTableauCoor(int i, int j, int *x, int *y);

extern int vitesseParEtat[5];

#endif

