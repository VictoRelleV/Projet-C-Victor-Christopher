#include "../include/Ball.h"
#include "../include/Game.h"

Ball::Ball(const sf::RenderWindow& window, Game& game, Net& net, int X, int Y): Solid(window, game, X, Y), net(net) {
    texture.loadFromFile("lib/basketball/textures/basketball.png");
    sprite.setTexture(texture);
}

void Ball::mouseDown(sf::Event::MouseButtonEvent mouseButton) {
    if (isThrowing) return;

    if ((float)mouseButton.x >= (sprite.getGlobalBounds().left-100) && (float)mouseButton.x <= (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width + 100) &&
        (float)mouseButton.y >= (sprite.getGlobalBounds().top-100) && (float)mouseButton.y <= (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height + 100)) {
        isDragging = true;
        startX = (int)(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width*0.5);
        startY = (int)(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height*0.5);
    }
}

void Ball::mouseUp(sf::Event::MouseButtonEvent mouseButton) {
    if (isThrowing || !isDragging) return;
    isDragging = false;

    endX = mouseButton.x;
    endY = mouseButton.y;

    if (endY > startY) return;

    double throwAmplitude = sqrt(pow(startX - endX, 2) + pow(startY - endY, 2));
    throwStrength = log(throwAmplitude)*DIV_18_LN5;

    if (throwStrength > 0) {
        throwAngle = M_PI_2 - acos((endX - startX) / throwAmplitude);

        if (throwAngle >= -M_PI_2 && throwAngle <= M_PI_2) {
            isThrowing = true;
        }
    }
}

bool Ball::isInsideOfNet() {
    bool leftBound = sprite.getGlobalBounds().left >= (net.getSprite().getGlobalBounds().left + 0.20*net.getSprite().getGlobalBounds().width);
    bool rightBound = (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) <= (net.getSprite().getGlobalBounds().left + 0.80*net.getSprite().getGlobalBounds().width);
    bool upperBound = sprite.getGlobalBounds().top >= (net.getSprite().getGlobalBounds().top + 0.5*net.getSprite().getGlobalBounds().height);
    bool lowerBound = (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) <= (net.getSprite().getGlobalBounds().top + net.getSprite().getGlobalBounds().height);

    return leftBound && rightBound && upperBound && lowerBound;
}

void Ball::updatePosition() {
    double Z = 0;
    if (isThrowing) {
        Y = (int) (initialY + pow(ticksElapsed, 2) / 1.2 - (throwStrength) * sin(M_PI_4) * ticksElapsed);
        X = (int) (initialX + (throwStrength / 4) * sin(throwAngle) * ticksElapsed);

        Z = throwStrength * cos(throwAngle) * ticksElapsed;

        if (maxZ == 1) {
            double delta = pow((throwStrength) * sin(M_PI_4), 2) + 4 * window.getSize().y;
            double maxTicks = ((throwStrength) * sin(M_PI_4) + sqrt(delta)) / 2.0;
            maxZ = throwStrength * cos(throwAngle) * maxTicks;
        }

        if (!isFalling && ticksElapsed > 0) {
            int previousY = (int) (initialY + pow((ticksElapsed - 1), 2) / 1.2 -
                                   (throwStrength) * sin(M_PI_4) * (ticksElapsed - 1));
            isFalling = Y > previousY;
        }

        bool outOfBounds = Y > 0 && Y >= window.getSize().y;
        bool scored = isFalling && isInsideOfNet();
        if (outOfBounds || scored) {
            if (scored) game.incrementScore();

            Y = initialY;
            X = initialX;
            maxZ = 1;
            isThrowing = false;
            isFalling = false;
            ticksElapsed = 0;
        } else {
            ticksElapsed++;
        }
    }

    sprite.setPosition((float) X, (float) Y);
    sprite.setScale((float) (1 - 0.7 * (Z / maxZ)), (float) (1 - 0.7 * (Z / maxZ)));
}

sf::Sprite& Ball::getSprite() {
    return sprite;
}