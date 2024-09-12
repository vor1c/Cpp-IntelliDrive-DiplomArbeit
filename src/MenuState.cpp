//
// Created by Voric on 11/08/2024.
//

#include "../include/MenuState.h"

#include "CarChooseState.h"
#include "../include/GameState.h"
#include "../include/ResourceManager.h"

MenuState::MenuState()
    : backgroundIndex(1) {

    std::string fontPath = "resources/Rubik-Regular.ttf";
    std::string MenuTitlePath = "resources/MenuTitle-Font.ttf";

    if (!Textfont.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font from path: " << fontPath << std::endl;
    }

    if (!Menufont.loadFromFile(MenuTitlePath)) {
        std::cerr << "Failed to load font from path: " << MenuTitlePath << std::endl;
    }

    loadBackground();

    sf::Vector2u defaultWindowSize(1920, 1080);
    initializeButton(playButton, Textfont, "Start Game", defaultWindowSize, 70);
    initializeButton(systemButton, Textfont, "iNateHiggers", defaultWindowSize, 170);
    initializeButton(carButton, Textfont, "Choose your Car", defaultWindowSize, 120);
    initializeButton(exitButton, Textfont, "Exit", defaultWindowSize, 220);

    changeBgButton.setFont(Textfont);
    changeBgButton.setString("Change Background");
    changeBgButton.setCharacterSize(30);
    changeBgButton.setFillColor(sf::Color::White);
    sf::FloatRect buttonBounds = changeBgButton.getLocalBounds();
    changeBgButton.setOrigin(buttonBounds.width / 2.0f, buttonBounds.height / 2.0f);
    changeBgButton.setPosition(150, defaultWindowSize.y - 30);

    title.setFont(Menufont);
    title.setString("INTELLIDRIVE");
    title.setCharacterSize(200);
    title.setFillColor(sf::Color{ 255, 255, 255, 255 });
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f);
    title.setPosition(defaultWindowSize.x / 2.0f, (defaultWindowSize.y / 4.0f + 100.f));

    copyrightText.setFont(Textfont);
    copyrightText.setString("\u00A9 2024 Devrim Yildiz & Tobias Huber. IntelliDrive is not really a TradeMark of Voric Productions LLC");
    copyrightText.setCharacterSize(20);
    copyrightText.setFillColor(sf::Color::White);
    sf::FloatRect copyrightBounds = copyrightText.getLocalBounds();
    copyrightText.setOrigin(copyrightBounds.width / 2.0f, copyrightBounds.height / 2.0f);
    copyrightText.setPosition(defaultWindowSize.x / 2.0f, defaultWindowSize.y - 50);

    versionText.setFont(Textfont);
    versionText.setString("Beta v1.5.4");
    versionText.setCharacterSize(20);
    versionText.setFillColor(sf::Color::White);
    versionText.setPosition(defaultWindowSize.x - 150, defaultWindowSize.y - 100);
}

void MenuState::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);

            if (playButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                game.changeState(std::make_shared<GameState>(game));
            } else if (carButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                game.changeState(std::make_shared<CarChoosingState>());
            } else if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                game.window.close();
            } else if (changeBgButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                changeBackground();
            }
        }
    }
}


void MenuState::update(Game& game) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);

    updateButtonHover(playButton, mousePos);
    updateButtonHover(systemButton, mousePos);
    updateButtonHover(carButton, mousePos);
    updateButtonHover(exitButton, mousePos);
    updateButtonHover(changeBgButton, mousePos);
}

void MenuState::updateButtonHover(sf::Text& button, const sf::Vector2i& mousePos) {
    if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        button.setFillColor(sf::Color(255, 215, 0));
        button.setScale(1.1f, 1.1f);
    } else {
        button.setFillColor(sf::Color::White);
        button.setScale(1.0f, 1.0f);
    }
}

void MenuState::render(Game& game) {
    game.window.clear();
    game.window.draw(backgroundSprite);
    game.window.draw(title);
    game.window.draw(playButton);
    game.window.draw(systemButton);
    game.window.draw(carButton);
    game.window.draw(exitButton);
    game.window.draw(changeBgButton);
    game.window.draw(copyrightText);
    game.window.draw(versionText);
}

void MenuState::initializeButton(sf::Text& button, const sf::Font& font, const std::string& text, const sf::Vector2u& windowSize, float offsetY) {
    button.setFont(font);
    button.setString(text);
    button.setCharacterSize(40);
    button.setFillColor(sf::Color::White);
    sf::FloatRect buttonBounds = button.getLocalBounds();
    button.setOrigin(buttonBounds.width / 2.0f, buttonBounds.height / 2.0f);
    button.setPosition(static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 2.0f + offsetY);
}

void MenuState::loadBackground() {
    std::string backgroundImagePath = "resources/background" + std::to_string(backgroundIndex) + ".png";
    if (!backgroundTexture.loadFromFile(backgroundImagePath)) {
        std::cerr << "Failed to load background image from path: " << backgroundImagePath << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void MenuState::changeBackground() {
    backgroundIndex = (backgroundIndex % 4) + 1;
    
    loadBackground();
}
