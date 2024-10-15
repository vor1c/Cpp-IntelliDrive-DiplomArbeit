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
    LevelCreator(Game& game);

    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    void saveWallToCSV(const std::string& filename);
    void clearDrawing(Game& game);

private:
    void addPointToTile(Game& game);
    void drawPolygon(Game &game, const std::vector<sf::Vector2f>& points, sf::Color Outline, sf::Color Fill);

    void initializeResources(Game& game);
    void createButtons(Game& game);

    void handleExplanationInput(const sf::Event& event);
    void handleTextInput(const sf::Event& event, Game& game);
    void handleMouseInput(const sf::Event& event, Game& game);
    void handleKeyboardInput(const sf::Event& event, Game& game);

    void addTileAtMouse(Game& game);
    void removeTileAtMouse(Game& game);

    void updatePreviewTile(Game& game);

    void drawPlacedTiles(Game& game);
    void drawButtons(Game& game);
    void drawExplanationScreen(Game& game);
    void drawInputBox(Game& game);

    sf::RectangleShape saveButton;
    sf::Text saveButtonText;

    sf::RectangleShape exitButton;
    sf::Text exitButtonText;

    sf::Font font;
    std::vector<Tile> tiles; // These are the tiles loaded by the resource manager they are used as blueprints

    sf::Vector2i boundaries; // How many tiles can be placed on the x -and y-axis

    bool tileEditMode = false; // edit the Tile

    std::vector<std::vector<int>> placedTileIDs;
    std::vector<std::vector<sf::Sprite>> placedTileSprites;

    sf::Sprite backgroundSprite;

    int selectedTile = 0;
    bool mouseDown = false;

    sf::Sprite previewTile;
    bool showExplanation = true;

    bool inputActive = false;
    bool rightMouseDown = false;
    std::string inputFileName;
};

#endif // LEVELCREATOR_H
