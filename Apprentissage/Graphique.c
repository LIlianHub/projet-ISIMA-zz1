#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Config.h"
#include "Algorithme.h"

/*Global MArkov*/

/*Tableau où sont stockées les valeurs des vitesses des différents états
 *du tableau de markov si dessus
 *ici ce serait :
 *vitesse   =  30ms
 *vitesse/2 =  60ms
 *vitesse*2 =  15ms
 *vitesse*3 =  7ms
 *endormi   =  0ms
 */
int vitesseParEtat[5] = {50, 80, 35, 27, 500};
// 50 pour endormi le programme continu de tourner mais on bloque le serpent

/*LIbération Propre de la SDL*/

void end_sdl(char ok,
             char const *msg,
             SDL_Window *window,
             SDL_Renderer *renderer,
             TTF_Font *font,
             SDL_Texture *logo,
             SDL_Texture *pomme,
             SDL_Texture *explosion,
             SDL_Texture *table_serpent)
{
    char msg_formated[255];
    int l;

    if (!ok)
    { // Affichage de ce qui ne va pas
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    if (font != NULL)
    {
        TTF_CloseFont(font);
        font = NULL;
    }
    if (logo != NULL)
    {
        SDL_DestroyTexture(logo);
        logo = NULL;
    }

    if (pomme != NULL)
    {
        SDL_DestroyTexture(pomme);
        pomme = NULL;
    }

    if (explosion != NULL)
    {
        SDL_DestroyTexture(explosion);
        explosion = NULL;
    }

    if (table_serpent != NULL)
    {
        SDL_DestroyTexture(table_serpent);
        table_serpent = NULL;
    }

    TTF_Quit();
    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

/*passage indice du plateau au coordonnées de la fenetre*/
void PassageTableauCoor(int i, int j, int *x, int *y)
{
    *x = j * (FENETREWIDTH / DIMENSION_TAB_JEU);
    *y = i * ((FENETREHEIGHT - TAILLE_MENU) / DIMENSION_TAB_JEU) + TAILLE_MENU;
}

/*AffichageLogoMenu*/

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

/*voir les tests*/
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

/*Menu en haut*/
void AffichageMenu(SDL_Renderer *renderer, TTF_Font *police, SDL_Texture *logo, int meilleurScore, int score)
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

/*Grille*/

void AffichagePomme(SDL_Renderer *renderer, SDL_Texture *pomme, SDL_Rect pos)
{
    SDL_Rect image = {0};
    SDL_QueryTexture(pomme, NULL, NULL, &image.w, &image.h);
    SDL_RenderCopy(renderer, pomme, &image, &pos);
}

void AffichageGrillage(SDL_Renderer *renderer, SDL_Texture *pomme, int **plateau, SDL_Rect etats_serpent[6][16], SDL_Texture *table_serpent)
{
    SDL_Rect element_grillage;
    element_grillage.x = 0;
    element_grillage.y = TAILLE_MENU;
    element_grillage.w = FENETREWIDTH / DIMENSION_TAB_JEU;
    element_grillage.h = (FENETREHEIGHT - TAILLE_MENU) / DIMENSION_TAB_JEU;

    for (int i = 0; i < DIMENSION_TAB_JEU; i++)
    {
        for (int j = 0; j < DIMENSION_TAB_JEU; j++)
        {

            // sol
            SDL_RenderCopy(renderer, table_serpent, &etats_serpent[0][3], &element_grillage);
            // si bordure
            if (plateau[i][j] == 2)
            {
                SDL_RenderCopy(renderer, table_serpent, &etats_serpent[0][6], &element_grillage);
            }

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

/* LE SERPENT*/
void PlaceTeteSerpent(SDL_Renderer *renderer, int direction, SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16], SDL_Rect pos)
{
    switch (direction)
    {
    case 0:
        SDL_RenderCopy(renderer, table_serpent, &etats_serpent[2][3], &pos);
        break;
    case 1:
        SDL_RenderCopy(renderer, table_serpent, &etats_serpent[4][3], &pos);
        break;
    case 2:
        SDL_RenderCopy(renderer, table_serpent, &etats_serpent[5][3], &pos);
        break;
    case 3:
        SDL_RenderCopy(renderer, table_serpent, &etats_serpent[3][3], &pos);
        break;
    default:
        break;
    }
}

void PlaceCorpsSerpent(SDL_Renderer *renderer, int courant, SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16], SDL_Rect pos){
    int prec = courant - 1;
    if(prec < 0)
        prec = DIMENSION_TAB_POS - 1;
    int suiv = courant + 1;
    suiv %= DIMENSION_TAB_POS;

    

}


void AffichageSerpent(int **serpent, SDL_Renderer *renderer, int taille_serpent, int teteSerpent, int direction, SDL_Texture *table_serpent, SDL_Rect etats_serpent[6][16])
{
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
        if (j == 0)
            PlaceTeteSerpent(renderer, direction, table_serpent, etats_serpent, element_serpent);
        else
        {
            SDL_SetRenderDrawColor(renderer, 90, 175, 237, 255);
            SDL_RenderFillRect(renderer, &element_serpent);
        }

        parcours = (parcours + 1);
        parcours %= DIMENSION_TAB_POS;
    }
}

/*InitTextureSerpent*/
void InitTextureSerpent(SDL_Rect etat_serpent[6][16], SDL_Texture *table_serpent)
{
    SDL_Rect planche = {0};
    SDL_QueryTexture(table_serpent, NULL, NULL, &planche.w, &planche.h);
    int offsetX = planche.w / 16;
    int offsetY = planche.h / 22; // 5 lignes et 5 colonnes

    // texture sol et mur
    int i = 0;
    for (int j = 0; j < 16; j++)
    {
        etat_serpent[i][j].x = j * offsetX;
        etat_serpent[i][j].y = offsetY;
        etat_serpent[i][j].w = offsetX;
        etat_serpent[i][j].h = offsetY;
    }

    // texture corps
    i++;
    for (int j = 0; j < 16; j++)
    {
        etat_serpent[i][j].x = j * offsetX;
        etat_serpent[i][j].y = 16 * offsetY;
        etat_serpent[i][j].w = offsetX;
        etat_serpent[i][j].h = offsetY;
    }

    i++;
    for (int j = 0; j < 16; j++)
    {
        etat_serpent[i][j].x = j * offsetX;
        etat_serpent[i][j].y = 17 * offsetY;
        etat_serpent[i][j].w = offsetX;
        etat_serpent[i][j].h = offsetY;
    }

    i++;
    for (int j = 0; j < 16; j++)
    {
        etat_serpent[i][j].x = j * offsetX;
        etat_serpent[i][j].y = 18 * offsetY;
        etat_serpent[i][j].w = offsetX;
        etat_serpent[i][j].h = offsetY;
    }

    i++;
    for (int j = 0; j < 16; j++)
    {
        etat_serpent[i][j].x = j * offsetX;
        etat_serpent[i][j].y = 19 * offsetY;
        etat_serpent[i][j].w = offsetX;
        etat_serpent[i][j].h = offsetY;
    }

    i++;
    for (int j = 0; j < 16; j++)
    {
        etat_serpent[i][j].x = j * offsetX;
        etat_serpent[i][j].y = 20 * offsetY;
        etat_serpent[i][j].w = offsetX;
        etat_serpent[i][j].h = offsetY;
    }
}

/*explosion de defaite*/
void GenereTabExplosion(SDL_Rect etats[25], SDL_Texture *explosion)
{
    SDL_Rect planche = {0};
    SDL_QueryTexture(explosion, NULL, NULL, &planche.w, &planche.h);
    int offsetX = planche.w / 5;
    int offsetY = planche.h / 5; // 5 lignes et 5 colonnes
    int indice = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            etats[indice].w = offsetX;
            etats[indice].h = offsetY;
            etats[indice].x = j * offsetX;
            etats[indice].y = i * offsetY;
            indice++;
        }
    }
}

