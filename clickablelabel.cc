#include "clickablelabel.hh"
#include "joueur.hh"
#include <QMenu>
#include <QAction>
#include <iostream>

extern int poste;
extern int action1;

ClickableLabel::ClickableLabel(const QString& playerName, int attack, int defense, int speed, int position, QWidget* parent, QLabel* infoLabel)
    : QLabel(parent), playerName(playerName.toStdString()), attack(attack), defense(defense), speed(speed), position(position), infoLabel(infoLabel) {
}

void ClickableLabel::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        QMenu menu(static_cast<QWidget*>(this));
        QAction* attackAction = menu.addAction("ATQ");
        QAction* defenseAction = menu.addAction("DEF");
        QAction* speedAction = menu.addAction("VIT");

        QAction* selectedAction = menu.exec(event->globalPos());

        if (selectedAction == attackAction) {
            infoLabel->setText(QString::number(attack));
            std::cout << "ATQ " << this->playerName << this->attack << std::endl;
            action1 = 1;
        } else if (selectedAction == defenseAction) {
            infoLabel->setText(QString::number(defense));
            std::cout << "DEF " << this->playerName << this->defense << std::endl;
            action1 = 2;
        } else if (selectedAction == speedAction) {
            infoLabel->setText(QString::number(speed));
            std::cout << "VIT " << this->playerName << this->speed << std::endl;
            action1 = 3;
        }
        poste = this->position;
    }
}

