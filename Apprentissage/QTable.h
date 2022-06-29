#ifndef QTABLE_H
#define QTABLE_H

typedef struct etat
{
    int nord_sud;
    int ouest_est;
} etat_t;

typedef struct donnees
{
  int etat;
  int action;
  float recompense;
  
}donnees;

typedef struct pile
{
  int taille;
  int nb_element;
  donnees * base;
}pile_t;



etat_t * genereTableauEtat();
void MainApprentissage(etat_t *listeEtat, int nbIteration, int **serpent, int **plateau);
int ExploitationQtable(int teteSi, int teteSj, int pommeI, int pommeJ, float ** Qtable);
void LibererTabFloat(float **tab, int nb_ligne);
float **GenereTabFloat(int nb_ligne, int nb_colonne);
void RecupQtable(float **Q, int nbLigne, int nbColonne);
void posPommeAvecCo(int **plateau, int **serpent, int tailleSerpent, int teteSerpent, int *posI, int *posJ);

#endif
