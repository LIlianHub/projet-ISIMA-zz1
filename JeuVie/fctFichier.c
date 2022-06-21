#include <stdio.h>
#include <stdlib.h>

void SauvFichier(FILE * f, int tab[4][4], int ligne, int colonne)
{
  int i,j;

  for ( i = 0 ; i < ligne ; i++ ){

    for ( j = 0 ; j < colonne ; j++ ){

      fprintf(f,"%d ",tab[i][j]);
      
      
    }
    fputc('\n',f);
  }  
}

void afficher(int tab[4][4], int ligne, int colonne){

  int i,j;

  for(i=0 ; i<ligne ; i++){

    for(j=0 ; j<colonne ; j++){

      printf("%d ",tab[i][j]);

      
    }

    printf("\n");
  }
  
}

void LectureFichier(FILE * file , t[4][4], int ligne, int colonne){
  int i,j;
  for( i = 0 ; i < ligne ; i++ ){

    for( j = 0 ; j < colonne ; j++){
      
      //t[i][j] = atoi(fgetc(file));
    }
    fgetc(file);
  }

  
}

int main (){

  FILE *f = fopen("file.txt","w");
  
  int tab[4][4] = {{1,2,3,4},{4,3,2,1},{2,2,2,2},{5,1,5,1}};
  SauvFichier(f,tab,4,4);
  int t[4][4] = {0};
  LectureFichier(f,t,4,4);
  afficher(t,4,4);
  fclose(f);
  return 0;
}
