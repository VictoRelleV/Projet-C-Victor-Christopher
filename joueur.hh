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

using namespace std;

class joueur
{
protected:
    string _nom;
    string _prenom;
    string _position;
    string _imagePath; // New attribute for image path

    int _ATQ; // Attaque
    int _DEF; // Defense
    int _VIT; // Vitesse

public:

    joueur()
    {
    }

    joueur(string nom, string prenom, string position, string imagePath, int ATQ, int DEF, int VIT)
        : _nom(nom), _prenom(prenom), _position(position), _imagePath(imagePath), _ATQ(ATQ), _DEF(DEF), _VIT(VIT)
    {
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

    const string getName() const {
        return _prenom+" "+_nom;
    }

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

    int getVIT() const {
        return _VIT;
    }

    void atq100()//test
    {
        _ATQ += 100;
    }

    virtual void atq2atq(joueur* adversaire, QLabel* Info, vector<Question> questions, map<int, match*> matches)
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
        }
    }

    virtual void def2atq(joueur* adversaire, QLabel* Info, vector<Question> questions, map<int, match*> matches)
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

map<int, joueur*> createPlayers();
pair<map<int, joueur*>, map<int, joueur*>> createTeams(map<int, joueur*> players);
joueur* choisirJoueurAuHasard(map<int, joueur*>& equipe);
int Action(joueur* joueur1, QLabel* Info);

#endif // JOUEUR_HH