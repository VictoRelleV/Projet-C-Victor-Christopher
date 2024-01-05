#include <valarray>
#include "../include/Net.h"
#include "../include/Game.h"

Net::Net(const sf::RenderWindow &window, Game &game, int X, int Y): Solid(window, game, X, Y) {
    texture.loadFromFile("lib/basketball/textures/net.png");
    sprite.setTexture(texture);
}

void Net::updatePosition() {
    if (game.getScore() >= 3) {
        if (movingLeft) {
            X -= (int)sqrt(game.getScore());
            if (X <= 0) {
                movingLeft = false;
            }
        } else {
            X += (int)sqrt(game.getScore());
            if (((float)X + sprite.getGlobalBounds().width) >= (float)window.getSize().x) {
                movingLeft = true;
            }
        }
    }
    if (game.getScore() >= 6) {
        if (movingDown) {
            Y += (int)sqrt(game.getScore());
            if (((float)Y + sprite.getGlobalBounds().height) >= (window.getSize().y-200.0)) {
                movingDown = false;
            }
        } else {
            Y -= (int)sqrt(game.getScore());
            if (Y <= 0) {
                movingDown = true;
            }
        }
    }
    sprite.setPosition((float)X, (float)Y);
}

sf::Sprite& Net::getSprite() {
    return sprite;
}
