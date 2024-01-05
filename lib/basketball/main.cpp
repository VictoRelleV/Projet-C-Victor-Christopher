#include <pthread.h>
#include "include/Game.h"

int gameScore = 0;
Game game(30, &gameScore);

void* updateScore(void* args) {
    gameScore = game.run();

    std::cout << "The game has ended with score " << gameScore << std::endl;
    
    return nullptr;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, nullptr, updateScore, nullptr);

    pthread_join(thread, nullptr);

    return 0;
}