#ifndef CENTER_H
#define CENTER_H

#include <iostream>
#include <string>
#include <map>
#include "joueur.hh"
#include "match.hh"
#include "question.hh"
#include "fonctions.hh"

#include <QLabel>


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

    void atq2atq(joueur* adversaire, QLabel* Info, vector<Question> questions, map<int, match*> matches) override
    {
        if(this->getATQ() > adversaire->getATQ()) {
            matches[3]->setScore1(matches[3]->getScore1() + this->getATQ()-adversaire->getATQ());
            Info->setText(QString("%1 %2 marque %3 points")
                .arg(this->getPrenom().c_str())
                .arg(this->getNom().c_str())
                .arg(this->getATQ()-adversaire->getATQ()));
        } else if (this->getATQ() < adversaire->getATQ()) {
            matches[3]->setScore2(matches[3]->getScore2() + adversaire->getATQ()-this->getATQ());
            Info->setText(QString("%1 %2 marque %3 points")
                .arg(adversaire->getPrenom().c_str())
                .arg(adversaire->getNom().c_str())
                .arg(adversaire->getATQ()-this->getATQ()));
        } else {
            askQuestion(Info, this, matches, questions);
        }
    }

    void def2atq(joueur* adversaire, QLabel* Info, vector<Question> questions, map<int, match*> matches) override
    {
        if(this->getDEF() > adversaire->getATQ()) {
            matches[3]->setScore2(matches[3]->getScore2() - this->getDEF()+adversaire->getATQ());
            Info->setText(QString("%1 perd %2 points")
                .arg(matches[3]->getEquipe2().c_str())
                .arg(this->getDEF()-adversaire->getATQ()));
        } else if (this->getDEF() < adversaire->getATQ()) {
            matches[3]->setScore2(matches[3]->getScore2() + adversaire->getATQ()-this->getDEF());
            Info->setText(QString("%1 %2 marque %3 points")
                .arg(adversaire->getPrenom().c_str())
                .arg(adversaire->getNom().c_str())
                .arg(adversaire->getATQ()-this->getDEF()));
        }
    }
};

#endif // CENTER_H

