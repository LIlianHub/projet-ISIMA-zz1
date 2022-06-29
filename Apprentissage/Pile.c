#include <stdlib.h>
#include <stdio.h>

#include "Pile.h"

/*Partie PILE*/

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

void LibererPile(pile_t *pile)
{
  free(pile->base);
  free(pile);
}

int PileVide(pile_t *pile)
{
  return (pile->nb_element == 0);
}

int PilePleine(pile_t *pile)
{
  return (pile->nb_element == pile->taille);
}

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
