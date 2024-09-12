//
// Created by Voric and tobisdev on 11/08/2024.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../include/State.h"
#include "../include/Car.h"
#include "../include/Game.h"

class GameState : public State {
public:
    GameState(Game& game) : car(game.getCar()) {
        initializeCar();
    }

    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    Car& car;

    void initializeCar();
    bool isPauseKeyPressed(const sf::Event& event) const;
    sf::RectangleShape createRoad(Game& game) const;
};

#endif // GAMESTATE_H