void Explosion(SDL_Renderer *renderer, SDL_Texture *explosion, SDL_Rect pos, int etat, SDL_Rect etats[25])
{
    /*recentrage explosion car coordonnées en haut a gauche*/
    pos.x -= pos.w / 2;
    pos.y -= pos.h / 2;
    SDL_RenderCopy(renderer, explosion, &etats[etat], &pos);
}

/*Initialisation*/
void Initialisation(SDL_bool *enJeu, SDL_bool *depart, int *iter_explo, int **serpent, int **plateau, int *taille_serpent,
                    int *direction, int *infoIter, int *etat_markov, int *vitesse_markov, int *score, int *multiplicateur, long *lastTick,
                    int *teteSerpent)
{
    *enJeu = SDL_FALSE;
    *depart = SDL_TRUE;
    *iter_explo = 0;
    *taille_serpent = 3;
    InitialisationSerpent(serpent, taille_serpent);
    *direction = 3;
    *infoIter = 2;
    InitPlateau(plateau);
    posPomme(plateau, serpent, *taille_serpent);
    *etat_markov = 0;
    *vitesse_markov = vitesseParEtat[*etat_markov];
    *score = 0;
    *multiplicateur = *taille_serpent / 3;
    *lastTick = 0;
    *teteSerpent = 0;
}

/*Iteration enJeu*/

/*Boucle Principale de Gestion d'événement*/

