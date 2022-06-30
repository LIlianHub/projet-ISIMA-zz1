#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Config.h"
#include "Algorithme.h"
#include "Graphique.h"
#include "QTable.h"

/*Affichage du logo de serpent dans le menu de jeu*/
void AffichageLogo(SDL_Renderer *renderer, SDL_Texture *my_texture)
{
    SDL_Rect boite_logo, image;

    boite_logo.x = 0;
    boite_logo.y = 0;
    boite_logo.w = FENETREWIDTH / 3;
    boite_logo.h = TAILLE_MENU;

    image.x = 0;
    image.y = 0;
    SDL_QueryTexture(my_texture, NULL, NULL, &image.w, &image.h);

    SDL_RenderCopy(renderer, my_texture, &image, &boite_logo);
}

// Affichage dans le menu de jeu du score actuel et du meilleur score
void AffichageScore(SDL_Renderer *renderer, TTF_Font *police, int score, int meilleurScore)
{
    SDL_Color colorBest = {255, 0, 0, 255};
    SDL_Color colorScore = {255, 255, 255, 255};
    SDL_Surface *surfaceBest = NULL;
    SDL_Surface *surfaceScore = NULL;
    SDL_Texture *text_best = NULL;
    SDL_Texture *text_score = NULL;

    char score_formated[255];
    char best_formated[255];

    sprintf(score_formated, "%d", score);
    sprintf(best_formated, "%d", meilleurScore);

    surfaceBest = TTF_RenderText_Blended(police, best_formated, colorBest);
    surfaceScore = TTF_RenderText_Blended(police, score_formated, colorScore);

    text_best = SDL_CreateTextureFromSurface(renderer, surfaceBest);
    text_score = SDL_CreateTextureFromSurface(renderer, surfaceScore);

    SDL_FreeSurface(surfaceBest);
    SDL_FreeSurface(surfaceScore);

    SDL_Rect posBest = {0};
    SDL_Rect posScore = {0};

    SDL_QueryTexture(text_best, NULL, NULL, &posBest.w, &posBest.h);
    SDL_QueryTexture(text_score, NULL, NULL, &posScore.w, &posScore.h);

    posBest.x = 5 * (FENETREWIDTH / 6) - posBest.w / 2;
    posScore.x = FENETREWIDTH / 2 - posScore.w / 2;

    SDL_RenderCopy(renderer, text_best, NULL, &posBest);
    SDL_RenderCopy(renderer, text_score, NULL, &posScore);

    SDL_DestroyTexture(text_best);
    SDL_DestroyTexture(text_score);
}

// Affichage du fond du menu de jeu (appel affiche logo et affichage score)
void AffichageMenuJeu(SDL_Renderer *renderer, TTF_Font *police, SDL_Texture *logo, int meilleurScore, int score)
{
    SDL_Rect fond_menu;
    fond_menu.x = 0;
    fond_menu.y = 0;
    fond_menu.w = FENETREWIDTH;
    fond_menu.h = TAILLE_MENU;
    SDL_SetRenderDrawColor(renderer, 183, 170, 119, 255);
    SDL_RenderFillRect(renderer, &fond_menu);
    AffichageLogo(renderer, logo);
    AffichageScore(renderer, police, score, meilleurScore);
}

/*affichage de la texture de pomme à la position voulu sur la grille dans les bonnes dimmensions*/
void AffichagePomme(SDL_Renderer *renderer, SDL_Texture *pomme, SDL_Rect pos)
{
    SDL_Rect image = {0};
    SDL_QueryTexture(pomme, NULL, NULL, &image.w, &image.h);
    SDL_RenderCopy(renderer, pomme, &image, &pos);
}

// Affichage de la grille de jeu
void AffichageGrillage(SDL_Renderer *renderer, SDL_Texture *pomme, int **plateau, SDL_Rect etats_serpent[6][16], SDL_Texture *table_serpent)
{
    SDL_Rect element_grillage;
    // calcul de la taille d'un element par rapport à la taille de la fenetre et de la grille de jeu
    element_grillage.x = 0;
    element_grillage.y = TAILLE_MENU;
    element_grillage.w = FENETREWIDTH / DIMENSION_TAB_JEU;
    element_grillage.h = (FENETREHEIGHT - TAILLE_MENU) / DIMENSION_TAB_JEU;

    int random;

    for (int i = 0; i < DIMENSION_TAB_JEU; i++)
    {
        for (int j = 0; j < DIMENSION_TAB_JEU; j++)
        {

            // sol
            random = rand() % 4; // random entre les 4 frames de sol possible pour animer le fond
            SDL_RenderCopy(renderer, table_serpent, &etats_serpent[0][random], &element_grillage);
            // si bordure on place la texture de bordure
            if (plateau[i][j] == 2)
            {
                SDL_RenderCopy(renderer, table_serpent, &etats_serpent[0][9], &element_grillage);
            }
            // si cactus on place la texture de cactus
            if (plateau[i][j] == 3)
            {
                SDL_RenderCopy(renderer, table_serpent, &etats_serpent[0][15], &element_grillage);
            }
            // si c'est une pomme on l'affiche
            if (plateau[i][j] == 1)
            {
                AffichagePomme(renderer, pomme, element_grillage);
            }
            element_grillage.x += element_grillage.w;
        }
        element_grillage.x = 0;
        element_grillage.y += element_grillage.h;
    }
}

