//
// Created by Voric on 11/08/2024.
//

#ifndef DEATHSTATE_H
#define DEATHSTATE_H

#include "../include/State.h"
#include "../include/Game.h"

class DeathState : public State {
public:
    DeathState();

    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    sf::Font font;
    sf::Text deathText;
    sf::Text playAgainButton;
    sf::Text menuButton;

    bool isRestartKeyPressed(const sf::Event& event) const;
    bool isMenuKeyPressed(const sf::Event& event) const;
    void initializeText(sf::Text& text, const std::string& str, unsigned int size, float x, float y);
};

#endif //DEATHSTATE_H