void GestionEvenement(SDL_Renderer *renderer, TTF_Font *font,
                      int **serpent, int **plateau,
                      int meilleurScore, SDL_Texture *logoMenu,
                      SDL_Texture *pomme, SDL_Texture *explosion,
                      SDL_Texture *table_serpent)
{

    /*Variable utile*/
    SDL_bool activation = SDL_TRUE;
    SDL_bool enJeu;
    SDL_bool depart;
    SDL_Event event;

    /*Gestion animation explosion*/
    SDL_Rect etats[25];
    GenereTabExplosion(etats, explosion);
    int iter_explo;
    SDL_Rect pos_explosion = {0, 0, FENETREWIDTH * TAILLE_EXPLOSION / DIMENSION_TAB_JEU, (FENETREHEIGHT - TAILLE_MENU) * TAILLE_EXPLOSION / DIMENSION_TAB_JEU};

    /*Gestion animation Serpent*/
    SDL_Rect etats_serpent[6][16];
    InitTextureSerpent(etats_serpent, table_serpent);

    /*Gestion Serpent*/
    int taille_serpent;
    int teteSerpent;

    /*direction serpent a chaque itératiion*/
    int direction;

    /*info sur le deplacement*/
    int infoIter;

    /*Gestion Markov*/
    // etat initiale 0 vitesse classique
    int etat_markov;
    int vitesse_prog;

    // score en fonction du temps qui passe
    int score;
    ;
    int multiplicateur;
    long lastTick;

    Initialisation(&enJeu, &depart, &iter_explo, serpent, plateau, &taille_serpent, &direction, &infoIter, &etat_markov, &vitesse_prog, &score, &multiplicateur, &lastTick, &teteSerpent);

    while (activation)
    {
        while (SDL_PollEvent(&event)) // on vide la pile d'evenement
        {
            switch (event.type)
            {
            case SDL_QUIT: // ON quitte
                activation = SDL_FALSE;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    if (direction != 2)
                        direction = 3;
                    break;
                case SDLK_RIGHT:
                    if (direction != 3)
                        direction = 2;
                    break;
                case SDLK_UP:
                    if (direction != 1)
                        direction = 0;
                    break;
                case SDLK_DOWN:
                    if (direction != 0)
                        direction = 1;
                    break;
                case SDLK_SPACE:
                    if (!enJeu)
                        enJeu = SDL_TRUE;
                    break;
                default:
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN: // Click droit
                if (SDL_GetMouseState(NULL, NULL) &
                    SDL_BUTTON(SDL_BUTTON_LEFT))
                { // clique droit
                }
                break;
            default: // poubelle à événement inutile
                break;
            }
        }

        // Nettoyage render
        SDL_RenderClear(renderer);

        /*Affichage*/
        AffichageGrillage(renderer, pomme, plateau, etats_serpent, table_serpent);
        AffichageMenu(renderer, font, logoMenu, meilleurScore, score);

        if (enJeu)
        {
            if (depart)
            {
                depart = !depart;
                lastTick = SDL_GetTicks();
            }

            /*Mort serpent*/
            if (infoIter == 0) // fin de jeu
            {
                if (iter_explo == 0)
                { // premiere frame on calcul position
                    int x_explo, y_explo;
                    PassageTableauCoor(serpent[teteSerpent][0], serpent[teteSerpent][1], &x_explo, &y_explo);
                    pos_explosion.x = x_explo;
                    pos_explosion.y = y_explo;
                    meilleurScore = MeilleurScore(score);
                }
                if (iter_explo < 25)
                {
                    Explosion(renderer, explosion, pos_explosion, iter_explo, etats);
                    iter_explo++;
                }
                if (iter_explo == 25)
                { // on a fini
                    enJeu = SDL_FALSE;
                }
            }

            else // en vie
            {
                // Calcul du score en fonction du temps ecoulé
                score += ((SDL_GetTicks() - lastTick) / 25) * multiplicateur; // en mili sec donc /1000 pour sec
                lastTick = SDL_GetTicks();

                if (etat_markov != 4)
                { // pas endormi
                    infoIter = TestDeplacement(serpent, direction, &taille_serpent, plateau, &teteSerpent);
                    if (infoIter == 1) // il a mangé
                    {
                        // on supprime la pomme
                        SupprimePomme(plateau, serpent, direction, teteSerpent);
                        // on ajoute une nouvelle pomme
                        posPomme(plateau, serpent, taille_serpent);
                        // calcul de la nouvelle vitesse possible selon markov
                        etat_markov = passageMarkov(etat_markov);
                        // printf("etat_markov : %d\n", etat_markov);
                        vitesse_prog = vitesseParEtat[etat_markov];
                        multiplicateur = taille_serpent / 3; // update multiplicateur
                    }
                }
                else
                { // endormi juste on fait des trirages mais le serpent bouge po
                    etat_markov = passageMarkov(etat_markov);
                    vitesse_prog = vitesseParEtat[etat_markov];
                    // printf("etat_markov : %d\n", etat_markov);
                }

                AffichageSerpent(serpent, renderer, taille_serpent, teteSerpent, direction, table_serpent, etats_serpent);
            }
        }
        if (depart) // menu demarrage on attend l'appuie sur espace
        {
            AffichageSerpent(serpent, renderer, taille_serpent, teteSerpent, direction, table_serpent, etats_serpent);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(vitesse_prog); // depend pour fps avec horloge
    }
}
