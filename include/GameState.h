//
// Created by Voric and tobisdev on 11/08/2024.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Car.h"
#include "Game.h"

class GameState : public State {
public:
    GameState(Game& game) : car(game.getCar()) {};
    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    Car &car;
};

#endif //GAMESTATE_H
