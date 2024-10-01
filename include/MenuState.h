//
// Created by Voric on 11/08/2024.
//

#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "Game.h"
#include "../include/LevelCreator.h"

class MenuState : public State {
public:
    MenuState();

    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:

    void initializeButton(sf::Text& button, const sf::Font& font, const std::string& text, const sf::Vector2u& windowSize, float offsetY);
    void initializeText(sf::Text& textItem, const sf::Font& font, const std::string& text, unsigned int size, float x, float y);
    bool loadFont(sf::Font& font, const std::string& fontPath);
    void loadBackground();
    void changeBackground();
    void updateButtonHover(sf::Text& button, const sf::Vector2i& mousePos);
    void handleMouseInput(Game& game);


    sf::Font Textfont;
    sf::Font Menufont;
    sf::Text playButton;
    sf::Text systemButton;
    sf::Text carButton;
    sf::Text exitButton;
    sf::Text changeBgButton;
    sf::Text levelEditorButton;
    sf::Text title;
    sf::Text copyrightText;
    sf::Text versionText;


    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    int backgroundIndex;
};

#endif // MENUSTATE_H
