#ifndef PILEV2_H
#define PILEV2_H

typedef struct donnees
{
  int etat;
  int etatAutour;
  int action;
  float recompense;
  
}donnees;


typedef struct pile
{
  int taille;
  int nb_element;
  donnees * base;
}pile_t;


int initPile(pile_t **newPile, int taille);
void LibererPile(pile_t *pile);
int Empiler(pile_t *pile, donnees ajout);
int Depiler(pile_t *pile, donnees *element);
int PilePleine(pile_t *pile);
int PileVide(pile_t *pile);

#endif