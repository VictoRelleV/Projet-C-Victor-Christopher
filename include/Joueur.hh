#ifndef JOUEUR_HH
#define JOUEUR_HH

#include <QLabel>

#include <iostream>
#include <string>
#include <map>
#include <random>
#include <utility>

#include "Joueur.hh"
#include "Match.hh"
#include "question.hh"
#include "Person.hh"

using namespace std;

class Joueur : public Person
{
protected:
    string _position;

    int statAttaque; // Attaque
    int statDefense; // Defense
    int statVitesse; // Vitesse

    int points = 0; // Points

public:
    Joueur(string nom, string prenom, string position, string imagePath, int ATQ, int DEF, int VIT)
        : Person(std::move(nom), std::move(prenom), std::move(imagePath)), _position(std::move(position)), statAttaque(ATQ), statDefense(DEF), statVitesse(VIT)
    {}

    // Other getter methods
    const string& getPosition() const {
        return _position;
    }

    int getStatAttaque() const {
        return statAttaque;
    }

    void setStatAttaque(int stat) {
        statAttaque = stat;
    }

    int getStatDefense() const {
        return statDefense;
    }

    void setStatDefense(int stat) {
        statDefense = stat;
    }

    int getStatVitesse() const {
        return statVitesse;
    }

    void setStatVitesse(int stat) {
        statVitesse = stat;
    }

    void addStat(int stat) {
        statAttaque += stat;
        statDefense += stat;
        statVitesse += stat;
    }

    int getPoints() const {
        return points;
    }

    void setPoints(int newPoints) {
        points = newPoints;
    }

    int operator++(int) {
        ++this->points;
        return this->points;
    }

    int operator+=(int nbPoints) {
        this->points += nbPoints;
        return this->points;
    }

    friend std::ostream& operator<<(std::ostream& os, const Joueur& joueur);

    virtual void atq(Joueur* adversaire, QLabel& Info, vector<Question> questions, map<int, Match*> matches) = 0;

    virtual void def(Joueur* adversaire, QLabel& Info, vector<Question> questions, map<int, Match*> matches) = 0;

    virtual void vit(Joueur* adversaire, QLabel& Info, vector<Question> questions, map<int, Match*> matches) = 0;
};

map<int, Joueur*> createPlayers();
pair<map<int, Joueur*>, map<int, Joueur*>> createTeams(map<int, Joueur*> players);
Joueur* choisirJoueurAuHasard(map<int, Joueur*>& equipe);
Joueur* getMVP(map<int, Joueur*> players);

#endif // JOUEUR_HH