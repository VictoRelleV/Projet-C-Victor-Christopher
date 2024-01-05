#ifndef JOUEUR_HH
#define JOUEUR_HH

#include <string>
#include <map>
#include <random>

using namespace std;

class joueur
{
protected:
    string _nom;
    string _prenom;
    int _OVR;
    string _position;
    string _team;
    string _imagePath; // New attribute for image path
    int _point; // Points scored

    int _ATQ; // Attaque
    int _DEF; // Defense
    int _VIT; // Vitesse

public:

    joueur()
    {
    }

    joueur(string nom, string prenom, int OVR, string position, string team, string imagePath)
        : _nom(nom), _prenom(prenom), _OVR(OVR), _position(position), _team(team), _imagePath(imagePath)
    {
        _point = 0;

        // Utilise l'horloge pour initialiser le générateur de nombres aléatoires
        random_device rd;
        mt19937 gen(rd());

        // Génère un nombre aléatoire entre 50 et 100
        uniform_int_distribution<> distribution1(50, 100);

        _ATQ = distribution1(gen);
        _DEF = distribution1(gen);
        _VIT = distribution1(gen);
    }

    // Getter and setter for the image path
    const string& getImagePath() const {
        return _imagePath;
    }

    void setImagePath(const string& imagePath) {
        _imagePath = imagePath;
    }

    // Other getter methods
    const string& getNom() const {
        return _nom;
    }

    const string& getPrenom() const {
        return _prenom;
    }

    int getOVR() const {
        return _OVR;
    }

    void setOVR(int OVR) {
        _OVR = OVR;
    }

    const string& getPosition() const {
        return _position;
    }

    const string& getTeam() const {
        return _team;
    }

    int getPoint() const {
        return _point;
    }

    void setPoint(int point) {
        _point = point;
    }

    int getATQ() const {
        return _ATQ;
    }

    int getDEF() const {
        return _DEF;
    }

    int getVIT() const {
        return _VIT;
    }
};

map<int, joueur*> createPlayers();
pair<map<int, joueur*>, map<int, joueur*>> createTeams(map<int, joueur*> players);

#endif // JOUEUR_HH