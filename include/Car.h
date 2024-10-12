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
    Car();

    void handleInput();
    void update(float dt);

    void resetRotationAngle();

    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

    void applyData(carData &data);

    sf::Sprite &getCarSprite() { return carSprite; }
    void setPreviousPosition(const sf::Vector2f& previousPosition) { previous_position = previousPosition; };
    void setCurrentPosition(const sf::Vector2f& currentPosition) { current_position = currentPosition; };
    float getRotationAngle() const { return rotation_angle; }
    sf::Vector2f getCurrentPosition() const { return current_position; }

private:
    sf::Sprite carSprite;
    sf::Vector2f direction;
    sf::Vector2f velocity;
    sf::Vector2f current_position;
    sf::Vector2f previous_position;

    float angular_velocity;
    float rotation_angle;
    float acceleration;
    float angular_acceleration;
    float friction;
    float acceleration_constant;
    float angular_acceleration_constant;
    float friction_coefficient;
    float angular_damping;



};

#endif //CAR_H