#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int DIMENSION_TAB_JEU = 4;

void posPomme (int grille[4][4],
	       int serpent[2][10],
	       int tailleSerpent){

  int i, j, m;
  
  int compteur = 0;
  int caseVide;
  
  int caseDispo = ( (DIMENSION_TAB_JEU -2) * (DIMENSION_TAB_JEU - 2) ) - tailleSerpent;
  printf("caseDispo : %d\n",caseDispo);
  int placement = (rand()% caseDispo)+1 ;
  printf("placement : %d\n\n",placement);
  
  for ( i = 1 ; i < DIMENSION_TAB_JEU - 1 ; i++ ){

    for ( j = 1 ; j < DIMENSION_TAB_JEU - 1 ; j++ ){
      printf("compteur : %d\n",compteur);
      caseVide = 1;
      
      for( m = 0 ; m < tailleSerpent ; m++ ){

	if( (i == serpent[0][m] && j == serpent[1][m]) ){

	  caseVide = 0;
	  
	}
	
      }
      if( caseVide == 1 ){

	compteur ++;
	
      }
      if ( compteur == placement){

	grille[i][j] = 1;
	i = DIMENSION_TAB_JEU; // on incrémente i et j de sorte qu'on sorte de la boucle
	j = DIMENSION_TAB_JEU;
      } 
      printf("compteurFinBoucle : %d\n",compteur); 
    }

    
  }
}


int main (){
  srand(time(NULL));

  int grille[4][4] = {0}; 

  int tailleSerpent = 3;
  int serpent[2][10] = {0};
  serpent[0][0] = 1;
  serpent[1][0] = 1;
  
  serpent[0][1] = 1;
  serpent[1][1] = 2;

  serpent[0][2] = 2;
  serpent[1][2] = 1;

  printf("Serpent\n");
  for (int k = 0;k<2; k++){
    for (int l = 0; l<tailleSerpent ; l++){

      printf("%d ",serpent[k][l]);
      
    }
    printf("\n");
  }
  printf("\n");
  
  posPomme(grille, serpent, tailleSerpent);

  int i,j;

  for (i=0;i<4;i++) {

    for(j=0;j<4;j++) {

      printf("%d ",grille[i][j]);
      
    }
    
    printf("\n");
  }
  printf("\n");
  return 0;
}
