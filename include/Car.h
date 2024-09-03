//
// Created by Voric and tobisdev on 11/08/2024.
//

#include <iostream>
#include "SFML/Window/Keyboard.hpp"
#include <vector>
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <cmath>
#include "SFML/Graphics/Sprite.hpp"
#ifndef CAR_H
#define CAR_H

class Car {
public:
    Car();

    void handleInput();
    void update(float dt);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    void setTexture(const sf::Texture& texture);

private:
    sf::Sprite carSprite;  // Change to sprite
    sf::Vector2f direction;

    float rotation_angle = 0.0f;
    float angular_acceleration = 0.0f;
    float angular_acceleration_constant = 1000.0f;

    float acceleration = 0.0f;
    float acceleration_constant = 11.0f;

    float friction = 0.99f;

    sf::Vector2f previous_position;
};

#endif //CAR_H