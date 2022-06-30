#include <stdlib.h>
#include <stdio.h>

#include "Pile.h"

/*Partie PILE*/

//on initialise la pile
int initPile(pile_t **newPile, int taille)
{
  int sortie = 1;
  *newPile = (pile_t *)malloc(sizeof(pile_t));
  if (newPile)
  {
    (*newPile)->base = (donnees *)malloc(taille * sizeof(donnees));
    if ((*newPile)->base)
    {
      (*newPile)->nb_element = 0;
      (*newPile)->taille = taille;
    }
    else
    {
      free(newPile);
      sortie = 0;
    }
  }
  else
  {
    sortie = 0;
  }
  return sortie;
}

//on libere la pile
void LibererPile(pile_t *pile)
{
  free(pile->base);
  free(pile);
}

//vrai si la pile est vide faux sinon
int PileVide(pile_t *pile)
{
  return (pile->nb_element == 0);
}

//vrai si la pile est pleine faux sinon
int PilePleine(pile_t *pile)
{
  return (pile->nb_element == pile->taille);
}

//on empile un element si c'est possible sinon on informe l'utilisateur
int Empiler(pile_t *pile, donnees ajout)
{
  int sortie = 0;
  if (!PilePleine(pile))
  {

    pile->base[pile->nb_element] = ajout;
    pile->nb_element++;

    sortie = 1;
  }
  return sortie;
}

//on depile un element si c'est possible sinon on informe l'utilisateur
int Depiler(pile_t *pile, donnees *element)
{
  int sortie = 0;
  if (!PileVide(pile))
  {
    pile->nb_element--;
    *element = pile->base[pile->nb_element];
    sortie = 1;
  }
  return sortie;
}
