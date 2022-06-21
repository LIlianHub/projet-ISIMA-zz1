#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MASQUE 9

/*Création tableau*/

int ** creer_tableau(int nb_lignes, int nb_colonnes)
{
    int ** tableau = (int**)malloc(nb_lignes * sizeof(int *));
    int i;
    for (i = 0; i < nb_lignes; i++)
    {
        tableau[i] = (int *)calloc(nb_colonnes, sizeof(int));
    }
    return tableau;
}

/*LIberation tableau*/

void liberer_tableau(int ** tableau, int nb_lignes)
{
    int i;
    for (i = 0; i < nb_lignes; i++)
    {
        free(tableau[i]);
    }
    free(tableau);
}



void afficher_tableau(int ** tableau, int nb_lignes, int nb_colonnes)
{
    int i, j;
    for (i = 0; i < nb_lignes; i++)
    {
        for (j = 0; j < nb_colonnes; j++)
        {
            printf("%d ", tableau[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}




int nbvoisins(int ** moment_t, int ligne, int colonne){

  int i,j;
  int nbre = 0;

  for (i = ligne - 1 ; i < ligne + 2 ; i++){

    for(j = colonne - 1 ; j < colonne + 2 ; j++){

      if(!(i == 1 && j == 1) && (moment_t[i][j] == 1)){

	nbre+= 1;
	
      }
    }   
  }
  return nbre;
}


/*Besoin de mettre une couche 0 autour du tableau donc prévoir une dimension en plus à l'initialisation*/
void iterationReel(int **moment_t , int ** moment_t1, int nb_lignes, int nb_colonnes,
		   int masqueVie[TAILLE_MASQUE],
		   int masqueMort[TAILLE_MASQUE])
{
  
  int i, j, m;
  int resultat = 0;
  for (i = 1; i < nb_lignes - 1 ; i++){

    for (j = 1; j < nb_colonnes - 1 ; j++){

      if(moment_t[i][j] == 1)
	{
	  
	  for(m = 0; m < TAILLE_MASQUE ; m++){
	    
	    if ( masqueVie[m] == 1 && nbvoisins(moment_t, i, j) == m){

	      resultat += 1; //son nombre de voisin est dans le masque de la Vie, il survit
	      
	    }
	  
	  }
	  if(resultat != 0){ moment_t1[i][j] = 1;}
	}
      else
	{
	  for(m = 0; m < TAILLE_MASQUE ; m++){
	    
	    if ( masqueMort[m] == 1 && nbvoisins(moment_t, i, j) == m){

	      resultat += 1; //son nombre de voisin est dans le masque de la Mort, il ressuscite
	      
	    }
	  
	  }
	  if(resultat != 0){ moment_t1[i][j] = 1;}
	}
    }
  }
  int ** tmp = moment_t;
  moment_t = moment_t1;
  moment_t1 = tmp;
  afficher_tableau(moment_t,nb_lignes, nb_colonnes);
  afficher_tableau(moment_t1,nb_lignes, nb_colonnes);
}


int main(){
  int masqueVie[TAILLE_MASQUE] = {0,1,0,0,0,0,1,0,0};
  int masqueMort[TAILLE_MASQUE] = {1,0,0,0,0,0,0,0,0};

  int nb_lignes = 10;
  int nb_colonnes = 10;

  int ** tableau = creer_tableau(nb_lignes, nb_colonnes);
  int ** tableau_t1 = creer_tableau(nb_lignes, nb_colonnes);
  afficher_tableau(tableau, nb_lignes, nb_colonnes);
  for(int i = 0; i< 10; i++){
    iterationReel(tableau,tableau_t1,nb_lignes,nb_colonnes,masqueVie,masqueMort);
  }
  liberer_tableau(tableau, nb_lignes);
  return 1;
}




