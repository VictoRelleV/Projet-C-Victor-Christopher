#ifndef CENTER_H
#define CENTER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
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

    void atq(joueur* adversaire, QLabel* Info, vector<Question> questions, map<int, match*> matches) override
    {
        int bonus = 0;
        if(adversaire->getPosition()=="Power Forward"){
            bonus = 2;
        }
        if(this->getATQ()+bonus > adversaire->getDEF()) {
            matches[3]->setScore1(matches[3]->getScore1() + this->getATQ()+bonus-adversaire->getDEF());
            Info->setText(QString("%1 %2 marque %3 points")
                .arg(this->getPrenom().c_str())
                .arg(this->getNom().c_str())
                .arg(this->getATQ()+bonus-adversaire->getDEF()));
            this->setATQ(this->getATQ() - (this->getATQ()+bonus-adversaire->getDEF()));
        } else if (this->getATQ()+bonus < adversaire->getDEF()) {
            matches[3]->setScore2(matches[3]->getScore2() + adversaire->getDEF()-this->getATQ()+bonus);
            Info->setText(QString("%1 %2 marque %3 points")
                .arg(adversaire->getPrenom().c_str())
                .arg(adversaire->getNom().c_str())
                .arg(adversaire->getDEF()-this->getATQ()+bonus));
            adversaire->setDEF(adversaire->getDEF() - (adversaire->getDEF()-this->getATQ()+bonus));
        } else {
            askQuestion(Info, this, matches, questions);
        }
    }

    void def(joueur* adversaire, QLabel* Info, vector<Question> questions, map<int, match*> matches) override
    {
        int bonus = 0;
        if(adversaire->getPosition()=="Power Forward"){
            bonus = 2;
        }
        if(this->getDEF()+bonus > adversaire->getATQ()) {
            matches[3]->setScore1(matches[3]->getScore1() + this->getDEF()+bonus-adversaire->getATQ());
            Info->setText(QString("%1 %2 marque %3 points")
                .arg(this->getPrenom().c_str())
                .arg(this->getNom().c_str())
                .arg(this->getDEF()+bonus-adversaire->getATQ()));
            this->setDEF(this->getDEF() - (this->getDEF()+bonus-adversaire->getATQ()));
        } else if (this->getDEF()+bonus < adversaire->getATQ()) {
            matches[3]->setScore2(matches[3]->getScore2() + adversaire->getATQ()-this->getDEF()+bonus);
            Info->setText(QString("%1 %2 marque %3 points")
                .arg(adversaire->getPrenom().c_str())
                .arg(adversaire->getNom().c_str())
                .arg(adversaire->getATQ()-this->getDEF()+bonus));
            adversaire->setATQ(adversaire->getATQ() - (adversaire->getATQ()-this->getDEF()+bonus));
        } else {
            askQuestion(Info, this, matches, questions);
        }
    }

    void vit(joueur* adversaire, QLabel* Info, vector<Question> questions, map<int, match*> matches) override
    {
        int bonus = 0;
        if(adversaire->getPosition()=="Power Forward"){
            bonus = 2;
        }
        if(this->getVIT()+bonus > adversaire->getVIT()) {
            matches[3]->setScore1(matches[3]->getScore1() + this->getVIT()+bonus-adversaire->getVIT());
            Info->setText(QString("%1 %2 marque %3 points")
                .arg(this->getPrenom().c_str())
                .arg(this->getNom().c_str())
                .arg(this->getVIT()+bonus-adversaire->getVIT()));
            this->setVIT(this->getVIT() - (this->getVIT()+bonus-adversaire->getVIT()));
        } else if (this->getVIT()+bonus < adversaire->getVIT()) {
            matches[3]->setScore2(matches[3]->getScore2() + adversaire->getVIT()-this->getVIT()+bonus);
            Info->setText(QString("%1 %2 marque %3 points")
                .arg(adversaire->getPrenom().c_str())
                .arg(adversaire->getNom().c_str())
                .arg(adversaire->getVIT()-this->getVIT()+bonus));
            adversaire->setVIT(adversaire->getVIT() - (adversaire->getVIT()-this->getVIT()+bonus));
        } else {
            askQuestion(Info, this, matches, questions);
        }
    }
};

#endif // CENTER_H

