#ifndef ALGORITHME_H
#define ALGORITHME_H

#define TAILLE_MASQUE 9

void EcritureConfig(int **tab, int ligne, int colonne);
void LectureFichier(int **tab, int ligne, int colonne);
void ClearTab(int **tab, int ligne, int colonne);
int **creer_tableau(int nb_lignes, int nb_colonnes);
void liberer_tableau(int **tableau, int nb_lignes);
void afficher_tableau(int **tableau, int nb_lignes, int nb_colonnes);
void VieTore(int **tab, int **cpyTab, int vie[TAILLE_MASQUE], int mort[TAILLE_MASQUE], int ligne, int colonne);
int TestStagne(int **tab1, int **tab2, int ligne, int colonne);
void iterationLimite(int **moment_t, int **tmp, int nb_lignes, int nb_colonnes, int masqueVie[TAILLE_MASQUE], int masqueMort[TAILLE_MASQUE]);
#endif
