//
// Created by Voric on 11/08/2024.
//

#ifndef DEATHSTATE_H
#define DEATHSTATE_H

#include "State.h"
#include "Game.h"

class DeathState : public State {
public:
    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    sf::Font font;
    sf::Text deathText;
    sf::Text playAgainButton;
    sf::Text menuButton;
};

#endif //DEATHSTATE_H
