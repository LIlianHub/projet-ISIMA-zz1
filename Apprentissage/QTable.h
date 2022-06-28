#ifndef QTABLE_H
#define QTABLE_H

typedef struct etat
{
    int nord_sud;
    int ouest_est;
} etat_t;


etat_t * genereTableauEtat();
void MainApprentissage(etat_t *listeEtat, int nbIteration, int **serpent, int **plateau);

#endif