// Trouvez ici tous les defines de configs du programme

#ifndef CONFIG_H
#define CONFIG_H

// Commun
#define DIMENSION_TAB_JEU 40
#define DIMENSION_TAB_POS (DIMENSION_TAB_JEU - 2) * (DIMENSION_TAB_JEU - 2)
#define ITER_POUR_DIM_SERPENT 25 // toutes les 50 iterations le serpent perd 1 de taille
#define AVEC_DIM_SERPENT 1       // activer le mode dim serpent

// Graphique
#define TAILLE_MENU 60
#define FENETREWIDTH 800
#define FENETREHEIGHT 800 + TAILLE_MENU
#define TAILLE_EXPLOSION 5   // taille de l'explosion de fin
#define ITER_POUR_MUR 10     // toutes les 10 iterations un cactus apparait
#define SERPENT_DEMARRAGE 10 // la taille de démarage du serpent
#define AVEC_CACTUS 0        // activer le mode cactus
#define NB_ETATS_MARKOV 5

// Apprentissage
#define TAILLEMAX_APPRENTISSAGE 500
#define NBRE_ETATS_APPRENTISSAGE 9
#define NBRE_ACTION_APPRENTISSAGE 4
#define NBRE_ETAT_AUTOUR 16
#define GAMMA 1.0

#endif
