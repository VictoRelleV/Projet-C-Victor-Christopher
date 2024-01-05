#include "../include/Solid.h"
#include "../include/Game.h"

Solid::Solid(const sf::RenderWindow &window, Game& game, int X, int Y): window(window), game(game), initialX(X), X(X), initialY(Y), Y(Y) {
    sprite.setPosition((float)initialX, (float)initialY);
}

const sf::Sprite &Solid::getSprite() const {
    return sprite;
}
