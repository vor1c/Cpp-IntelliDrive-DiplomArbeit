//
// Created by Voric and tobisdev on 11/08/2024.
//

#include "../include/Game.h"
#include <iostream>
#include <../include/MenuState.h>
#include <SFML/System/Clock.hpp>
sf::Event event;

Game::Game() : window(sf::VideoMode(1920, 1080), "IntelliDrive", sf::Style::Fullscreen)
{
    car = {};
    // Load all the cars and set the default state
    loadCarData("resources/cars.csv");
    car.applyData(cars[0]);
    pushState(std::make_shared<MenuState>());
}
Game::~Game() {
    std::cout << "Game is exiting..." << std::endl;
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        dt = deltaTime.asSeconds();
        auto currentState = getCurrentState();
        if (currentState) {
            currentState->handleInput(*this);
            currentState->update(*this);
            window.clear();
            currentState->render(*this);
            window.display();
        }
    }
}


void Game::pushState(std::shared_ptr<State> state) {
    states.push_back(state);
}

void Game::popState() {
    states.pop_back();
}

void Game::changeState(std::shared_ptr<State> state) {
    if (!states.empty()) {
        states.pop_back();
    }
    states.push_back(state);
}

std::shared_ptr<State> Game::getCurrentState() {
    if (states.empty()) return nullptr;
    return states.back();
}

void Game::loadCarData(std::string path) {
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cerr << "ERROR: Error opening file!" << "\n";
        return;
    }

    std::string line;
    std::string delimiter = ",";
    int row = 0;

    while (getline(inputFile, line)) {
        if (row != 0) {
            std::stringstream ss(line);
            std::string token;
            int entry = 0;

            carData data;

            std::cout << line << "\n";

            while (getline(ss, token, ',')) {
                if (!token.empty()) {
                    switch(entry){
                        case 0:
                            data.name = token;
                            break;
                        case 1:
                            data.texture.loadFromFile(token);
                            break;
                        case 2:
                            data.maxSpeed = std::stoi(token);
                            break;
                        case 3:
                            data.handling = std::stoi(token);
                            break;
                        case 4:
                            data.acceleration = std::stoi(token);
                            break;
                        case 5:
                            data.weight = std::stoi(token);
                            break;
                        case 6:
                            data.power = std::stoi(token);
                            break;
                        case 7:
                            data.torque = std::stoi(token);
                            break;
                        case 8:
                            data.driveType = token;
                            break;
                    }
                }
                entry++;
            }
            cars.emplace_back(data);
        }
        row++;
    }
    inputFile.close();
}