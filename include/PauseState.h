//
// Created by Voric on 11/08/2024.
//

#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include <iostream>
#include "../include/State.h"
#include "../include/Game.h"
#include "../include/ResourceManager.h"
#include "../include/MenuState.h"

class PauseState : public State {
public:
    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    sf::Font font;
    sf::Text pauseText;
    sf::Text resumeButton;
    sf::Text menuButton;
};

#endif //PAUSESTATE_H
