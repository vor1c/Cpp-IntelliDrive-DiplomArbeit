//
// Created by Voric and tobisdev on 11/08/2024.
//

#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Car.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "State.h"

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

    void loadCarData(std::string path);
    Car &getCar(){ return car; }

    std::vector<carData> cars;

private:
    sf::Clock clock;
    Car car;
    std::vector<std::shared_ptr<State>> states;
};

#endif //GAME_H
