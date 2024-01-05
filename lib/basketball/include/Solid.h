#pragma once

#include <SFML/Graphics.hpp>
#include "Game.fwd.h"

class Solid {
public:
    Solid(const sf::RenderWindow& window, Game& game, int X, int Y);

    virtual const sf::Sprite& getSprite() const;

protected:
    int initialX, X;
    int initialY, Y;

    const sf::RenderWindow& window;
    Game& game;
    sf::Texture texture;
    sf::Sprite sprite;
};
