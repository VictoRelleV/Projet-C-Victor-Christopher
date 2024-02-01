#include "../include/PointGuard.hh"

void PointGuard::printInfos() {
    cout << "Nom : " << this->getNom() << endl;
    cout << "Prenom : " << this->getPrenom() << endl;
    cout << "Position : " << this->getPosition() << endl;
    cout << "Image : " << this->getImagePath() << endl;
    cout << "ATQ : " << this->getStatAttaque() << endl;
    cout << "DEF : " << this->getStatDefense() << endl;
    cout << "VIT : " << this->getStatVitesse() << endl;
}


void PointGuard::atq(Joueur *adversaire, QLabel &Info, vector<Question> questions, map<int, Match *> matches) {
    int bonus = 0;
    if(adversaire->getPosition()=="Center"){
        bonus = 2;
    }
    if(this->getStatAttaque() + bonus > adversaire->getStatDefense()) {
        matches[3]->setScore1(matches[3]->getScore1() + this->getStatAttaque() + bonus -
                              adversaire->getStatDefense());
        this->setPoints(this->getPoints() + this->getStatAttaque() + bonus - adversaire->getStatDefense());
        Info.setText(QString("%1 %2 marque %3 points")
                             .arg(this->getPrenom().c_str())
                             .arg(this->getNom().c_str())
                             .arg(this->getStatAttaque() + bonus - adversaire->getStatDefense()));
        this->addStat(-(this->getStatAttaque() + bonus - adversaire->getStatDefense()));
    } else if (this->getStatAttaque() + bonus < adversaire->getStatDefense()) {
        matches[3]->setScore2(matches[3]->getScore2() + adversaire->getStatDefense() - (this->getStatAttaque() + bonus));
        adversaire->setPoints(adversaire->getPoints() + adversaire->getStatDefense() - (this->getStatAttaque() + bonus));
        Info.setText(QString("%1 %2 marque %3 points")
                             .arg(adversaire->getPrenom().c_str())
                             .arg(adversaire->getNom().c_str())
                             .arg(adversaire->getStatDefense() - (this->getStatAttaque() + bonus)));
        adversaire->setStatDefense(
                adversaire->getStatDefense() - (adversaire->getStatDefense() - (this->getStatAttaque() + bonus)));
    } else {
        askQuestion(Info, this, matches, questions);
    }
}


void PointGuard::def(Joueur *adversaire, QLabel &Info, vector<Question> questions, map<int, Match *> matches) {
    int bonus = 0;
    if(adversaire->getPosition()=="Center"){
        bonus = 2;
    }
    if(this->getStatDefense() + bonus > adversaire->getStatAttaque()) {
        matches[3]->setScore1(matches[3]->getScore1() + this->getStatDefense() + bonus - adversaire->getStatAttaque());
        this->setPoints(this->getPoints() + this->getStatDefense() + bonus - adversaire->getStatAttaque());
        Info.setText(QString("%1 %2 marque %3 points")
                             .arg(this->getPrenom().c_str())
                             .arg(this->getNom().c_str())
                             .arg(this->getStatDefense() + bonus - adversaire->getStatAttaque()));
        this->addStat(-(this->getStatDefense() + bonus - adversaire->getStatAttaque()));
    } else if (this->getStatDefense() + bonus < adversaire->getStatAttaque()) {
        matches[3]->setScore2(matches[3]->getScore2() + adversaire->getStatAttaque() - (this->getStatDefense() + bonus));
        adversaire->setPoints(adversaire->getPoints() + adversaire->getStatAttaque() - (this->getStatDefense() + bonus));
        Info.setText(QString("%1 %2 marque %3 points")
                             .arg(adversaire->getPrenom().c_str())
                             .arg(adversaire->getNom().c_str())
                             .arg(adversaire->getStatAttaque() - (this->getStatDefense() + bonus)));
        adversaire->setStatAttaque(
                adversaire->getStatAttaque() - (adversaire->getStatAttaque() - (this->getStatDefense() + bonus)));
    } else {
        askQuestion(Info, this, matches, questions);
    }
}

void PointGuard::vit(Joueur *adversaire, QLabel &Info, vector<Question> questions, map<int, Match *> matches) {
    int bonus = 0;
    if(adversaire->getPosition()=="Center"){
        bonus = 2;
    }
    if(this->getStatVitesse() + bonus > adversaire->getStatVitesse()) {
        matches[3]->setScore1(matches[3]->getScore1() + this->getStatVitesse() + bonus - adversaire->getStatVitesse());
        this->setPoints(this->getPoints() + this->getStatVitesse() + bonus - adversaire->getStatVitesse());
        Info.setText(QString("%1 %2 marque %3 points")
                             .arg(this->getPrenom().c_str())
                             .arg(this->getNom().c_str())
                             .arg(this->getStatVitesse() + bonus - adversaire->getStatVitesse()));
        this->addStat(-(this->getStatVitesse() + bonus - adversaire->getStatVitesse()));
    } else if (this->getStatVitesse() + bonus < adversaire->getStatVitesse()) {
        matches[3]->setScore2(matches[3]->getScore2() + adversaire->getStatVitesse() - (this->getStatVitesse() + bonus));
        adversaire->setPoints(adversaire->getPoints() + adversaire->getStatVitesse() - (this->getStatVitesse() + bonus));
        Info.setText(QString("%1 %2 marque %3 points")
                             .arg(adversaire->getPrenom().c_str())
                             .arg(adversaire->getNom().c_str())
                             .arg(adversaire->getStatVitesse() - (this->getStatVitesse() + bonus)));
        adversaire->setStatVitesse(
                adversaire->getStatVitesse() - (adversaire->getStatVitesse() - (this->getStatVitesse() + bonus)));
    } else {
        askQuestion(Info, this, matches, questions);
    }
}
