#include <iostream>
#include <string>
#include <map>
#include "joueur.hh"

using namespace std;

class shootingguard : public joueur
{
public:

    shootingguard()
    {
    }

    shootingguard(string nom, string prenom, string position, string imagePath, int ATQ, int DEF, int VIT)
        : joueur(nom, prenom, position, imagePath, ATQ, DEF, VIT)
    {
    }
};

