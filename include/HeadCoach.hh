#ifndef HEADCOACH_HH
#define HEADCOACH_HH

#include <QLabel>

#include "Joueur.hh"
#include "Person.hh"
#include "Match.hh"
#include <random>
#include <utility>
#include <vector>

using namespace std;

class HeadCoach : public Person
{
protected:
    string _equipe;
public:
    HeadCoach() = default;

    HeadCoach(string nom, string prenom, string equipe, string imagePath)
        : Person(std::move(nom), std::move(prenom), std::move(imagePath)), _equipe(std::move(equipe)) {}

    // Other getter methods
    const string& getEquipe() const {
        return _equipe;
    }

    vector<int> scoutingReport(int horloge, int nbrChoix, map<int, Match*> matches, map<int, Joueur*> team2, QLabel& Info);
};

int Draft();

#endif // HEADCOACH_HH
