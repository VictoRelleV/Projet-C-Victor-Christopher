#pragma once

#include <ctime>
#include <SFML/Graphics.hpp>
#include <string>
#include "Net.h"
#include "Ball.h"

class Game {
public:
    Game(unsigned int timer = 0, int* externalScore = nullptr, std::function<void(int)> onScore = nullptr);

    int run();
    void kill();
    void render();
    void mouseDown(sf::Event& event);
    void mouseUp(sf::Event& event);

    void incrementScore();
    int getScore();
    std::string getScoreString();
    bool getIsRunning();

private:
    std::function<void(int)> onScore;

    unsigned int timer;
    unsigned int exitOn = -1;

    int score = 0;
    int* externalScore;

    bool startTimer = false;
    bool isRunning = false;
    bool shouldClose = false;

    sf::RenderWindow window{ { 1920, 1080 }, "Basketball Game", sf::Style::Fullscreen };
    Net net;
    Ball basketball;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Font scoreBoardFont;
    sf::Font textFont;

    sf::Text scoreBoardText;
    sf::Text scoreLabelText;
    sf::Text timerText;
    sf::Text timerLabelText;
    sf::Text exitText;
};