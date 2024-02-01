#ifndef JOUEUR_HH
#define JOUEUR_HH

#include <QLabel>

#include <iostream>
#include <string>
#include <map>
#include <random>

#include "joueur.hh"
#include "match.hh"
#include "question.hh"
#include "person.hh"

using namespace std;

class joueur : public person
{
protected:
    string _position;

    int _ATQ; // Attaque
    int _DEF; // Defense
    int _VIT; // Vitesse

    int _points = 0; // Points

public:

    joueur()
    {
    }

    joueur(string nom, string prenom, string position, string imagePath, int ATQ, int DEF, int VIT)
        : person(nom, prenom, imagePath), _position(position), _ATQ(ATQ), _DEF(DEF), _VIT(VIT)
    {
    }

    // Other getter methods
    const string& getPosition() const {
        return _position;
    }

    int getATQ() const {
        return _ATQ;
    }

    void setATQ(int ATQ) {
        _ATQ = ATQ;
    }

    int getDEF() const {
        return _DEF;
    }

    void setDEF(int DEF) {
        _DEF = DEF;
    }

    int getVIT() const {
        return _VIT;
    }

    void setVIT(int VIT) {
        _VIT = VIT;
    }

    void addSTAT(int STAT) {
        _ATQ += STAT;
        _DEF += STAT;
        _VIT += STAT;
    }

    int getPoints() const {
        return _points;
    }

    void setPoints(int points) {
        _points = points;
    }

    friend std::ostream& operator<<(std::ostream& os, const joueur& joueur);

    joueur operator++(int) {
        // Logique pour l'incrémentation postfixe
        joueur temp(*this);
        ++_points;
        return temp;
    }

    virtual void atq(joueur* adversaire, QLabel& Info, vector<Question> questions, map<int, match*> matches)
    {
        if(this->getATQ() > adversaire->getDEF()) {
            matches[3]->setScore1(matches[3]->getScore1() + this->getATQ()-adversaire->getDEF());
            Info.setText(QString("%1 %2 marque %3 points")
                .arg(this->getPrenom().c_str())
                .arg(this->getNom().c_str())
                .arg(this->getATQ()-adversaire->getDEF()));
        } else if (this->getATQ() < adversaire->getDEF()) {
            matches[3]->setScore2(matches[3]->getScore2() + adversaire->getDEF()-this->getATQ());
            Info.setText(QString("%1 %2 marque %3 points")
                .arg(adversaire->getPrenom().c_str())
                .arg(adversaire->getNom().c_str())
                .arg(adversaire->getDEF()-this->getATQ()));
        }
    }

    virtual void def(joueur* adversaire, QLabel& Info, vector<Question> questions, map<int, match*> matches)
    {
        if(this->getDEF() > adversaire->getATQ()) {
            matches[3]->setScore1(matches[3]->getScore1() + this->getDEF()-adversaire->getATQ());
            Info.setText(QString("%1 %2 marque %3 points")
                .arg(this->getPrenom().c_str())
                .arg(this->getNom().c_str())
                .arg(this->getDEF()-adversaire->getATQ()));
        } else if (this->getDEF() < adversaire->getATQ()) {
            matches[3]->setScore2(matches[3]->getScore2() + adversaire->getATQ()-this->getDEF());
            Info.setText(QString("%1 %2 marque %3 points")
                .arg(adversaire->getPrenom().c_str())
                .arg(adversaire->getNom().c_str())
                .arg(adversaire->getATQ()-this->getDEF()));
        }
    }

    virtual void vit(joueur* adversaire, QLabel& Info, vector<Question> questions, map<int, match*> matches)
    {
        if(this->getVIT() > adversaire->getVIT()) {
            matches[3]->setScore1(matches[3]->getScore1() + this->getVIT()-adversaire->getVIT());
            Info.setText(QString("%1 %2 marque %3 points")
                .arg(this->getPrenom().c_str())
                .arg(this->getNom().c_str())
                .arg(this->getVIT()-adversaire->getVIT()));
        } else if (this->getVIT() < adversaire->getVIT()) {
            matches[3]->setScore2(matches[3]->getScore2() + adversaire->getVIT()-this->getVIT());
            Info.setText(QString("%1 %2 marque %3 points")
                .arg(adversaire->getPrenom().c_str())
                .arg(adversaire->getNom().c_str())
                .arg(adversaire->getVIT()-this->getVIT()));
        }
    }
};

map<int, joueur*> createPlayers();
pair<map<int, joueur*>, map<int, joueur*>> createTeams(map<int, joueur*> players);
joueur* choisirJoueurAuHasard(map<int, joueur*>& equipe);
joueur* getMVP(map<int, joueur*> players);

#endif // JOUEUR_HH