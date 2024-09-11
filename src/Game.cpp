//
// Created by Voric and tobisdev on 11/08/2024.
//

#include "../include/Game.h"
#include <iostream>
#include <numeric>
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

    // Load font for displaying FPS
    if (!font.loadFromFile("resources/Rubik-Regular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    // Setup text objects
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(100.f, 100.f);

    avgText.setFont(font);
    avgText.setCharacterSize(24);
    avgText.setFillColor(sf::Color::White);
    avgText.setPosition(100.f, 140.f);

    lowsText.setFont(font);
    lowsText.setCharacterSize(24);
    lowsText.setFillColor(sf::Color::White);
    lowsText.setPosition(100.f, 170.f);
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
            calculateAndDisplayFPS();
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
                            data.carTexture.loadFromFile(token);
                            break;
                        case 2:
                            data.maxSpeed = std::stof(token);
                            break;
                        case 3:
                            data.handling = std::stof(token);
                            break;
                        case 4:
                            data.acceleration = std::stof(token);
                            break;
                        case 5:
                            data.weight = std::stof(token);
                            break;
                        case 6:
                            data.power = std::stof(token);
                            break;
                        case 7:
                            data.torque = std::stof(token);
                            break;
                        case 8:
                            data.driveType = token;
                            break;
                        case 9:
                            data.logoTexture.loadFromFile(token);
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

void Game::calculateAndDisplayFPS() {
    // Calculate average FPS
    float sumFrameTimes = std::accumulate(frameTimes.begin(), frameTimes.end(), 0.0f);
    float avgFrameTime = sumFrameTimes / frameTimes.size();
    float avgFPS = 1.0f / avgFrameTime;

    // Calculate 1% lows (the average of the slowest 1% of frames)
    std::vector<float> sortedFrameTimes(frameTimes.begin(), frameTimes.end());
    std::sort(sortedFrameTimes.begin(), sortedFrameTimes.end());
    size_t onePercentIndex = static_cast<size_t>(sortedFrameTimes.size() * 0.01f);
    float onePercentLowTime = std::accumulate(sortedFrameTimes.begin(), sortedFrameTimes.begin() + onePercentIndex, 0.0f) / onePercentIndex;
    float onePercentLowsFPS = 1.0f / onePercentLowTime;

    // Update the FPS text
    fpsText.setString("FPS: " + std::to_string(static_cast<float>(1.0f / dt)));
    avgText.setString("Avg FPS: " + std::to_string(static_cast<float>(avgFPS)));
    lowsText.setString("1% Lows: " + std::to_string(static_cast<float>(onePercentLowsFPS)));
    window.draw(fpsText);
    window.draw(avgText);
    window.draw(lowsText);

}