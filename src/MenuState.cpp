//
// Created by Voric on 11/08/2024.
//

#include "../include/MenuState.h"
#include "../include/GameState.h"
#include "../include/ResourceManager.h"

MenuState::MenuState()
    : backgroundIndex(1) { // Initialize backgroundIndex

    std::string fontPath = "resources/Rubik-Regular.ttf";
    std::string MenuTitlePath = "resources/MenuTitle-Font.ttf";

    if (!Textfont.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font from path: " << fontPath << std::endl;
    }

    if (!Menufont.loadFromFile(MenuTitlePath)) {
        std::cerr << "Failed to load font from path: " << MenuTitlePath << std::endl;
    }

    loadBackground(); // Load the initial background

    sf::Vector2u defaultWindowSize(1920, 1080);
    initializeButton(playButton, Textfont, "Start Game", defaultWindowSize, 70);
    initializeButton(systemButton, Textfont, "System", defaultWindowSize, 120);
    initializeButton(infoButton, Textfont, "Information", defaultWindowSize, 170);
    initializeButton(exitButton, Textfont, "Exit", defaultWindowSize, 220);

    // Initialize the new button
    changeBgButton.setFont(Textfont);
    changeBgButton.setString("Change Background");
    changeBgButton.setCharacterSize(30);
    changeBgButton.setFillColor(sf::Color::White);
    sf::FloatRect buttonBounds = changeBgButton.getLocalBounds();
    changeBgButton.setOrigin(buttonBounds.width / 2.0f, buttonBounds.height / 2.0f);
    changeBgButton.setPosition(150, defaultWindowSize.y - 30); // Position it in the bottom-left corner

    title.setFont(Menufont);
    title.setString("INTELLIDRIVE");
    title.setCharacterSize(200);
    title.setFillColor(sf::Color{ 255, 255, 255, 255 });
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f);
    title.setPosition(defaultWindowSize.x / 2.0f, (defaultWindowSize.y / 4.0f + 100.f));

    copyrightText.setFont(Textfont);
    copyrightText.setString("© 2024 Devrim Yildiz & Tobias Huber. IntelliDrive is not really a TradeMark of Voric Productions LLC");
    copyrightText.setCharacterSize(20);
    copyrightText.setFillColor(sf::Color::White);
    sf::FloatRect copyrightBounds = copyrightText.getLocalBounds();
    copyrightText.setOrigin(copyrightBounds.width / 2.0f, copyrightBounds.height / 2.0f);
    copyrightText.setPosition(defaultWindowSize.x / 2.0f, defaultWindowSize.y - 50); // Moved up a bit

    versionText.setFont(Textfont);
    versionText.setString("Beta v1.1.1");
    versionText.setCharacterSize(20);
    versionText.setFillColor(sf::Color::White);
    versionText.setPosition(defaultWindowSize.x - 150, defaultWindowSize.y - 100); // Moved up a bit
}

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
            } else if (changeBgButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                // Change background when the changeBgButton is clicked
                changeBackground();
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
    updateButtonHover(changeBgButton, mousePos); // Update hover state for the new button
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
    game.window.clear();
    game.window.draw(backgroundSprite);
    game.window.draw(title);

    // Draw buttons
    game.window.draw(playButton);
    game.window.draw(systemButton);
    game.window.draw(infoButton);
    game.window.draw(exitButton);
    game.window.draw(changeBgButton); // Draw the new button

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
    backgroundIndex = (backgroundIndex % 4) + 1; // Cycle through backgrounds 1 to 4
    loadBackground();
}
