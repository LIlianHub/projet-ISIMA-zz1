#ifndef GRAPHIQUEENJEU_H
#define GRAPHIQUEENJEU_H

void AffichageLogo(SDL_Renderer *renderer, SDL_Texture *my_texture);
void AffichageScore(SDL_Renderer *renderer, TTF_Font *police, int score, int meilleurScore);
void AffichageMenuJeu(SDL_Renderer *renderer, TTF_Font *police, SDL_Texture *logo, int meilleurScore, int score);
void AffichagePomme(SDL_Renderer *renderer, SDL_Texture *pomme, SDL_Rect pos);
void AffichageGrillage(SDL_Renderer *renderer, SDL_Texture *pomme, int **plateau, SDL_Rect etats_serpent[6][16], SDL_Texture *table_serpent);
void PlaceTeteSerpent(SDL_Renderer *renderer, int direction, SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16], SDL_Rect pos, int etat);
void PlaceCorpsSerpent(SDL_Renderer *renderer, int courant, SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16], SDL_Rect pos, int **serpent);
void PlaceQueueSerpent(SDL_Renderer *renderer, int courant, SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16], SDL_Rect pos, int **serpent);
void AffichageSerpent(int **serpent, SDL_Renderer *renderer, int taille_serpent, int teteSerpent, int direction, SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16], int etat);
void Explosion(SDL_Renderer *renderer, SDL_Texture *explosion, SDL_Rect pos, int etat, SDL_Rect etats[25]);
void IterEnJeu(SDL_bool *depart, long *lastTick, int *infoIter, int *iter_explo, int *meilleurScore, int *score, SDL_bool *enJeu, int *etat_markov, int *vitesse_prog,
               int *multiplicateur, int *nbItePosMur, int *direction, int **serpent, int **plateau, int *taille_serpent, int *teteSerpent, SDL_Texture *explosion, SDL_Rect etats[25],
               SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16], SDL_Renderer *renderer, SDL_Rect *pos_explosion, SDL_bool *dansJeu, SDL_bool *dansMenu, int *posPommeI, int *posPommeJ, int * IterPourDimSerp);

#endif