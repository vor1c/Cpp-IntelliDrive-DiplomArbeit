//
// Created by Voric on 31/08/2024.
//

#ifndef CARCHOOSINGSTATE_H
#define CARCHOOSINGSTATE_H

#include "State.h"
#include "SFML/Graphics.hpp"
#include <vector>

class CarChoosingState : public State {
public:
    CarChoosingState();
    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    void loadCars();
    void selectCar(int index);

    std::vector<sf::Sprite> carSprites;
    std::vector<sf::Texture> carTextures;  // We need to keep the textures in memory.
    int selectedCarIndex;
    sf::Font font;
    sf::Text titleText;
};

#endif // CARCHOOSINGSTATE_H
