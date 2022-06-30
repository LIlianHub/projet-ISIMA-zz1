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
 *vitesse   =  50ms
 *vitesse/2 =  80ms
 *vitesse*2 = 35ms
 *vitesse*3 =  27ms
 *endormi   =  500ms
 */
int vitesseParEtat[5] = {50, 80, 35, 27, 500};
// 500 pour endormi le programme continu de tourner mais on bloque mouvement du serpent

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

/*passage indice du plateau au coordonnées de la fenetre pour placer le serpent et les explosions au bon endroit*/
void PassageTableauCoor(int i, int j, int *x, int *y)
{
    *x = j * (FENETREWIDTH / DIMENSION_TAB_JEU);
    *y = i * ((FENETREHEIGHT - TAILLE_MENU) / DIMENSION_TAB_JEU) + TAILLE_MENU;
}

/*InitTextureSerpent (les frames necessaires) dans un tableau 2D de SDL_Rect*/
void InitTextureSerpent(SDL_Rect etat_serpent[6][16], SDL_Texture *table_serpent)
{
    SDL_Rect planche = {0};
    SDL_QueryTexture(table_serpent, NULL, NULL, &planche.w, &planche.h);
    int offsetX = planche.w / 16;
    int offsetY = planche.h / 22; // 5 lignes et 5 colonnes

    // texture sol et mur sur la ligne 1 d'ou 1 * offsetY
    int i = 0;
    for (int j = 0; j < 16; j++)
    {
        etat_serpent[i][j].x = j * offsetX;
        etat_serpent[i][j].y = 1 * offsetY;
        etat_serpent[i][j].w = offsetX;
        etat_serpent[i][j].h = offsetY;
    }

    // texture corps de la ligne 15 à 20
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

/*Recuperation de l'animation de l'explosion de defaite (25 frames) dans 1 tableau 1D*/
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

/*Initialisation: necessaire pour chaque nouvelle partie, permet de remettre toutes les variables comme il faut*/
void Initialisation(SDL_bool *enJeu, SDL_bool *depart, int *iter_explo, int **serpent, int **plateau, int *taille_serpent,
                    int *direction, int *infoIter, int *etat_markov, int *vitesse_markov, int *score, int *multiplicateur, long *lastTick,
                    int *teteSerpent, int *nbItePosMur, SDL_bool *dansJeu, SDL_bool *dansMenu, SDL_bool *AI_mode, int *posPommeI, int *posPommeJ)
{
    *enJeu = SDL_FALSE;                                                                    // on est plus en train de jouer
    *depart = SDL_TRUE;                                                                    // on est sur le depart de partie
    *iter_explo = 0;                                                                       // on a par encore affiché l'explosion
    *taille_serpent = SERPENT_DEMARRAGE;                                                   // le serpent a sa taille de démarrage
    InitialisationSerpent(serpent, taille_serpent);                                        // on initialise le tableau serpent
    *direction = 3;                                                                        // la direction de base au depart est à gauche
    *infoIter = 2;                                                                         // la premiere itération tout va bien
    *teteSerpent = 0;                                                                      // la tete de serpent est à la ligne 0 du tableau serpent à l'initialisation
    *etat_markov = 0;                                                                      // etat classique de markov
    *vitesse_markov = vitesseParEtat[*etat_markov];                                        // vitesse classique de markov
    *score = 0;                                                                            // score à 0
    *multiplicateur = *taille_serpent / 3;                                                 // multiplicateur en lien avec la taille du serpent
    *lastTick = 0;                                                                         // le dernier tick de jeu pour le score avec le temps est remis à 0
    *nbItePosMur = 0;                                                                      // on remet à 0 le compteur pour poser les cactus qui gène
    InitPlateau(plateau);                                                                  // on initialise le plateau
    ClearMap(plateau);                                                                     // on le nettoie
    posPommeAvecCo(plateau, serpent, *taille_serpent, *teteSerpent, posPommeI, posPommeJ); // on pose la premiere pomme
    *dansJeu = SDL_FALSE;                                                                  // on est plus dans le mode jeu
    *dansMenu = SDL_TRUE;                                                                  // on est dans le menu
    *AI_mode = SDL_FALSE;                                                                  // on est pas en mode AI
}

/*Boucle Principale de Gestion d'événement*/

void GestionEvenement(SDL_Renderer *renderer, TTF_Font *font,
                      int **serpent, int **plateau,
                      int meilleurScore, SDL_Texture *logoMenu,
                      SDL_Texture *pomme, SDL_Texture *explosion,
                      SDL_Texture *table_serpent, SDL_Texture *menuTexture)
{

    /*Variable utile*/
    SDL_bool activation = SDL_TRUE; // le programmme tourne
    SDL_bool enJeu;                 // on est en mode jeu
    SDL_bool depart;                // on est sur un debut de partie
    SDL_Event event;                // recupere les evenements
    SDL_bool dansJeu;               // on est en train de jouer
    SDL_bool dansMenu;              // on est dans le menu
    SDL_bool AI_mode;               // on est en mode AI

    /*Gestion animation explosion*/
    SDL_Rect etats[25];
    GenereTabExplosion(etats, explosion);
    int iter_explo;
    // taille de l'explosion en fonction de la taille de la fenetre
    SDL_Rect pos_explosion = {0, 0, FENETREWIDTH * TAILLE_EXPLOSION / DIMENSION_TAB_JEU, (FENETREHEIGHT - TAILLE_MENU) * TAILLE_EXPLOSION / DIMENSION_TAB_JEU};

    /*Gestion animation Serpent*/
    SDL_Rect etats_serpent[6][16];
    InitTextureSerpent(etats_serpent, table_serpent);

    /*Gestion Serpent*/
    int taille_serpent;
    int teteSerpent;

    /*direction serpent a chaque itératiion*/
    int direction;

    /*info sur le deplacement à chaque itération (si on est mort ou non ..)*/
    int infoIter;

    /*Gestion Markov*/
    // etat initiale 0 vitesse classique
    int etat_markov;
    int vitesse_prog;

    // Placement des murs toutes les "nbItePosMur" itérations
    int nbItePosMur;

    // score en fonction du temps qui passe
    int score;
    int multiplicateur;
    long lastTick;

    /*position pomme a chaque iteration*/
    int posPommeI;
    int posPommeJ;

    /*init apprentissage*/
    double QTable[NBRE_ETATS_APPRENTISSAGE][NBRE_ACTION_APPRENTISSAGE][NBRE_ETAT_AUTOUR];
    RecupQtable(QTable, NBRE_ETATS_APPRENTISSAGE, NBRE_ACTION_APPRENTISSAGE, NBRE_ETAT_AUTOUR);

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
                {               // on peut pas retourner sur soit même (quand on était direction gauche on retourne pas direct à droite)
                case SDLK_LEFT: // on bouge seulement en mode joueur quand on est en jeu
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
                    if (dansJeu) //
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
                    if (dansMenu) // si dans le menu on itéragit par clique avec le menu
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
            // On affiche la grille et le menu en haut avec le score
            AffichageGrillage(renderer, pomme, plateau, etats_serpent, table_serpent);
            AffichageMenuJeu(renderer, font, logoMenu, meilleurScore, score);

            if (AI_mode)
            { // si en mode AI on calcul la direction avec la qtable
                direction = UtilisationQTable(serpent[teteSerpent][0], serpent[teteSerpent][1], posPommeI, posPommeJ, QTable, serpent, plateau, &taille_serpent, &teteSerpent);
            }

            if (depart) // demarrage on attend l'appuie sur espace le serpent s'affiche mais ne bouge pas
            {
                AffichageSerpent(serpent, renderer, taille_serpent, teteSerpent, direction, table_serpent, etats_serpent, etat_markov);
            }
            if (enJeu) // le serpent bouge quand on est en jeu
            {
                IterEnJeu(&depart, &lastTick, &infoIter, &iter_explo, &meilleurScore, &score, &enJeu, &etat_markov,
                          &vitesse_prog, &multiplicateur, &nbItePosMur, &direction, serpent, plateau, &taille_serpent, &teteSerpent,
                          explosion, etats, table_serpent, etats_serpent, renderer, &pos_explosion, &dansJeu, &dansMenu, &posPommeI, &posPommeJ);
            }
        }

        if (dansMenu) // dans le menu
        {
            // on affiche le menu
            IterMenu(renderer, menuTexture);
            // effet over sympa pour rendre le menu responsif sur les boutons
            OverBoutonMenu(renderer, event.motion.x, event.motion.y);
        }

        //delay selon la vitesse de markov pour le serpent se deplace + ou -vite
        SDL_Delay(vitesse_prog);
        //on affiche le render
        SDL_RenderPresent(renderer);
    }
}