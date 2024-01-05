#include <iostream>
#include <string>
#include <map>
#include "joueur.hh"

using namespace std;

class pointguard : public joueur
{
public:
    pointguard() {}

    pointguard(string nom, string prenom, int OVR, string position, string team, string imagePath)
        : joueur(nom, prenom, OVR, position, team, imagePath)
    {
        // Utilise l'horloge pour initialiser le générateur de nombres aléatoires
        std::random_device rd;
        std::mt19937 gen(rd());

        // Génère un nombre aléatoire
        uniform_int_distribution<> distribution1(70, 100);
        uniform_int_distribution<> distribution2(0, 50);
        uniform_int_distribution<> distribution3(70, 100);

        _ATQ = distribution1(gen);
        _DEF = distribution2(gen);
        _VIT = distribution3(gen);
    }
};

