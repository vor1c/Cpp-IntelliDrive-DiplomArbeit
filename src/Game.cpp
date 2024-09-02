//
// Created by Voric on 11/08/2024.
//

#include "../include/Game.h"
#include <iostream>
#include <../include/MenuState.h>
#include <SFML/System/Clock.hpp>
sf::Event event;

Game::Game() : window(sf::VideoMode(1920, 1080), "IntelliDrive", sf::Style::Fullscreen)
{
    car = std::make_shared<Car>();
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

void Game::setSelectedCarTexture(const sf::Texture& texture) {
    selectedCarTexture = texture;
}

const sf::Texture& Game::getSelectedCarTexture() const {
    return selectedCarTexture;
}