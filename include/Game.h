//
// Created by Voric on 11/08/2024.
//

#ifndef GAME_H
#define GAME_H


#include <Car.h>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/RenderWindow.hpp"
#include "State.h"
#include <memory>
#include <SFML/System/Clock.hpp>

class Game {
public:
    Game();
    ~Game();
    void run();
    float dt;
    void pushState(std::shared_ptr<State> state);
    void popState();
    void changeState(std::shared_ptr<State> state);

    std::shared_ptr<State> getCurrentState();

    sf::RenderWindow window;

    // Add these methods:
    void setSelectedCarTexture(const sf::Texture& texture);
    const sf::Texture& getSelectedCarTexture() const;

private:
    sf::Clock clock;
    std::shared_ptr<Car> car;
    std::vector<std::shared_ptr<State>> states;

    // Add this variable:
    sf::Texture selectedCarTexture;  // Texture of the selected car
};

#endif //GAME_H
