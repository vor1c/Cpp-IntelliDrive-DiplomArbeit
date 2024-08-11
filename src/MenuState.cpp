//
// Created by Voric on 11/08/2024.
//

#include "../include/MenuState.h"
#include "../include/GameState.h"
#include "../include/ResourceManager.h"
//#include "../include/FileSystem.h"
int cnt = 0;
void MenuState::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            std::cout << "Key Pressed: " << event.key.code << std::endl;
            if (event.key.code == sf::Keyboard::Enter) {
                std::cout << "Enter Key Pressed, changing state." << std::endl;
                game.changeState(std::make_shared<GameState>());
            }
        }
    }
}


void MenuState::update(Game& game) {}

void MenuState::render(Game& game) {
    if(cnt == 0)
    {
        std::cout<<"MenuState 1" << std::endl;
        cnt++;
    }

    std::string fontPath = "resources/Rubik-Regular.ttf";

    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font from path: " << fontPath << std::endl;
        return;
    }

    title.setFont(font);
    title.setString("IntelliDrive");
    title.setCharacterSize(40);
    // Center the title
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f);
    title.setPosition(game.window.getSize().x / 2.0f, game.window.getSize().y / 2.0f - 50);

    // Set up the play button text
    playButton.setFont(font);
    playButton.setString("Press Enter to Play");
    playButton.setCharacterSize(20);

    // Center the play button text
    sf::FloatRect playButtonBounds = playButton.getLocalBounds();
    playButton.setOrigin(playButtonBounds.width / 2.0f, playButtonBounds.height / 2.0f);
    playButton.setPosition(game.window.getSize().x / 2.0f, game.window.getSize().y / 2.0f + 50);
    game.window.draw(title);
    game.window.draw(playButton);
}
