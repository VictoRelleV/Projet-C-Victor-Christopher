#ifndef POINTGUARD_H
#define POINTGUARD_H

#include <iostream>
#include <string>
#include <map>
#include "Joueur.hh"
#include "Match.hh"
#include "question.hh"
#include "fonctions.hh"

#include <QLabel>
#include <utility>

using namespace std;

class PointGuard : public Joueur
{
public:
    PointGuard() = default;

    PointGuard(string nom, string prenom, string position, string imagePath, int ATQ, int DEF, int VIT)
        : Joueur(std::move(nom), std::move(prenom), std::move(position), std::move(imagePath), ATQ, DEF, VIT) {}

    void printInfos();

    void atq(Joueur* adversaire, QLabel& Info, vector<Question> questions, map<int, Match*> matches) override;

    void def(Joueur* adversaire, QLabel& Info, vector<Question> questions, map<int, Match*> matches) override;

    void vit(Joueur* adversaire, QLabel& Info, vector<Question> questions, map<int, Match*> matches) override;
};

#endif // POINTGUARD_H