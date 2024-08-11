//
// Created by Voric on 11/08/2024.
//

#ifndef GAME_H
#define GAME_H


#include <SFML/Graphics.hpp>
#include "State.h"
#include <memory>

class Game {
public:
    Game();
    void run();

    void pushState(std::shared_ptr<State> state);
    void popState();
    void changeState(std::shared_ptr<State> state);

    std::shared_ptr<State> getCurrentState();

    sf::RenderWindow window;

private:
    std::vector<std::shared_ptr<State>> states;
};


#endif //GAME_H
