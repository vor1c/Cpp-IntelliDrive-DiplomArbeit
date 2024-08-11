//
// Created by Voric on 11/08/2024.
//

#ifndef STATE_H
#define STATE_H


#include <SFML/Graphics.hpp>
#include <memory>

class Game;

class State {
public:
    virtual void handleInput(Game& game) = 0;
    virtual void update(Game& game) = 0;
    virtual void render(Game& game) = 0;
};


#endif //STATE_H
