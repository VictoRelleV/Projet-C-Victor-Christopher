#include "../include/ClickableLabel.hh"
#include "../include/Joueur.hh"
#include <QMenu>
#include <QAction>
#include <iostream>

extern int poste;
extern int action1;

ClickableLabel::ClickableLabel(const QString& playerName, int attack, int defense, int speed, int position, QWidget& parent, QLabel& infoLabel)
    : QLabel(&parent), playerName(playerName.toStdString()), attack(attack), defense(defense), speed(speed), position(position), infoLabel(infoLabel) {
}

void ClickableLabel::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        QMenu menu(static_cast<QWidget*>(this));
        QAction* attackAction = menu.addAction("ATQ");
        QAction* defenseAction = menu.addAction("DEF");
        QAction* speedAction = menu.addAction("VIT");

        QAction* selectedAction = menu.exec(event->globalPos());

        if (selectedAction == attackAction) {
            infoLabel.setText(QString("%1 utilise son ATQ: %3")
                                    .arg(this->playerName.c_str())
                                    .arg(this->attack));
            action1 = 1;
        } else if (selectedAction == defenseAction) {
            infoLabel.setText(QString("%1 utilise sa DEF: %3")
                                    .arg(this->playerName.c_str())
                                    .arg(this->defense));
            action1 = 2;
        } else if (selectedAction == speedAction) {
            infoLabel.setText(QString("%1 utilise sa VIT: %3")
                                    .arg(this->playerName.c_str())
                                    .arg(this->speed));
            action1 = 3;
        }
        poste = this->position;
    }
}

void recreateLabels(ClickableLabel& PointGuard1, ClickableLabel& ShootingGuard1, ClickableLabel& SmallForward1,
                    ClickableLabel& PowerForward1, ClickableLabel& Center1, map<int, Joueur*> team1) {

    PointGuard1.setPlayerName(team1[1]->getPrenom() + " " + team1[1]->getNom());
    PointGuard1.setAttack(team1[1]->getStatAttaque());
    PointGuard1.setDefense(team1[1]->getStatDefense());
    PointGuard1.setSpeed(team1[1]->getStatVitesse());
    //PointGuard1.setPosition(team1[1]->getPosition());

    ShootingGuard1.setPlayerName(team1[2]->getPrenom() + " " + team1[2]->getNom());
    ShootingGuard1.setAttack(team1[2]->getStatAttaque());
    ShootingGuard1.setDefense(team1[2]->getStatDefense());
    ShootingGuard1.setSpeed(team1[2]->getStatVitesse());
    //ShootingGuard1.setPosition(team1[2]->getPosition());

    SmallForward1.setPlayerName(team1[3]->getPrenom() + " " + team1[3]->getNom());
    SmallForward1.setAttack(team1[3]->getStatAttaque());
    SmallForward1.setDefense(team1[3]->getStatDefense());
    SmallForward1.setSpeed(team1[3]->getStatVitesse());
    //SmallForward1.setPosition(team1[3]->getPosition());

    PowerForward1.setPlayerName(team1[4]->getPrenom() + " " + team1[4]->getNom());
    PowerForward1.setAttack(team1[4]->getStatAttaque());
    PowerForward1.setDefense(team1[4]->getStatDefense());
    PowerForward1.setSpeed(team1[4]->getStatVitesse());
    //PowerForward1.setPosition(team1[4]->getPosition());

    Center1.setPlayerName(team1[5]->getPrenom() + " " + team1[5]->getNom());
    Center1.setAttack(team1[5]->getStatAttaque());
    Center1.setDefense(team1[5]->getStatDefense());
    Center1.setSpeed(team1[5]->getStatVitesse());
    //Center1.setPosition(team1[5]->getPosition());
}