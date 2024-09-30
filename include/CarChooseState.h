//
// Created by Voric and tobisdev on 31/08/2024.
//

#ifndef CARCHOOSINGSTATE_H
#define CARCHOOSINGSTATE_H

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../include/MenuState.h"
#include "../include/State.h"
#include "../include/Game.h"
#include "../include/GameState.h"


class Game;
class MenuState;

class CarChoosingState : public State {
public:
    CarChoosingState();
    void handleInput(Game& game);
    void update(Game& game);
    void renderLogos(Game& game);
    void loadBackground();
    void render(Game& game);


private:
    void renderBottomLine(Game& game);

    sf::Font font;
    sf::Font titlefont;
    sf::Text titleText;
    sf::Text carStatsText;
    sf::Text statBarsLabel;
    sf::Text driveTypeText;
    sf::Sprite carSprite;
    sf::Vector2u defaultWindowSize;
    sf::RectangleShape dividerline;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    float rotationAngle;
    float legendheight;
    int selectedCarIndex;
};

#endif // CARCHOOSINGSTATE_H
