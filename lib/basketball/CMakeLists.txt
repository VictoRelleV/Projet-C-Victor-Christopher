cmake_minimum_required(VERSION 3.16)
project(BasketballGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        src/Solid.cpp
        src/Net.cpp
        src/Ball.cpp
        src/Game.cpp
        main.cpp
)

target_link_libraries(BasketballGame sfml-graphics sfml-window sfml-system pthread)

install(TARGETS BasketballGame)