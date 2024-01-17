#include <iostream>
#include <string>
#include <map>
#include "joueur.hh"

#include <QLabel>

using namespace std;

class pointguard : public joueur
{
public:
    pointguard() {}

    pointguard(string nom, string prenom, string position, string imagePath, int ATQ, int DEF, int VIT)
        : joueur(nom, prenom, position, imagePath, ATQ, DEF, VIT)
    {
    }

    /*
    void atq2atq(joueur* adversaire, QLabel* Info)
    {
        if(this->getATQ() > adversaire->getATQ()) {
            Info->setText(QString("%1 %2 marque %3 points")
                .arg(this->getPrenom().c_str())
                .arg(this->getNom().c_str())
                .arg(this->getATQ()-adversaire->getATQ()));
        } else if (this->getATQ() < adversaire->getATQ()) {
            Info->setText(QString("%1 %2 marque %3 points")
                .arg(adversaire->getPrenom().c_str())
                .arg(adversaire->getNom().c_str())
                .arg(adversaire->getATQ()-this->getATQ()));
        } else {
            Info->setText(QString("%1 %2 marque %3 points")
                .arg(this->getPrenom().c_str())
                .arg(this->getNom().c_str())
                .arg(this->getATQ()));
        }
    }
    */   
};
