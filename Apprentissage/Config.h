// Trouvez ici tous les defines de configs du programme

#ifndef CONFIG_H
#define CONFIG_H

//Commun
#define DIMENSION_TAB_JEU 40
#define DIMENSION_TAB_POS (DIMENSION_TAB_JEU - 2) * (DIMENSION_TAB_JEU - 2)

//Graphique
#define TAILLE_MENU 60
#define FENETREWIDTH 800
#define FENETREHEIGHT 800 + TAILLE_MENU
#define TAILLE_EXPLOSION 5
#define ITER_POUR_MUR 5
#define SERPENT_DEMARRAGE 10
#define AVEC_CACTUS 0
#define NB_ETATS_MARKOV 5


//Apprentissage
#define TAILLEMAX_APPRENTISSAGE 500
#define NBRE_ETATS_APPRENTISSAGE 9
#define NBRE_ACTION_APPRENTISSAGE 4
#define NBRE_ETAT_AUTOUR 16
#define GAMMA 1.0

#endif
