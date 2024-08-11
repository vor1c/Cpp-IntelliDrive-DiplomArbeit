//
// Created by Voric on 11/08/2024.
//

#include "../include/Car.h"

Car::Car() : speed(200.0f), direction(0.0f, 0.0f) {
    carShape.setSize(sf::Vector2f(16, 16));
    carShape.setFillColor(sf::Color::Red);
    carShape.setPosition(400, 300);
}

void Car::handleInput() {
    direction = sf::Vector2f(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction.y += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction.x += 1.0f;
    }
}

void Car::update() {
    carShape.move(direction * speed * 0.01f);
}

void Car::render(sf::RenderWindow& window) {
    window.draw(carShape);
}

sf::FloatRect Car::getBounds() const {
    return carShape.getGlobalBounds();
}
