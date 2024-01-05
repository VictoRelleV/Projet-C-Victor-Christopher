#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Solid.h"
#include "Net.h"

#define DIV_18_LN5 11.1840288221

class Ball: public Solid {
public:
    Ball(const sf::RenderWindow& window, Game& game, Net& net, int X, int Y);

    void mouseDown(sf::Event::MouseButtonEvent mouseButton);
    void mouseUp(sf::Event::MouseButtonEvent mouseButton);

    bool isInsideOfNet();

    void updatePosition();
    sf::Sprite& getSprite();

private:
    int ticksElapsed = 0;

    int startX = 0, startY = 0, endX = 0, endY = 0;
    double throwStrength = 0, throwAngle = 0;

    double maxZ = 1;

    bool isDragging = false;
    bool isThrowing = false;
    bool isFalling = false;

    Net& net;
};