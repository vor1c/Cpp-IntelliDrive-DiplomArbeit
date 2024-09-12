//
// Created by Voric and tobisdev on 11/08/2024.
//

#include "../include/Car.h"

// https://en.sfml-dev.org/forums/index.php?topic=7068.0

void Car::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        acceleration = acceleration_constant;
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        acceleration = -acceleration_constant;
    }else{
        acceleration = 0.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        angular_acceleration = -angular_acceleration_constant;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        angular_acceleration = angular_acceleration_constant;
    } else {
        angular_acceleration = 0.0f;
    }
}

void Car::update(float dt) {
    float radian_angle = rotation_angle * (3.14159265358979323846f / 180.0f);
    sf::Vector2f forward_direction(std::sin(radian_angle), -std::cos(radian_angle));
    sf::Vector2f velocity = (carSprite.getPosition() - previous_position) / dt; // Velocity = distance / time
    velocity *= friction; // Apply friction to velocity
    sf::Vector2f new_velocity = velocity + (forward_direction * acceleration * dt); // Add forward acceleration

    sf::Vector2f newPosition = carSprite.getPosition() + new_velocity * dt;
    float speed = std::sqrt(new_velocity.x * new_velocity.x + new_velocity.y * new_velocity.y);

    rotation_angle += angular_acceleration * speed * dt;

    if (rotation_angle >= 360.0f) {
        rotation_angle -= 360.0f;
    } else if (rotation_angle < 0.0f) {
        rotation_angle += 360.0f;
    }

    carSprite.setRotation(rotation_angle);
    carSprite.setPosition(newPosition);

    previous_position = carSprite.getPosition();
}

void Car::render(sf::RenderWindow& window) {
    window.draw(carSprite);
}

sf::FloatRect Car::getBounds() const {
    return carSprite.getGlobalBounds();
}

void Car::applyData(carData &data) {
    carSprite = {};
    carSprite.setTexture(data.carTexture);
}