#include <iostream>
#include <string>
#include <map>
#include "joueur.hh"

using namespace std;

class center : public joueur
{
public:

    center()
    {
    }

    center(string nom, string prenom, string position, string imagePath, int ATQ, int DEF, int VIT)
        : joueur(nom, prenom, position, imagePath, ATQ, DEF, VIT)
    {
    }
};