// Affichage de la tete du serpent
void PlaceTeteSerpent(SDL_Renderer *renderer, int direction, SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16], SDL_Rect pos, int etat)
{
    // texture differente en fonction de la direction et de l'état de markov !
    switch (direction)
    {
    case 0:
        SDL_RenderCopy(renderer, table_serpent, &etats_serpent[2][etat], &pos);
        break;
    case 1:
        SDL_RenderCopy(renderer, table_serpent, &etats_serpent[4][etat], &pos);
        break;
    case 2:
        SDL_RenderCopy(renderer, table_serpent, &etats_serpent[5][etat], &pos);
        break;
    case 3:
        SDL_RenderCopy(renderer, table_serpent, &etats_serpent[3][etat], &pos);
        break;
    default:
        break;
    }
}

// Affichage du corps de serpent selon ses voisins (textures d'angle, droite ....)
void PlaceCorpsSerpent(SDL_Renderer *renderer, int courant, SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16], SDL_Rect pos, int **serpent)
{
    /*ON a besoin du precedent et du suivant*/
    int prec = courant - 1;
    if (prec < 0)
        prec = DIMENSION_TAB_POS - 1;
    int suiv = courant + 1;
    suiv %= DIMENSION_TAB_POS;

    /*valeur precedent, suivant et courant du bout de serpent courant*/
    int precI = serpent[prec][0];
    int precJ = serpent[prec][1];
    int suivI = serpent[suiv][0];
    int suivJ = serpent[suiv][1];
    int courI = serpent[courant][0];
    int courJ = serpent[courant][1];

    if (courI == (precI - 1))
    { // on monte en premier
        if (suivJ == (courJ + 1))
        {
            SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][5], &pos);
        }
        else if (suivJ == (courJ - 1))
        {
            SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][4], &pos);
        }
        else if (suivJ == courJ)
        {
            SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][0], &pos);
        }
    }
    else if (courI == precI)
    { // on reste sur la même ligne
        if (courJ == (precJ + 1))
        {
            if (suivI == (courI + 1))
            {
                SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][4], &pos);
            }
            else if (suivI == (courI - 1))
            {
                SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][2], &pos);
            }
            else
            {
                SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][1], &pos);
            }
        }
        else if (courJ == (precJ - 1))
        {
            if (suivI == (courI + 1))
            {
                SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][5], &pos);
            }
            else if (suivI == (courI - 1))
            {
                SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][3], &pos);
            }
            else
            {
                SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][1], &pos);
            }
        }
    }
    else if (courI == (precI + 1))
    { // on descend en premier
        if (suivJ == (courJ + 1))
        {
            SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][3], &pos);
        }
        else if (suivJ == (courJ - 1))
        {
            SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][2], &pos);
        }
        else if (suivJ == courJ)
        {
            SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][0], &pos);
        }
    }
}

// Placement de la queue du serpent
void PlaceQueueSerpent(SDL_Renderer *renderer, int courant, SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16], SDL_Rect pos, int **serpent)
{
    /*on a besoin du prec et du courant*/
    int prec = courant - 1;
    if (prec < 0)
        prec = DIMENSION_TAB_POS - 1;

    int precI = serpent[prec][0];
    int precJ = serpent[prec][1];

    int curI = serpent[courant][0];
    int curJ = serpent[courant][1];

    if ((curJ + 1) == precJ)
    {
        SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][9], &pos);
    }
    else if ((curJ - 1) == precJ)
    {
        SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][7], &pos);
    }
    else if ((curI + 1) == precI)
    {
        SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][8], &pos);
    }
    else if ((curI - 1) == precI)
    {
        SDL_RenderCopy(renderer, table_serpent, &etats_serpent[1][6], &pos);
    }
}

// Affichage du serpent (appel affichetete, affichecorps et affiche queue selon le cas)
void AffichageSerpent(int **serpent, SDL_Renderer *renderer, int taille_serpent, int teteSerpent, int direction, SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16], int etat)
{
    // taille de la texture du serpent selon la taille de la grille et de la fenetre
    SDL_Rect element_serpent = {0};
    element_serpent.w = FENETREWIDTH / DIMENSION_TAB_JEU;
    element_serpent.h = (FENETREHEIGHT - TAILLE_MENU) / DIMENSION_TAB_JEU;
    int x, y;
    int parcours = teteSerpent;

    for (int j = 0; j < taille_serpent; j++)
    {
        PassageTableauCoor(serpent[parcours][0], serpent[parcours][1], &x, &y);
        element_serpent.x = x;
        element_serpent.y = y;
        if (j == 0) // on place la tete
            PlaceTeteSerpent(renderer, direction, table_serpent, etats_serpent, element_serpent, etat);
        else if (j == taille_serpent - 1) // on place la queue
            PlaceQueueSerpent(renderer, parcours, table_serpent, etats_serpent, element_serpent, serpent);
        else // sinon c'est le corps
            PlaceCorpsSerpent(renderer, parcours, table_serpent, etats_serpent, element_serpent, serpent);

        parcours = (parcours + 1);
        parcours %= DIMENSION_TAB_POS;
    }
}

