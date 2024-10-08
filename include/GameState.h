//
// Created by Voric and tobisdev on 11/08/2024.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../include/State.h"
#include "../include/Car.h"
#include "../include/Game.h"
#include "Wall.h"
class GameState : public State {
public:
    GameState(Game& game, const std::string& levelFile);
    GameState(Game& game) : car(game.getCar()) {
        initializeCar();
    }

    void handleInput(Game& game) override;
    void resetGameState(const std::string& levelFile);
    void loadLevelFromCSV(const std::string &filename);

    void update(Game& game) override;
    void render(Game& game) override;

private:
    Car& car;
    std::vector<Wall> walls;

    void initializeCar();
    bool isPauseKeyPressed(const sf::Event& event) const;
    sf::RectangleShape createRoad(Game& game) const;
};

#endif // GAMESTATE_H
