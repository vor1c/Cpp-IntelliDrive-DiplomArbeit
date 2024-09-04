//
// Created by Voric on 11/08/2024.
//

#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "State.h"
#include <iostream>

class MenuState : public State {
public:
    MenuState();

    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    void updateButtonHover(sf::Text& button, const sf::Vector2i& mousePos);
    void initializeButton(sf::Text& button, const sf::Font& font, const std::string& text, const sf::Vector2u& windowSize, float offsetY);
    void loadBackground();
    void changeBackground();

    sf::Font Textfont;
    sf::Font Menufont;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Text playButton;
    sf::Text systemButton;
    sf::Text carButton;
    sf::Text exitButton;
    sf::Text title;
    sf::Text copyrightText;
    sf::Text versionText;
    sf::Text changeBgButton;

    int backgroundIndex;
};

#endif // MENUSTATE_H
