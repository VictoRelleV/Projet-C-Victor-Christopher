#include <iostream>
#include <string>
#include <map>
#include "joueur.hh"

using namespace std;

class powerforward : public joueur
{
public:

    powerforward()
    {
    }

    powerforward(string nom, string prenom, string position, string imagePath, int ATQ, int DEF, int VIT)
        : joueur(nom, prenom, position, imagePath, ATQ, DEF, VIT)
    {
    }
};

