
typedef struct etat{
  int nord_sud;
  int ouest_est;
}etat;




int calculEtat(int teteSx, int teteSy, int pommex, int pommey)
{
    int directionX = teteSx - pommex; // si positif : ouest sinon est
    int directionY = teteSy - pommey; // si positif : nord sinon su
    int etat = 4;

    if (directionX > 0) // ouest
    {
        if (directionY > 0)
        {
            etat = 8; // nord ouest
        }
        else if (directionY < 0)
        {
            etat = 2; // sud ouest
        }
        else
        {
            etat = 5; // ouest
        }
    }
    else if (directionX < 0) // est
    {
        if (directionY > 0)
        {
            etat = 6; // nord est
        }
        else if (directionY < 0)
        {
            etat = 0; // sud est
        }
        else
        {
            etat = 3; // est
        }
    }
    else // juste nord ou sud
    {
        if (directionY > 0)
        {
            etat = 7; // nord
        }
        else if (directionY < 0)
        {
            etat = 1; // sud
        }
        else
        {
            etat = 4; // sur la pomme
        }
    }

    return etat;
}


etat * liste_etats;

void genereTableauEtat()
{
    liste_etats = (etat *)malloc(sizeof(etat) * 9);
    liste_etats[0].nord_sud = -1;
    liste_etats[0].ouest_est = -1;
    liste_etats[1].nord_sud = -1;
    liste_etats[1].ouest_est = 0;
    liste_etats[2].nord_sud = -1;
    liste_etats[2].ouest_est = 1;
    liste_etats[3].nord_sud = 0;
    liste_etats[3].ouest_est = -1;
    liste_etats[4].nord_sud = 0;
    liste_etats[4].ouest_est = 0;
    liste_etats[5].nord_sud = 0;
    liste_etats[5].ouest_est = 1;
    liste_etats[6].nord_sud = 1;
    liste_etats[6].ouest_est = -1;
    liste_etats[7].nord_sud = 1;
    liste_etats[7].ouest_est = 0;
    liste_etats[8].nord_sud = 1;
    liste_etats[8].ouest_est = 1;
}
