#pragma once

#include "Solid.h"

class Net: public Solid {
public:
    Net(const sf::RenderWindow& window, Game& game, int X, int Y);

    void updatePosition();
    sf::Sprite& getSprite();

protected:
    bool movingLeft = true;
    bool movingDown = true;
};