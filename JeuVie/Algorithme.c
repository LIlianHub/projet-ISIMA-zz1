#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*void EcritureConfig(int **tab, int ligne, int colonne)
{
    printf("yo");
    FILE *fichier = NULL;
    int debut = 1;
    printf("suh");
    if ((fichier = fopen("LastSave/save.txt","w+")) != NULL)
    {
        if(debut)
            debut = 0;
        else
            fputc('\n', fichier);

        for (int i = 0; i < ligne; i++)
        {
            for (int j = 0; j < colonne; j++)
            {
                char ecriture = (char)tab[i][j] + 'a';
                fputc(ecriture, fichier);
            }
        }
        fclose(fichier);
    }
}*/