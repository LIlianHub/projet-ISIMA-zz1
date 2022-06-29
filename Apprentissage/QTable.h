#ifndef QTABLE_H
#define QTABLE_H

typedef struct etat
{
    int nord_sud;
    int ouest_est;
} etat_t;



etat_t * genereTableauEtat();
void MainApprentissage(int nbIteration, int **serpent, int **plateau);
int UtilisationQTable(int teteSi, int teteSj, int pommeI, int pommeJ, double ** Qtable);
void LibererTabFloat(double **tab, int nb_ligne);
double **GenereTabFloat(int nb_ligne, int nb_colonne);
void RecupQtable(double **Q, int nbLigne, int nbColonne);
void posPommeAvecCo(int **plateau, int **serpent, int tailleSerpent, int teteSerpent, int *posI, int *posJ);

#endif
