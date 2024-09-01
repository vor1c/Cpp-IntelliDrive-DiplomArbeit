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

    sf::Font font;
    sf::Text titleText;
    std::vector<sf::Texture> carTextures;
    std::vector<sf::Sprite> carSprites;
    int selectedCarIndex;
    bool updateNeeded; // Flag to indicate if an update is needed
};

#endif // CARCHOOSINGSTATE_H

