#ifndef HEADCOACH_HH
#define HEADCOACH_HH

#include <QLabel>

#include "joueur.hh"
#include "person.hh"
#include "match.hh"
#include <random>
#include <vector>  

using namespace std;

class headcoach : public person
{
protected:
    string _equipe;
public:
    headcoach()
    {
    }

    headcoach(string nom, string prenom, string equipe, string imagePath)
        : person(nom, prenom, imagePath), _equipe(equipe)
    {
    }

    // Other getter methods
    const string& getEquipe() const {
        return _equipe;
    }

    vector<int> scoutingReport(int horloge, int nbrChoix, map<int, match*> matches, map<int, joueur*> team2, QLabel* Info)
    {
        // Utilise l'horloge pour initialiser le générateur de nombres aléatoires
        std::random_device rd;
        std::mt19937 gen(rd());
        // Génère un nombre aléatoire entre 0 et 4
        uniform_int_distribution<> distribution5(0, 4);

        vector<int> indices(5, 0);
        int coût = nbrChoix * (12-horloge);
        team2[1]->setPoints(team2[1]->getPoints() + coût);
        matches[3]->setScore2(matches[3]->getScore2() + coût);
        Info->setText(QString::fromStdString(team2[1]->getPrenom() + " " + team2[1]->getNom() + " scored " + to_string(coût) + " points!"));
        for (int i = 0; i < nbrChoix; ++i) {
            int nouvelIndice;
            do {
                nouvelIndice = distribution5(gen);
            } while (indices[nouvelIndice] == 1); {
                indices[nouvelIndice] = 1;
            }
        }
        return indices;   
    }
    
};

int Draft();

#endif // HEADCOACH_HH
