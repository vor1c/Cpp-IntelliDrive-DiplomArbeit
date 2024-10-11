//
// Created by Voric and tobisdev on 11/08/2024.
//

#include "../include/Car.h"
#include <iostream>
#include <cmath>

constexpr float PI = 3.14159265f;
// https://en.sfml-dev.org/forums/index.php?topic=7068.0

Car::Car()
    : current_position(0.0f, 0.0f),
      previous_position(0.0f, 0.0f),
      velocity(0.0f, 0.0f),
      rotation_angle(0.0f),
      angular_velocity(0.0f),
      acceleration(0.0f),
      angular_acceleration(100.0f),
      angular_damping(0.1f), // Similar to friction_coefficient but for rotation
      friction(0.01f),
      friction_coefficient(0.9f), // Adjust between 0 (no friction) and 1 (full stop instantly)
      acceleration_constant(1000.0f),  // Units: pixels per second squared
      angular_acceleration_constant(300.0f) // Units: degrees per second squared
{

}

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
    float radian_angle = rotation_angle * (PI / 180.0f);

    sf::Vector2f forward_direction(sinf(radian_angle), -cosf(radian_angle));

    velocity += forward_direction * acceleration * dt;

    velocity -= velocity * friction_coefficient * dt;

    current_position += velocity * dt;

    angular_velocity += angular_acceleration * dt;

    angular_velocity -= angular_velocity * angular_damping * dt;

    rotation_angle += angular_velocity * dt;

    if (rotation_angle >= 360.0f) {
        rotation_angle -= 360.0f;
    } else if (rotation_angle < 0.0f) {
        rotation_angle += 360.0f;
    }

    carSprite.setPosition(current_position);
    carSprite.setRotation(rotation_angle);

    previous_position = current_position;
}

void Car::resetRotationAngle() {
    rotation_angle = 0.0f;
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