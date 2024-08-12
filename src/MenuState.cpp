//
// Created by Voric on 11/08/2024.
//

#include "../include/MenuState.h"
#include "../include/GameState.h"
#include "../include/ResourceManager.h"

void MenuState::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                game.changeState(std::make_shared<GameState>());
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);

            if (playButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                game.changeState(std::make_shared<GameState>());
            } else if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                game.window.close();
            }
        }
    }
}

void MenuState::update(Game& game) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);

    updateButtonHover(playButton, mousePos);
    updateButtonHover(systemButton, mousePos);
    updateButtonHover(infoButton, mousePos);
    updateButtonHover(exitButton, mousePos);
}

void MenuState::updateButtonHover(sf::Text& button, const sf::Vector2i& mousePos) {
    if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        button.setFillColor(sf::Color(255, 215, 0)); // Yellow color for hover
        button.setScale(1.1f, 1.1f); // Scale up on hover
    } else {
        button.setFillColor(sf::Color::White); // Default color
        button.setScale(1.0f, 1.0f); // Default scale
    }
}

void MenuState::render(Game& game) {

    std::string fontPath = "resources/Rubik-Regular.ttf";
    std::string MenuTitlePath = "resources/MenuTitle-Font.ttf";
    std::string backgroundImagePath = "resources/background4.png";

    if (!Textfont.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font from path: " << fontPath << std::endl;
        return;
    }

    if (!Menufont.loadFromFile(MenuTitlePath)) {
        std::cerr << "Failed to load font from path: " << MenuTitlePath << std::endl;
        return;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(backgroundImagePath)) {
        std::cerr << "Failed to load background image from path: " << backgroundImagePath << std::endl;
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // Initialize buttons
    initializeButton(playButton, Textfont, "Start Game", game.window.getSize(), 70);
    initializeButton(systemButton, Textfont, "System", game.window.getSize(), 120);
    initializeButton(infoButton, Textfont, "Information", game.window.getSize(), 170);
    initializeButton(exitButton, Textfont, "Exit", game.window.getSize(), 220);

    // Set up title
    title.setFont(Menufont);
    title.setString("INTELLIDRIVE");
    title.setCharacterSize(200);
    title.setFillColor(sf::Color{ 255, 255, 255, 255 });
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f);
    title.setPosition(static_cast<float>(game.window.getSize().x) / 2.0f, (static_cast<float>(game.window.getSize().y) / 4.0f + 100.f));

    // Set up copyright and version texts
    copyrightText.setFont(Textfont);
    copyrightText.setString("© 2024 Devrim Yildiz & Tobias Huber. IntelliDrive is not really a TradeMark of Voric Productions LLC");
    copyrightText.setCharacterSize(20);
    copyrightText.setFillColor(sf::Color::White);
    sf::FloatRect copyrightBounds = copyrightText.getLocalBounds();
    copyrightText.setOrigin(copyrightBounds.width / 2.0f, copyrightBounds.height / 2.0f);
    copyrightText.setPosition(static_cast<float>(game.window.getSize().x) / 2.0f, static_cast<float>(game.window.getSize().y) - 50); // Moved up a bit

    versionText.setFont(Textfont);
    versionText.setString("Beta v1.0.1");
    versionText.setCharacterSize(20);
    versionText.setFillColor(sf::Color::White);
    versionText.setPosition(static_cast<float>(game.window.getSize().x) - 100, static_cast<float>(game.window.getSize().y) - 100); // Moved up a bit

    // Clear window and draw all elements
    game.window.clear();
    game.window.draw(backgroundSprite);
    game.window.draw(title);

    // Draw buttons
    game.window.draw(playButton);
    game.window.draw(systemButton);
    game.window.draw(infoButton);
    game.window.draw(exitButton);

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

