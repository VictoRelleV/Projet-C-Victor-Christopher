#include "clickablelabel.hh"
#include "joueur.hh"
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
                    ClickableLabel& PowerForward1, ClickableLabel& Center1, map<int, joueur*> team1) {

    PointGuard1.setPlayerName(team1[1]->getPrenom() + " " + team1[1]->getNom());
    PointGuard1.setAttack(team1[1]->getATQ());
    PointGuard1.setDefense(team1[1]->getDEF());
    PointGuard1.setSpeed(team1[1]->getVIT());
    //PointGuard1.setPosition(team1[1]->getPosition());

    ShootingGuard1.setPlayerName(team1[2]->getPrenom() + " " + team1[2]->getNom());
    ShootingGuard1.setAttack(team1[2]->getATQ());
    ShootingGuard1.setDefense(team1[2]->getDEF());
    ShootingGuard1.setSpeed(team1[2]->getVIT());
    //ShootingGuard1.setPosition(team1[2]->getPosition());

    SmallForward1.setPlayerName(team1[3]->getPrenom() + " " + team1[3]->getNom());
    SmallForward1.setAttack(team1[3]->getATQ());
    SmallForward1.setDefense(team1[3]->getDEF());
    SmallForward1.setSpeed(team1[3]->getVIT());
    //SmallForward1.setPosition(team1[3]->getPosition());

    PowerForward1.setPlayerName(team1[4]->getPrenom() + " " + team1[4]->getNom());
    PowerForward1.setAttack(team1[4]->getATQ());
    PowerForward1.setDefense(team1[4]->getDEF());
    PowerForward1.setSpeed(team1[4]->getVIT());
    //PowerForward1.setPosition(team1[4]->getPosition());

    Center1.setPlayerName(team1[5]->getPrenom() + " " + team1[5]->getNom());
    Center1.setAttack(team1[5]->getATQ());
    Center1.setDefense(team1[5]->getDEF());
    Center1.setSpeed(team1[5]->getVIT());
    //Center1.setPosition(team1[5]->getPosition());
}