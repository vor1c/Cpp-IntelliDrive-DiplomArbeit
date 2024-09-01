//
// Created by Voric on 11/08/2024.
//

#include "../include/DeathState.h"
#include "../include/GameState.h"
#include "../include/MenuState.h"
#include "../include/ResourceManager.h"
//#include "../include/FileSystem.h"

void DeathState::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            game.window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
            game.changeState(std::make_shared<GameState>(game));
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
            game.changeState(std::make_shared<MenuState>());
        }
    }
}

void DeathState::update(Game& game) {}

void DeathState::render(Game& game) {
    std::cout<<"DeathState 1" << std::endl;

    std::string fontPath = "resources/Rubik-Regular.ttf";

    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font from path: " << fontPath << std::endl;
        return;
    }
    deathText.setFont(font);
    deathText.setString("You Crashed!");
    deathText.setCharacterSize(40);
    deathText.setPosition(300, 150);

    playAgainButton.setFont(font);
    playAgainButton.setString("Press R to Play Again");
    playAgainButton.setCharacterSize(20);
    playAgainButton.setPosition(250, 300);

    menuButton.setFont(font);
    menuButton.setString("Press M for Menu");
    menuButton.setCharacterSize(20);
    menuButton.setPosition(250, 350);

    game.window.draw(deathText);
    game.window.draw(playAgainButton);
    game.window.draw(menuButton);
}
