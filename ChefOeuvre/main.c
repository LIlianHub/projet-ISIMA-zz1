#include <stdio.h>
#include <stdlib.h>


/*
 *tableau de markov qui va contient les probabilités 
 *de passer entre les différents états :
 *vitesse/2 : indice 0 , 
 *vitesse   : indice 1 , 
 *vitesse*2 : indice 2 ,
 *vitesse*3 : indice 3 ,
 *endormi   : indice 4
*/


float markov [5][5] = {{ 0.15,   0.5, 0.25,    0,   0.1},
		       { 0.1 ,   0.4,  0.3, 0.15,  0.05},
		       {0.025,  0.15,  0.5,  0.3, 0.025},
		       {0.075, 0.075, 0.15,  0.4,   0.3},
		       {  0.3,     0,    0,    0,   0.7}}; 

// passer d'un état à un autre


int  meilleurScore(int ScoreActuel){
  
  int MeilleurScore;
  char PremiereLigne[10];
  
  FILE * score = fopen("score.txt","r+");

  MeilleurScore = atoi(fgets(PremiereLigne, 10, score));

  if (MeilleurScore < ScoreActuel){

    MeilleurScore = ScoreActuel;
    rewind(score);
    fprintf(score,"%d",MeilleurScore);
    
  }
  
  fclose(score);
    
  return MeilleurScore;
}



int main (){  

  printf("%d",meilleurScore(5));
  
  return 0;
}
