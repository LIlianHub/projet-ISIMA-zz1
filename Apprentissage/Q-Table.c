#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define DIMENSION_TAB_JEU 10
#define NBRE_ETATS 9
#define GAMMA 0.5




typedef struct etat{
  int nord_sud;
  int ouest_est;
}etat;


void genereTableauEtat(etat * liste_etats)
{
    liste_etats = (etat *)malloc(sizeof(etat) * 9);
    liste_etats[0].nord_sud = -1;
    liste_etats[0].ouest_est = -1;
    liste_etats[1].nord_sud = -1;
    liste_etats[1].ouest_est = 0;
    liste_etats[2].nord_sud = -1;
    liste_etats[2].ouest_est = 1;
    liste_etats[3].nord_sud = 0;
    liste_etats[3].ouest_est = -1;
    liste_etats[4].nord_sud = 0;
    liste_etats[4].ouest_est = 0;
    liste_etats[5].nord_sud = 0;
    liste_etats[5].ouest_est = 1;
    liste_etats[6].nord_sud = 1;
    liste_etats[6].ouest_est = -1;
    liste_etats[7].nord_sud = 1;
    liste_etats[7].ouest_est = 0;
    liste_etats[8].nord_sud = 1;
    liste_etats[8].ouest_est = 1;
}

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
 *                                       Q_Table       |     Haut      |     Bas       |    Droite     |    Gauche     |
 *                   ---------------------------------------------------------------------------------------------------
 * orientation :    état0: S-E           (-1,-1)       |               |               |               |               |
 *                  état1: S             (-1,0 )       |               |               |               |               |
 *                  état2: S-O           (-1,1 )       |               |               |               |               |
 *    ETATS         état3: E             ( 0,-1)       |               |               |               |               |
 *   (9 états)      état4:               ( 0,0 )       |               |               |               |               |
 *                  état5: O             ( 0,1 )       |               |               |               |               |
 *                  état6: N-E           ( 1,-1)       |               |               |               |               |
 *                  état7: N             ( 1,0 )       |               |               |               |               |
 *                  état8: N-O           ( 1,1 )       |               |               |               |               |
 */

/* un épisode est une partie
 * 
 * les états sont composés de (nord(1)/memeHauteur(0)/sud(-1),ouest(1)/memeColonne(0)/est(-1)) = les différents composants sont des bools (ex :
 * nord =1 si la pomme est au nord par rapport à la tête du serpent et =-1 si la pomme est au sud )
 *
 * les actions sont   : Haut(0), Bas(1), Droite(2), Gauche(3)
 *
 */



etat calculEtat(int pos_x_tete, int pos_y_tete, int pos_x_pomme, int pos_y_pomme)
{
  etat etatActuel;

  if(pos_x_tete < pos_x_pomme)    //la pomme est à l'est de la la tête
    {
      etatActuel.ouest_est = -1;
    }
  else if(pos_x_tete > pos_x_pomme) // A l'ouest
    {
      etatActuel.ouest_est = 1;
    }
  else
    {
      etatActuel.ouest_est = 0; // sur la même colonne
    }

  
  if(pos_y_tete < pos_y_pomme) // La pomme est au sud de la tête
    {
      etatActuel.nord_sud = -1;
    }
  else if(pos_y_tete > pos_y_pomme) // Au nord
    {
      etatActuel.nord_sud = 1;
    }
  else
    {
      etatActuel.nord_sud = 0; //même ligne
    }

  
  return etatActuel;
}



int EtatActuel(int teteSx, int teteSy, int pommex, int pommey)
{
    int directionX = teteSx - pommex; // si positif : ouest sinon est
    int directionY = teteSy - pommey; // si positif : nord sinon su
    int etat = 4;

    if (directionX > 0) // ouest
    {
        if (directionY > 0)
        {
            etat = 8; // nord ouest
        }
        else if (directionY < 0)
        {
            etat = 2; // sud ouest
        }
        else
        {
            etat = 5; // ouest
        }
    }
    else if (directionX < 0) // est
    {
        if (directionY > 0)
        {
            etat = 6; // nord est
        }
        else if (directionY < 0)
        {
            etat = 0; // sud est
        }
        else
        {
            etat = 3; // est
        }
    }
    else // juste nord ou sud
    {
        if (directionY > 0)
        {
            etat = 7; // nord
        }
        else if (directionY < 0)
        {
            etat = 1; // sud
        }
        else
        {
            etat = 4; // sur la pomme
        }
    }

    return etat;
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
	      actionActuel = 0;
	    }
	  else
	    {
	      actionActuel = 1;
	    }
	}
      else                                                 // sinon ce sera la colonne
	{
	  if(etatActuel.ouest_est > 0)
	    {
	      actionActuel = 3;
	    }
	  else
	    {
	      actionActuel = 2;
	    }
	}
      
    }
  else if(abs(etatActuel.nord_sud) == 1 )                  //bonne colonne - mauvaise ligne
    {
      if(etatActuel.nord_sud > 0)
	{
	  actionActuel = 0;
	}
      else
	{
	  actionActuel = 1;
	}
    }
  else if (abs(etatActuel.ouest_est) == 1)                 //bonne ligne - mauvaise colonne
    {
      if(etatActuel.ouest_est > 0)
	{
	  actionActuel = 3;
	}
      else
	{
	  actionActuel = 2;
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





void explorationSerpent(int *pos_x_tete, int *pos_y_tete, int *pos_x_pomme, int *pos_y_pomme, int *
   			listeEtats , int * listeActions, int * listeRecompense, int tailleMax, int *taille_serpent,
			int **plateau, int ** serpent, float ** Q_Table, etat * liste_etats)
{
  int i = 0;
  float epsilon = 0.1;
  float gamma  = 0;
  int fin = 0;
  int max = 0;
  int tmp, j;
  
  while(i < tailleMax)
    {
      listeEtats[i] = EtatActuel(*pos_x_tete, *pos_y_tete, *pos_x_pomme, *pos_y_pomme);
      
      listeActions[i] = quelAction( liste_etats [ listeEtats [i] ] );
      tmp = TestDeplacement(serpent,listeActions[i],taille_serpent, plateau, pos_x_tete, pos_y_tete);

      if(tmp == 2)
	{
	  listeRecompense [i] = 0;
	}
      else if(tmp == 1)
	{
	  listeRecompense [i] = 1 ; 
	}
      else
	{
	  listeRecompense [i] = -1;
	  fin = i;
	  i = tailleMax;
	}
      i ++;
    }
  if(i == tailleMax) {
    //veut dire que l'on s'est arrété parce que on a dépassé la tailleMax d'états
    //on alloue aussi mais avec un epsilon epsilon (moins représentatif)
    fin = tailleMax ;
    epsilon = 0.05;
  }

  //       ===> On update la Q_Table avec les états 
  Q_Table[listeEtats[fin - 1]] [listeActions[fin -1]] += epsilon * (listeRecompense[fin -1] -
  Q_Table[listeEtats[fin - 1]] [listeActions[fin -1]]);

  for ( i = fin -2 ; i >= 0 ; i ++ )
    {
      for( j = 0 ; j < 4 ; j++ )
	{
	  if (max < Q_Table[listeEtats[i+1]][j])
	    {
	      max  = Q_Table[listeEtats[i+1]][j];
	    }
	  Q_Table[listeEtats[i]][listeActions[i]] += epsilon * (listeRecompense[i] + (gamma * max) - Q_Table[listeEtats[i]][listeActions[i]]);
	    
	}

      
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
  etat * liste_etats;
  genereTableauEtat(liste_etats);

  
  return 0;
  }
