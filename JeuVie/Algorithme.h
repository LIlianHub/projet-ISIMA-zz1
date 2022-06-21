#ifndef ALGORITHME_H
#define ALGORITHME_H


void EcritureConfig(int **tab, int ligne, int colonne);
void LectureFichier(int **tab, int ligne, int colonne);
void ClearTab(int **tab, int ligne, int colonne);
int **creer_tableau(int nb_lignes, int nb_colonnes);
void liberer_tableau(int **tableau, int nb_lignes);
void afficher_tableau(int **tableau, int nb_lignes, int nb_colonnes);

#endif
