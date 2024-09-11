//
// Created by Voric and tobisdev on 11/08/2024.
//

#ifndef GAME_H
#define GAME_H

#include <deque>
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
    void calculateAndDisplayFPS();
    std::shared_ptr<State> getCurrentState();

    sf::RenderWindow window;

    void loadCarData(std::string path);
    Car &getCar(){ return car; }

    std::vector<carData> cars;

private:
    sf::Clock clock;
    Car car;
    std::vector<std::shared_ptr<State>> states;
    std::deque<float> frameTimes;  // Store frame times
    sf::Font font;
    sf::Text fpsText, lowsText, avgText;
    const int maxFrameSamples = 300;  // Store data for about 5 seconds at 60 FPS
};

#endif //GAME_H
