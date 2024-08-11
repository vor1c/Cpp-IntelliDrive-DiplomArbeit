//
// Created by Voric on 11/08/2024.
//

#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "Game.h"
#include <iostream>

class MenuState : public State {

public:
    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    sf::Font font;
    sf::Text title;
    sf::Text playButton;
};


#endif //MENUSTATE_H
