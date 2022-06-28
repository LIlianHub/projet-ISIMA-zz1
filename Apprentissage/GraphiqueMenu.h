#ifndef GRAPHIQUEMENU_H
#define GRAPHIQUEMENU_H

void IterMenu(SDL_Renderer *renderer, SDL_Texture *menu);
int DetectBoutonMenu(float x, float y);
void OverBoutonMenu(SDL_Renderer *renderer, float x, float y);
void ChoixMenu(float x, float y, SDL_bool *dansJeu, SDL_bool *dansMenu, SDL_bool *enJeu, SDL_bool *depart, int *iter_explo, int **serpent, int **plateau, int *taille_serpent,
               int *direction, int *infoIter, int *etat_markov, int *vitesse_markov, int *score, int *multiplicateur, long *lastTick, int *teteSerpent, int *nbItePosMur);

#endif