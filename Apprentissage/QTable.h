#ifndef QTABLE_H
#define QTABLE_H

typedef struct etat
{
    int nord_sud;
    int ouest_est;

} etat_t;

typedef struct etatAutour
{
    int caseHaut;
    int caseBas;
    int caseDroite;
    int caseGauche;
} etatAutour;

void MainApprentissage(int nbIteration, int **serpent, int **plateau);
void posPommeAvecCo(int **plateau, int **serpent, int tailleSerpent, int teteSerpent, int *posI, int *posJ);
void AfficherQTAble(double Q[NBRE_ETATS_APPRENTISSAGE][NBRE_ACTION_APPRENTISSAGE][NBRE_ETAT_AUTOUR], int ligne, int colonne, int profondeur);
void RecupQtable(double Q[NBRE_ETATS_APPRENTISSAGE][NBRE_ACTION_APPRENTISSAGE][NBRE_ETAT_AUTOUR], int nbLigne, int nbColonne, int profondeur);
int UtilisationQTable(int teteSi, int teteSj, int pommeI, int pommeJ, double QTable[NBRE_ETATS_APPRENTISSAGE][NBRE_ACTION_APPRENTISSAGE][NBRE_ETAT_AUTOUR],
                      int **serpent, int **plateau, int *taille_serpent, int *teteSerpent);
void RecupQtable(double Q[NBRE_ETATS_APPRENTISSAGE][NBRE_ACTION_APPRENTISSAGE][NBRE_ETAT_AUTOUR], int nbLigne, int nbColonne, int profondeur);

#endif
