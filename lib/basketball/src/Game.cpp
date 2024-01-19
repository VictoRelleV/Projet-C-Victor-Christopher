#include <utility>

#include "../include/Game.h"

Game::Game(unsigned int timer, int* externalScore, std::function<void(int)> onScore):
    timer(timer),
    exitOn(timer + std::time(nullptr)),
    onScore(std::move(onScore)),
    net(window, *this, 820, 100),
    basketball(window, *this, net, 935, 800),
    externalScore(externalScore) {

    scoreBoardFont.loadFromFile("lib/basketball/textures/scoreboard_font.ttf");
    textFont.loadFromFile("lib/basketball/textures/text_font.ttf");

    backgroundTexture.loadFromFile("lib/basketball/textures/background.png");
    backgroundSprite.setTexture(backgroundTexture);

    scoreBoardText.setPosition(50, 800);
    scoreBoardText.setFont(scoreBoardFont);
    scoreBoardText.setCharacterSize(256);

    scoreLabelText.setPosition(50, 815);
    scoreLabelText.setFont(textFont);
    scoreLabelText.setCharacterSize(82);
    scoreLabelText.setString("SCORE");

    if (timer > 0) {
        timerText.setPosition(50, 0);
        timerText.setFont(scoreBoardFont);
        timerText.setCharacterSize(256);

        timerLabelText.setPosition(50, 15);
        timerLabelText.setFont(textFont);
        timerLabelText.setCharacterSize(82);
        timerLabelText.setString("TIME LEFT");
    }

    exitText.setPosition(1500, 975);
    exitText.setFont(textFont);
    exitText.setCharacterSize(82);
    exitText.setFillColor(sf::Color::Red);
    exitText.setString("<EXIT>");
}

int Game::run() {
    isRunning = true;

    window.setFramerateLimit(60);

    bool mouseIsClicked = false;
    while (window.isOpen() && !shouldClose) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && !mouseIsClicked) {
                    mouseIsClicked = true;
                    mouseDown(event);
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mouseUp(event);
                    mouseIsClicked = false;
                }
            }
        }

        if (exitOn - std::time(nullptr) <= 0) {
            break;
        }

        window.clear();
        render();
        window.display();
    }

    if (window.isOpen()) window.close();

    isRunning = false;

    std::cout << "Score: " << score << std::endl;
    return score;
}

void Game::kill() {
    shouldClose = true;
}

void Game::render() {
    window.draw(backgroundSprite);

    net.updatePosition();
    window.draw(net.getSprite());

    basketball.updatePosition();
    window.draw(basketball.getSprite());

    window.draw(scoreLabelText);
    scoreBoardText.setString(getScoreString());
    window.draw(scoreBoardText);

    if (timer > 0) {
        window.draw(timerLabelText);
        if (startTimer) {
            timerText.setString(std::to_string(exitOn - std::time(nullptr)));
        } else {
            timerText.setString(std::to_string(timer));
        }
        window.draw(timerText);
    }

    window.draw(exitText);
}

void Game::mouseDown(sf::Event& event) {
    basketball.mouseDown(event.mouseButton);
    if (!startTimer) {
        startTimer = true;
        exitOn = timer + std::time(nullptr);
    }
}

void Game::mouseUp(sf::Event& event) {
    basketball.mouseUp(event.mouseButton);

    if ((float)event.mouseButton.x >= exitText.getGlobalBounds().left && (float)event.mouseButton.y >= exitText.getGlobalBounds().top) {
        kill();
    }
}

void Game::incrementScore() {
    score++;

    if (externalScore != nullptr) *externalScore = score;
    if (onScore != nullptr) onScore(score);
}

int Game::getScore() {
    return score;
}

std::string Game::getScoreString() {
    std::string stringScore;

    if (score < 100) {
        stringScore = "0" + stringScore;
    }
    if (score < 10) {
        stringScore = "0" + stringScore;
    }
    stringScore = stringScore + std::to_string(score);

    return stringScore;
}

bool Game::getIsRunning() {
    return isRunning;
}
