#ifndef ALGORITHME_H
#define ALGORITHME_H

int ** TAB1;
int ** TAB2;
#define TAILLE_MASQUE 9

void EcritureConfig(int **tab, int ligne, int colonne);
void LectureFichier(int **tab, int ligne, int colonne);
void ClearTab(int **tab, int ligne, int colonne);
int **creer_tableau(int nb_lignes, int nb_colonnes);
void liberer_tableau(int **tableau, int nb_lignes);
void afficher_tableau(int **tableau, int nb_lignes, int nb_colonnes);
void iterationReelLimite(int nb_lignes, int nb_colonnes,
                   int masqueVie[TAILLE_MASQUE],
                   int masqueMort[TAILLE_MASQUE]);
void VieTore(int B[TAILLE_MASQUE], int S[TAILLE_MASQUE], int NbLignes,int NbColonnes);
int TestStagne(int ligne, int colonne);

#endif
