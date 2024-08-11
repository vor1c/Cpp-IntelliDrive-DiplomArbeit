//
// Created by Voric on 11/08/2024.
//

#include "../include/Car.h"

// https://en.sfml-dev.org/forums/index.php?topic=7068.0
Car::Car() : speed(100.0f), direction(0.0f, 0.0f) {
    carShape.setSize(sf::Vector2f(16, 16));
    carShape.setFillColor(sf::Color::Red);
    carShape.setPosition(400, 300);
}

void Car::handleInput() {
    direction = sf::Vector2f(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        direction.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        direction.y += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        direction.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        direction.x += 1.0f;
    }

    // Normalize direction to prevent faster diagonal movement
    if (direction.x != 0.0f || direction.y != 0.0f) {
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;
    }
}

void Car::update(float dt) {
    // Move car based on direction and speed
    carShape.move(direction * speed * dt);
}

void Car::render(sf::RenderWindow& window) {
    window.draw(carShape);
}

sf::FloatRect Car::getBounds() const {
    return carShape.getGlobalBounds();
}
