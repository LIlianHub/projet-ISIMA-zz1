#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Config.h"
#include "Algorithme.h"
#include "GraphiqueMenu.h"
#include "GraphiqueEnJeu.h"
#include "Graphique.h"
#include "QTable.h"

/*Global Markov*/

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
             SDL_Texture *table_serpent,
             SDL_Texture *menu)
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

    if (menu != NULL)
    {
        SDL_DestroyTexture(menu);
        menu = NULL;
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
        etat_serpent[i][j].y = 1 * offsetY;
        etat_serpent[i][j].w = offsetX;
        etat_serpent[i][j].h = offsetY;
    }

    // texture corps
    for (int i = 1; i < 6; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            etat_serpent[i][j].x = j * offsetX;
            etat_serpent[i][j].y = (i + 15) * offsetY;
            etat_serpent[i][j].w = offsetX;
            etat_serpent[i][j].h = offsetY;
        }
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

/*Initialisation*/
void Initialisation(SDL_bool *enJeu, SDL_bool *depart, int *iter_explo, int **serpent, int **plateau, int *taille_serpent,
                    int *direction, int *infoIter, int *etat_markov, int *vitesse_markov, int *score, int *multiplicateur, long *lastTick,
                    int *teteSerpent, int *nbItePosMur, SDL_bool *dansJeu, SDL_bool *dansMenu, SDL_bool *AI_mode, int *posPommeI, int *posPommeJ)
{
    *enJeu = SDL_FALSE;
    *depart = SDL_TRUE;
    *iter_explo = 0;
    *taille_serpent = SERPENT_DEMARRAGE;
    InitialisationSerpent(serpent, taille_serpent);
    *direction = 3;
    *infoIter = 2;
    *teteSerpent = 0;
    *etat_markov = 0;
    *vitesse_markov = vitesseParEtat[*etat_markov];
    *score = 0;
    *multiplicateur = *taille_serpent / 3;
    *lastTick = 0;
    *nbItePosMur = 0;
    InitPlateau(plateau);
    ClearMap(plateau);
    posPommeAvecCo(plateau, serpent, *taille_serpent, *teteSerpent, posPommeI, posPommeJ);
    *dansJeu = SDL_FALSE;
    *dansMenu = SDL_TRUE;
    *AI_mode = SDL_FALSE;
}

/*Boucle Principale de Gestion d'événement*/

void GestionEvenement(SDL_Renderer *renderer, TTF_Font *font,
                      int **serpent, int **plateau,
                      int meilleurScore, SDL_Texture *logoMenu,
                      SDL_Texture *pomme, SDL_Texture *explosion,
                      SDL_Texture *table_serpent, SDL_Texture *menuTexture)
{

    /*Variable utile*/
    SDL_bool activation = SDL_TRUE;
    SDL_bool enJeu;
    SDL_bool depart;
    SDL_Event event;
    SDL_bool dansJeu;
    SDL_bool dansMenu;
    SDL_bool AI_mode;

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
    int nbItePosMur;

    // score en fonction du temps qui passe
    int score;
    int multiplicateur;
    long lastTick;

    /*position pomme a chaque iteration*/
    int posPommeI;
    int posPommeJ;

    /*init apprentissage*/
    double **Qtable = NULL;
    Qtable = GenereTabFloat(NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE);
    RecupQtable(Qtable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE);

    // initialisation du jeu
    Initialisation(&enJeu, &depart, &iter_explo, serpent, plateau, &taille_serpent, &direction, &infoIter,
                   &etat_markov, &vitesse_prog, &score,
                   &multiplicateur, &lastTick, &teteSerpent, &nbItePosMur, &dansJeu, &dansMenu, &AI_mode, &posPommeI, &posPommeJ);

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
                case SDLK_LEFT: // on bouge seulement en mode joueur
                    if (direction != 2 && enJeu && !AI_mode)
                        direction = 3;
                    break;
                case SDLK_RIGHT:
                    if (direction != 3 && enJeu && !AI_mode)
                        direction = 2;
                    break;
                case SDLK_UP:
                    if (direction != 1 && enJeu && !AI_mode)
                        direction = 0;
                    break;
                case SDLK_DOWN:
                    if (direction != 0 && enJeu && !AI_mode)
                        direction = 1;
                    break;
                case SDLK_SPACE:
                    if (dansJeu)
                        enJeu = SDL_TRUE;
                    break;
                default:
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN: // Click droit
                if (SDL_GetMouseState(NULL, NULL) &
                    SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    if (dansMenu)
                    {
                        ChoixMenu(event.button.x, event.button.y, &dansJeu, &dansMenu, &enJeu, &depart, &iter_explo, serpent, plateau, &taille_serpent,
                                  &direction, &infoIter, &etat_markov, &vitesse_prog, &score, &multiplicateur, &lastTick, &teteSerpent, &nbItePosMur, &AI_mode,
                                  &posPommeI, &posPommeJ);
                    }
                }
                break;
            default: // poubelle à événement inutile
                break;
            }
        }

        // Nettoyage render
        SDL_RenderClear(renderer);

        if (dansJeu) // dans le mode jeu
        {
            AffichageGrillage(renderer, pomme, plateau, etats_serpent, table_serpent);
            AffichageMenuJeu(renderer, font, logoMenu, meilleurScore, score);

            if (AI_mode)
            { // si en mode AI on calcul la direction avec la qtable
                direction = UtilisationQTable(serpent[teteSerpent][0], serpent[teteSerpent][1], posPommeI, posPommeJ, Qtable);
            }

            if (depart) // menu demarrage on attend l'appuie sur espace
            {
                AffichageSerpent(serpent, renderer, taille_serpent, teteSerpent, direction, table_serpent, etats_serpent, etat_markov);
            }
            if (enJeu)
            {

                IterEnJeu(&depart, &lastTick, &infoIter, &iter_explo, &meilleurScore, &score, &enJeu, &etat_markov,
                          &vitesse_prog, &multiplicateur, &nbItePosMur, &direction, serpent, plateau, &taille_serpent, &teteSerpent,
                          explosion, etats, table_serpent, etats_serpent, renderer, &pos_explosion, &dansJeu, &dansMenu, &posPommeI, &posPommeJ);
            }
        }

        if (dansMenu) // dans le menu
        {
            IterMenu(renderer, menuTexture);
            OverBoutonMenu(renderer, event.motion.x, event.motion.y);
        }

        SDL_Delay(vitesse_prog);
        SDL_RenderPresent(renderer);
    }

    // Libération de la mémoire
    LibererTabFloat(Qtable, NBRE_ETATS_APPRENTISSAGE);
}