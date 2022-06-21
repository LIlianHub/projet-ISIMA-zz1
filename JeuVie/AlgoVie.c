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
}

int NbVoisins(int ** TabT1, int nbLignes, int nbColonnes, int i, int j){
    int nbV;

    if(i==0){
        if(j==0){
                nbV = TabT1[i+1][j] + TabT1[i+1][j+1] + TabT1[i][j+1] + TabT1[nbLignes-1][0] + TabT1[nbLignes-1][1] + TabT1[nbLignes-1][nbColonnes-1] + TabT1[0][nbColonnes-1]
                            + TabT1[1][nbColonnes-1];
                            printf("%d \n", nbV);
        }
        else{
                if(j==nbColonnes-1){
                nbV = TabT1[0][j-1] + TabT1[1][j-1] + TabT1[1][j] + TabT1[nbLignes-1][j-1] + TabT1[nbLignes-1][j] + TabT1[0][0] + TabT1[1][0] + TabT1[nbLignes-1][nbColonnes-1];
                }
                else{
                nbV = TabT1[i][j-1]+TabT1[i][j+1]+TabT1[i+1][j-1]+TabT1[i+1][j]+TabT1[i+1][j+1]+TabT1[nbLignes-1][j]+TabT1[nbLignes-1][j-1]+TabT1[nbLignes-1][j+1];
                }
        }
    }
    else{
        if(i==nbLignes-1){
            if(j==0){
                nbV = TabT1[i-1][j] + TabT1[i-1][j+1] + TabT1[i][j+1] + TabT1[0][j] + TabT1[0][j+1] + TabT1[i][nbColonnes-1] + TabT1[i-1][nbColonnes-1] + TabT1[0][nbColonnes-1];
            }
            else{
                if(j==nbColonnes-1){
                    printf("baba\n");
                    nbV = TabT1[i][j-1]+TabT1[i-1][j-1]+TabT1[i-1][j]+TabT1[i-1][0]+TabT1[i][0]+TabT1[0][j-1]+TabT1[0][j]+TabT1[0][0];
                }
                else{
                nbV = TabT1[i][j-1]+TabT1[i][j+1]+TabT1[i-1][j-1]+TabT1[i-1][j]+TabT1[i-1][j+1]+TabT1[0][j-1]+TabT1[0][j]+TabT1[0][j+1];
                }
            }
        }
        else{
            if(j==0){
                nbV = TabT1[i][j-1]+TabT1[i][j+1]+TabT1[i+1][j-1]+TabT1[i+1][j]+TabT1[i+1][j+1]+TabT1[i][nbColonnes-1]+TabT1[i+1][nbColonnes-1]+TabT1[i-1][nbColonnes-1];
            }
            else{
                if(j==nbColonnes-1){
                     nbV = TabT1[i][j-1]+TabT1[i][j+1]+TabT1[i-1][j-1]+TabT1[i-1][j]+TabT1[i-1][j+1]+TabT1[i][0]+TabT1[i+1][0]+TabT1[i-1][0];
                }
                else{
                    nbV = TabT1[i][j-1]+TabT1[i][j+1]+TabT1[i-1][j-1]+TabT1[i-1][j]+TabT1[i-1][j+1]+TabT1[i+1][j-1]+TabT1[i+1][j]+TabT1[i-1][j+1];
                }

            }
        }
    
    }
    return nbV;
}

void VieTore(int ** TabT1, int ** TabTplus1, int B[TAILLE_MASQUE], int S[TAILLE_MASQUE], int NbLignes,int NbColonnes){
    int i,j, NbV;
    int ** TabInt;

    for (i=0;i<NbLignes; i++){
        printf("%d ggg\n",i);
        for(j=0;j<NbColonnes;j++){
            printf("%dloijij \n",j);
                NbV = NbVoisins(TabT1,NbLignes,NbColonnes,i,j);
                //printf("%d hhhh\n", NbV);
                if(TabT1[i][j]==1){             //Cas où la cellule est vivante donc masque de mort
                    if(NbV==B[NbV]){
                        TabTplus1[i][j]= 0;
                    }
                }
                
                else{                           //Cas où la cellule est morte donc masque de vie
                    if(NbV==S[NbV]){
                        TabTplus1[i][j]= 1;
                    }
                }


        }
    }
    TabInt = TabT1;
    TabT1 = TabTplus1;
    TabTplus1 = TabInt;

}



int main(){
    int B[TAILLE_MASQUE] = {0,1,0,0,1,0,0,0,0};
    int S[TAILLE_MASQUE] = {0,0,0,0,0,0,1,0,0};

    int ** TabT1 = creer_tableau(4,4);
    int ** TabTplus1 = creer_tableau(4,4);

    afficher_tableau(TabT1,4,4);
    printf("\n");
    afficher_tableau(TabTplus1,4,4);
    

    VieTore(TabT1,TabTplus1,B,S,4,4);
    

    afficher_tableau(TabT1,4,4);
    afficher_tableau(TabTplus1,4,4);

    return 0;

}



