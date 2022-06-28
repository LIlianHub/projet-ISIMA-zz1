

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