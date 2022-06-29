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



etat_t * genereTableauEtat();
void MainApprentissage(etat_t *listeEtat, int nbIteration, int **serpent, int **plateau);
int UtilisationQTable(int teteSi, int teteSj, int pommeI, int pommeJ, float ** Qtable);
void LibererTabFloat(float **tab, int nb_ligne);
float **GenereTabFloat(int nb_ligne, int nb_colonne);
void RecupQtable(float **Q, int nbLigne, int nbColonne);
void posPommeAvecCo(int **plateau, int **serpent, int tailleSerpent, int teteSerpent, int *posI, int *posJ);

#endif
