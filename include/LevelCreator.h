//
// Created by Devrim on 30.09.2024.
//

#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include "State.h"
#include "Game.h"
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

class LevelCreator : public State {
public:
    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    void saveWallToCSV(const std::string& filename);
    void clearDrawing(Game &game);
    LevelCreator(Game &game);

    void createSaveButton(Game& game);

private:
    std::vector<sf::Vector2f> wallPoints;
    sf::RectangleShape currentWallSegment;
    bool isDrawing = false;
    sf::RectangleShape saveButton;
    sf::Text buttonText;
    sf::Font font;

    sf::RenderWindow nameInputWindow;
    std::string inputFileName;
};

#endif // LEVELCREATOR_H
