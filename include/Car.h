//
// Created by Voric and tobisdev on 11/08/2024.
//

#include <vector>
#include <cmath>
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#ifndef CAR_H
#define CAR_H

struct carData{
    std::string name;
    sf::Texture carTexture;
    float maxSpeed;
    float handling;
    float acceleration;
    float weight;
    float power;
    float torque;
    std::string driveType;
    sf::Texture logoTexture;
};

class Car {
public:
    Car() = default;

    void handleInput();
    void update(float dt);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

    void applyData(carData &data);

    sf::Sprite &getCarSprite() { return carSprite; }
    void setPreviousPosition(sf::Vector2f const &previousPosition) { previous_position = previousPosition; }

private:
    sf::Sprite carSprite;
    sf::Vector2f direction;

    float rotation_angle = 0.0f;
    float angular_acceleration = 0.0f;
    float angular_acceleration_constant = 0.80f;

    float acceleration = 0.0f;
    float acceleration_constant = 5000000.0f;

    float friction = 0.1f;

    sf::Vector2f previous_position;
};

#endif //CAR_H