// Placement de la frame de l'explosion à l'état voulu à l'endroit voulu
void Explosion(SDL_Renderer *renderer, SDL_Texture *explosion, SDL_Rect pos, int etat, SDL_Rect etats[25])
{
    /*recentrage explosion car coordonnées en haut a gauche*/
    pos.x -= pos.w / 2;
    pos.y -= pos.h / 2;
    SDL_RenderCopy(renderer, explosion, &etats[etat], &pos);
}

/*Iteration enJeu*/
// Une itération de jeu
void IterEnJeu(SDL_bool *depart, long *lastTick, int *infoIter, int *iter_explo, int *meilleurScore, int *score, SDL_bool *enJeu, int *etat_markov, int *vitesse_prog,
               int *multiplicateur, int *nbItePosMur, int *direction, int **serpent, int **plateau, int *taille_serpent, int *teteSerpent, SDL_Texture *explosion, SDL_Rect etats[25],
               SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16], SDL_Renderer *renderer, SDL_Rect *pos_explosion, SDL_bool *dansJeu, SDL_bool *dansMenu, int *posPommeI, int *posPommeJ)
{
    if (*depart) // si c'est le depart on declare que ça ne l'est plus et on recupere le premier temps pour le score selon le temps
    {
        *depart = !(*depart);
        *lastTick = SDL_GetTicks();
    }

    /*Mort serpent*/
    if (*infoIter == 0) // fin de jeu
    {
        if (*iter_explo == 0)
        { // premiere frame explosion on calcul position
            int x_explo, y_explo;
            PassageTableauCoor(serpent[*teteSerpent][0], serpent[*teteSerpent][1], &x_explo, &y_explo);
            pos_explosion->x = x_explo;
            pos_explosion->y = y_explo;
            *meilleurScore = MeilleurScore(*score);
        }
        if (*iter_explo < 25) // on affiche les 25 frames d'explosions pour avoir l'animation
        {
            Explosion(renderer, explosion, *pos_explosion, *iter_explo, etats);
            (*iter_explo)++;
        }
        if (*iter_explo == 25)
        { // on a fini d'afficher les explosions on sort du mode jeu FIN DE PARTIE
            *enJeu = SDL_FALSE;
            *dansJeu = SDL_FALSE;
            *dansMenu = SDL_TRUE;
        }
    }

    else // on est en vie
    {
        // Calcul du score en fonction du temps ecoulé à la derniere itérations
        *score += ((SDL_GetTicks() - (*lastTick)) / 25) * (*multiplicateur);
        *lastTick = SDL_GetTicks(); // on recupere le temps pour la prochaine iteration

        if (*etat_markov != 4)
        { // si le serpent est reveillé
            // on recupere l'info de si le serpent a touché quelque chose ou non et on le deplace
            *infoIter = TestDeplacement(serpent, *direction, taille_serpent, plateau, teteSerpent);
            if (*infoIter == 1) // il a mangé
            {
                // on supprime les murets et la pomme car le joueur a fait son job
                ClearMap(plateau);
                // on ajoute une nouvelle pomme
                posPommeAvecCo(plateau, serpent, *taille_serpent, *teteSerpent, posPommeI, posPommeJ);
                // calcul du nouvel etat de markov à chaque fois qu'on mange et de sa vitesse associée
                *etat_markov = passageMarkov(*etat_markov);
                // printf("etat_markov : %d\n", etat_markov);
                *vitesse_prog = vitesseParEtat[*etat_markov];
                *multiplicateur = *taille_serpent / 3; // update multiplicateur tt les 3 pommes

            } // il a pas mangé
            else
            {
                if (AVEC_CACTUS) // possible de jouer avec ou sans cactus selon config.h
                {
                    // on pose un mur toutes les "nbItePosMur"
                    *nbItePosMur += 1;
                    if (*nbItePosMur == ITER_POUR_MUR)
                    {
                        posMuret(plateau, serpent, *direction, *teteSerpent);
                        *nbItePosMur = 0;
                    }
                }
            }
        }
        else
        { // endormi on iter toujours et on rechange d'etat de markov à chaque itération pour le reveiller
            *etat_markov = passageMarkov(*etat_markov);
            *vitesse_prog = vitesseParEtat[*etat_markov];
            // printf("etat_markov : %d\n", etat_markov);
            // on iter toujours pour toujours update le score du serpent !
        }
        // on affiche le serpent
        AffichageSerpent(serpent, renderer, *taille_serpent, *teteSerpent, *direction, table_serpent, etats_serpent, *etat_markov);
    }
}