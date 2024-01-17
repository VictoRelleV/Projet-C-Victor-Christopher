#ifndef CLICKABLELABEL_HH
#define CLICKABLELABEL_HH

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <iostream>

#include "joueur.hh"

class ClickableLabel : public QLabel {
public:
    ClickableLabel(const QString& playerName, int attack, int defense, int speed, int position, QWidget* parent = nullptr, QLabel* infoLabel = nullptr);

    int getPosition() const {
        return position;
    }

protected:
    void mousePressEvent(QMouseEvent *event) override;
    
private:
    std::string playerName;
    int attack;
    int defense;
    int speed;
    int position;
    QLabel* infoLabel; // Ajout du membre infoLabel
};

#endif
