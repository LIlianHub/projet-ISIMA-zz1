#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define DIMENSION_TAB_JEU 10
#define NBRE_ETATS 16
#define ALPHA 0.1
#define LAMBDA 10



typedef struct etat{
  int nord_sud;
  int ouest_est;
}etat;


void afficher_tableau(float **tableau, int nb_lignes, int nb_colonnes)
{
  int i, j;
  for (i = 0; i < nb_lignes; i++)
    {

      for (j = 0; j < nb_colonnes; j++)
        {
	  printf("%f ", tableau[i][j]);
        }
      printf("\n");
    }
  printf("\n");
}
float **creer_tableau(int nb_lignes, int nb_colonnes)
{
  float **tableau = (float **)malloc(nb_lignes * sizeof(float *));
  int i;
  for (i = 0; i < nb_lignes; i++)
    {
      tableau[i] = (float *)calloc(nb_colonnes, sizeof(float));
    }
  return tableau;
}

void liberer_tableau(int **tableau, int nb_lignes)
{
  int i;
  for (i = 0; i < nb_lignes; i++)
    {
      free(tableau[i]);
    }
  free(tableau);
}


/*La Q_Table : 
 *elle est de la forme :                                                  ACTIONS
 *                             Q_Table       |     Gauche    |     Droite    |      Bas      |    Haut     |
 *                   -----------------------------------------------------------------------------------------
 * orientation :    état0:     (-1,-1)       |               |               |               |               |
 *                  état1:     (-1,0 )       |               |               |               |               |
 *                  état2:     (-1,1 )       |               |               |               |               |
 *    ETATS         état3:     ( 0,-1)       |               |               |               |               |
 *   (9 états)      état4:     ( 0,0 )       |               |               |               |               |
 *                  état5:     ( 0,1 )       |               |               |               |               |
 *                  état6:     ( 1,-1)       |               |               |               |               |
 *                  état7:     ( 1,0 )       |               |               |               |               |
 *                  état8:     ( 1,1 )       |               |               |               |               |
 */

/* un épisode est une partie
 * 
 * les états sont composés de (nord(1)/memeHauteur(0)/sud(-1),ouest(1)/memeColonne(0)/est(-1)) = les différents composants sont des bools (ex :
 * nord =1 si la pomme est au nord par rapport à la tête du serpent et =-1 si la pomme est au sud )
 *
 * les actions sont  : gauche(0), droite(1), bas(2), haut(3)
 *
 *
 */



etat calculEtat(int pos_x_tete, int pos_y_tete, int pos_x_pomme, int pos_y_pomme)
{
  etat etatActuel;

  if(pos_x_tete < pos_x_pomme)
    {
      etatActuel.ouest_est = -1;
    }
  else if(pos_x_tete > pos_x_pomme)
    {
      etatActuel.ouest_est = 1;
    }

  
  if(pos_y_tete < pos_y_pomme)
    {
      etatActuel.nord_sud = -1;
    }
  else if(pos_y_tete > pos_y_pomme)
    {
      etatActuel.nord_sud = 1;
    }
  else
    {
      etatActuel.nord_sud = 0;
    }

  
  return etatActuel;
}

int quelAction (etat etatActuel)
{
  int tmp;
  int actionActuel = 4;

  if(abs(etatActuel.nord_sud + etatActuel.ouest_est) == 2) //2 directions possibles
    {
      tmp = rand()%2;                                      // représente notre proba aléatoire uniforme 
      
      if(tmp == 0)                                         // on dit que si ==0 alors on agira sur la ligne
	{
	  if(etatActuel.nord_sud > 0)
	    {
	      actionActuel = 3;
	    }
	  else
	    {
	      actionActuel = 2;
	    }
	}
      else                                                 // sinon ce sera la colonne
	{
	  if(etatActuel.ouest_est > 0)
	    {
	      actionActuel = 1;
	    }
	  else
	    {
	      actionActuel = 0;
	    }
	}
      
    }
  else if(abs(etatActuel.nord_sud) == 1 )                  //bonne colonne - mauvaise ligne
    {
      if(etatActuel.nord_sud > 0)
	{
	  actionActuel = 3;
	}
      else
	{
	  actionActuel = 2;
	}
    }
  else if (abs(etatActuel.ouest_est) == 1)                 //bonne ligne - mauvaise colonne
    {
      if(etatActuel.ouest_est > 0)
	{
	  actionActuel = 1;
	}
      else
	{
	  actionActuel = 0;
	}
    }
  return actionActuel;
}

/*explorationSerpent(pos_tete, posPomme, listeEtat, listeAction, liste recompense, Q_Table)
 *        
 *        => On calcul l'état avec la pos_tete et pos_pomme
 *                .update listeEtat        (FAIT)
 *        
 *        => le serpent va dans direction aléatoire entre toutes les directions d'état = 1 et -1
 *	          .update listeAction      (FAIT)
 *		  .update pos_tete
 *
 *	 => testDéplacement pour savoir la récompense
 *	          .update listeRecompense
 *	     	  => Si recompense = - 1  : On stoppe l'épisode
 *		  => Sinon : itération suivante
 *
 *
 *
 *        ===> On update la Q_Table avec les états
 *
 *        ___________> on répète on répère on répète pour avoir une Q_table la plus représentative
 */





void explorationSerpent(int pos_x_tete, int pos_y_tete, int pos_x_pomme, int pos_y_pomme, etat * listeEtats , int ** listeAction_Gain, int tailleMax)
{
  int i = 0;
  
  while(i < tailleMax)
    {
      listeEtats[i] = calculEtat(pos_x_tete, pos_y_tete, pos_x_pomme, pos_y_pomme);
      listeAction_Gain[i][0] = quelAction(listeEtats[i]);
      listeAction
      
      
      i ++;
    }

  
}




/*exploitationSerpent(Q_table, pos_tete, posPomme)
 *
 *             => le serpent va faire l'action avec la plus grande QValue en fonction de l'état ou
 *             il est
 *                           .update pos_tete
 *             => on recalcule l'état avec la pose_tete et posPomme
 *                           .update etat
 *             => testDeplacement pour savoir la récompense
 *                     => Si pomme touchée continuer exploitation
 *                     => Si un mur est touché, perdu 
 */


int main (){

  srand(time(NULL)); 
 
  
  return 0;
  }
