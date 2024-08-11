//
// Created by Voric on 11/08/2024.
//

#include "../include/MenuState.h"
#include "../include/GameState.h"
#include "../include/ResourceManager.h"
//#include "../include/FileSystem.h"

void MenuState::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            game.window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            game.changeState(std::make_shared<GameState>());
        }
    }
}

void MenuState::update(Game& game) {}

void MenuState::render(Game& game) {
    std::cout<<"MenuState 1" << std::endl;
    std::string fontPath = "resources/Rubik-Regular.ttf";

    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font from path: " << fontPath << std::endl;
        return;
    }

    title.setFont(font);
    title.setString("IntelliDrive");
    title.setCharacterSize(40);
    title.setPosition(200, 150);

    playButton.setFont(font);
    playButton.setString("Press Enter to Play");
    playButton.setCharacterSize(20);
    playButton.setPosition(250, 300);

    game.window.draw(title);
    game.window.draw(playButton);
}
