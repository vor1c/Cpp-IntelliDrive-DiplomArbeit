//
// Created by Devrim on 30.09.2024.
//

#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include "State.h"
#include "Game.h"
#include "ResourceManager.h"
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
    sf::RectangleShape saveButton;
    sf::Text buttonText;
    sf::Font font;

    std::vector<sf::Texture> tiles;

    std::vector<sf::Sprite> placedTiles;
    std::vector<int> textureIDs;

    int selectedTile = 0;

    bool mouseDown = false;

    sf::RenderWindow nameInputWindow;
    std::string inputFileName;
};

#endif // LEVELCREATOR_H
