#ifndef CLICKABLELABEL_HH
#define CLICKABLELABEL_HH

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <iostream>

#include "Joueur.hh"

class ClickableLabel : public QLabel {
public:
    ClickableLabel(const QString& playerName, int attack, int defense, int speed, int position, QWidget& parent, QLabel& infoLabel);

    int getAttack() const {
        return attack;
    }

    int getDefense() const {
        return defense;
    }

    int getSpeed() const {
        return speed;
    }

    int getPosition() const {
        return position;
    }

    const std::string& getPlayerName() const {
        return playerName;
    }

    void setAttack(int attack) {
        this->attack = attack;
    }

    void setDefense(int defense) {
        this->defense = defense;
    }

    void setSpeed(int speed) {
        this->speed = speed;
    }

    void setPosition(int position) {
        this->position = position;
    }

    void setPlayerName(const std::string& playerName) {
        this->playerName = playerName;
    }

protected:
    void mousePressEvent(QMouseEvent *event) override;
    
private:
    std::string playerName;
    int attack;
    int defense;
    int speed;
    int position;
    QLabel& infoLabel;
};

void recreateLabels(ClickableLabel& PointGuard1, ClickableLabel& ShootingGuard1, ClickableLabel& SmallForward1,
                    ClickableLabel& PowerForward1, ClickableLabel& Center1, map<int, Joueur*> team1);

#endif
