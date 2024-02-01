#ifndef POWERFORWARD_H
#define POWERFORWARD_H

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include "Joueur.hh"
#include "Match.hh"
#include "question.hh"
#include "fonctions.hh"

#include <QLabel>

using namespace std;

class PowerForward : public Joueur
{
public:

    PowerForward() = default;

    PowerForward(string nom, string prenom, string position, string imagePath, int ATQ, int DEF, int VIT)
        : Joueur(std::move(nom), std::move(prenom), std::move(position), std::move(imagePath), ATQ, DEF, VIT) {}

    void atq(Joueur* adversaire, QLabel& Info, vector<Question> questions, map<int, Match*> matches) override;

    void def(Joueur* adversaire, QLabel& Info, vector<Question> questions, map<int, Match*> matches) override;

    void vit(Joueur* adversaire, QLabel& Info, vector<Question> questions, map<int, Match*> matches) override;
};

#endif // POWERFORWARD_H