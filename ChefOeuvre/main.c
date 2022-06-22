#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//nbres de règles de notre tableau de markov
int NB_ETATS = 5;

/*
 *tableau de markov qui va contient les probabilités 
 *de passer entre les différents états :
 *vitesse   : indice 0 
 *vitesse/2 : indice 1 
 *vitesse*2 : indice 2 
 *vitesse*3 : indice 3 
 *endormi   : indice 4
 */
float markov [5][5] = {{ 0.4,   0.1,   0.3,  0.15,  0.05},
		       { 0.5,  0.15,  0.25,     0,   0.1},
		       {0.14,  0.03,   0.5,   0.3,  0.03},
		       {0.08,  0.07,  0.15,   0.4,   0.3},
		       {  0,    0.3,     0,     0,   0.7}}; 





// passer d'un état à un autre
// comme tu voulais faire

int VitesseNormale = 30 ;  //la vitesse de base est 30ms

int passageMarkovLilou(int EtatPrec, int * vitesse){
  
  int i;
  int pourcentCumul= 0;
  
  int nvlEtat = EtatPrec;
  int pourcent = (rand()%101);
  for(i = 0; i < NB_ETATS ; i++){

    pourcentCumul += markov[EtatPrec][i];
    
    if(pourcent <= pourcentCumul * 100){

      nvlEtat = i ;
      i = 6;
      
    }
   
  }       

  if(nvlEtat == 0){ //etat 0 : vitesse normale

    *vitesse = VitesseNormale;
    
  }
  else if(nvlEtat == 1){ //etat 1 : vitesse/2

    *vitesse = VitesseNormale/2;
    
  }else if(nvlEtat == 2){ //etat 2 : vitesse*2

    *vitesse = VitesseNormale*2;
    
  }else if(nvlEtat == 3){ //etat 3 : vitesse*3

    *vitesse = VitesseNormale*3;
    
  }else{ //etat 4 : vitesse NULLE

    *vitesse = 0;
    
  }
  
  return nvlEtat;
}


// passer d'un état à un autre
//avec mon idée


/*Tableau où sont stockées les valeurs des vitesses des différents états
 *du tableau de markov si dessus
 *ici ce serait :
 *vitesse   =  30ms
 *vitesse/2 =  15ms
 *vitesse*2 =  60ms
 *vitesse*3 =  90ms
 *endormi   =  0ms
 */
int vitesseParEtat[5] = { 30, 15, 60, 90, 0 };


int passageMarkov(int EtatPrec/*,int * vitesse*/){
  
  int i;
  int pourcentCumul= 0;
  
  int nvlEtat;
  int pourcent = (rand()%101);
  for(i = 0; i < 5 ; i++){

    pourcentCumul += markov[EtatPrec][i];
    
    if(pourcent <= pourcentCumul * 100){

      nvlEtat = i ;
      
      i = 6;
      
    }
    //*vitesse = vitesseParEtat[nvlEtat];
  }       
  
  return nvlEtat;
}


/*Récupére le meilleur score stocké dans un fichier texte
 *on compare avec le score actuel passé en paramètre
 *le plus grand est remis dans le texte et retourné par 
 *la fonction
 */

int  meilleurScore(int ScoreActuel){
  
  srand(time(NULL));
  
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
