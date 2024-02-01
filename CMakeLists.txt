cmake_minimum_required(VERSION 3.16)
project(OlympicBasketball)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        src/Center.cc
        src/ClickableLabel.cc
        src/fonctions.cc
        src/HeadCoach.cc
        include/Jeu.hh
        src/Joueur.cc
        src/Match.cc
        include/Person.hh
        src/PointGuard.cc
        src/PowerForward.cc
        src/question.cc
        src/ShootingGuard.cc
        src/SmallForward.cc
        lib/basketball/src/Solid.cpp
        lib/basketball/src/Net.cpp
        lib/basketball/src/Ball.cpp
        lib/basketball/src/Game.cpp
        main.cc
)

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
target_link_libraries(OlympicBasketball Qt5::Widgets Qt5::Core Qt5::Gui sfml-graphics sfml-window sfml-system)
install(TARGETS OlympicBasketball)