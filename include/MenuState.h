//
// Created by Voric on 11/08/2024.
//

#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class MenuState : public State {
public:
    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    void updateButtonHover(sf::Text& button, const sf::Vector2i& mousePos);
    void initializeButton(sf::Text& button, const sf::Font& font, const std::string& text, const sf::Vector2u& windowSize, float offsetY);

    sf::Font Textfont;
    sf::Font Menufont;
    sf::Text title;
    sf::Text playButton;
    sf::Text systemButton;
    sf::Text infoButton;
    sf::Text copyrightText;
    sf::Text versionText;
    sf::Text exitButton;
};

#endif