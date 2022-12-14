#ifndef ALGORITHME_H
#define ALGORITHME_H

int **creer_tableau(int nb_lignes, int nb_colonnes);
void liberer_tableau(int **tableau, int nb_lignes);
void afficher_tableau(int **tableau, int nb_lignes, int nb_colonnes);
void InitialisationSerpent(int **tableau, int *tailleSerpent);
void decalagedroite(int **serpent, int direction, int aManger, int *taille_serpent);
void InitPlateau(int **plateau);
int TestDeplacement(int **serpent, int direction, int *taille_serpent, int **plateau, int *teteSerpent);
int MeilleurScore(int ScoreActuel);
int passageMarkov(int EtatPrec);
void posMuret(int **plateau, int **serpent, int tailleSerpent, int teteSerpent);
void ClearMap(int ** plateau);
int TestCollisionSerpent(int **serpent, int TeteI, int TeteJ, int *taille_serpent, int *teteSerpent);
void posPommeAvecCo(int **plateau, int **serpent, int tailleSerpent, int teteSerpent, int *posI, int *posJ);
void DiminueSerpent(int *tailleserpent);

#endif