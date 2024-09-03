//
// Created by Voric on 31/08/2024.
//

#ifndef CARCHOOSINGSTATE_H
#define CARCHOOSINGSTATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <../include/State.h>

class Game;
class MenuState;

class CarChoosingState : public State {
public:
    CarChoosingState();
    void handleInput(Game& game);
    void update(Game& game);
    void render(Game& game);

private:
    void loadCars();
    void selectCar(int index);
    void renderStatsBars(Game& game);

    sf::Font font;
    sf::Font titlefont;
    sf::Text titleText;
    sf::Text carStatsText;
    sf::Text driveTypeText;
    sf::Vector2u defaultWindowSize;
    sf::RectangleShape dividerline;
    std::vector<sf::Texture> carTextures;
    std::vector<sf::Sprite> carSprites;
    std::vector<std::string> carNames;
    float rotationAngle;
    std::vector<int> maxSpeeds;
    std::vector<int> handlings;
    std::vector<int> accelerations;
    std::vector<int> weights;
    std::vector<int> maxPowers;
    std::vector<float> torques;
    std::vector<std::string> driveTypes;
    int selectedCarIndex;
};

#endif // CARCHOOSINGSTATE_H
