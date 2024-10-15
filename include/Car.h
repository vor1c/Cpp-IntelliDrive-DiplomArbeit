//
// Created by Voric and tobisdev on 11/08/2024.
//



#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

struct carData {
    std::string name;
    sf::Texture carTexture;
    int MaxSpeed;
    int Handling;
    int Acceleration;
    float weight;
    float power;
    float torque;
    std::string driveType;
    sf::Texture logoTexture;
};

class Car {
public:
    Car();
    void resetVelocity();

    void resetAngularAcceleration();

    void handleInput();
    void update(float dt);
    void render(sf::RenderWindow& window);
    void applyData(carData &data);
    void resetRotationAngle();
    sf::FloatRect getBounds() const;

    float getRotationAngle() const;
    sf::Vector2f getCurrentPosition() const;
    sf::Sprite& getCarSprite();

    void setPreviousPosition(const sf::Vector2f& position);
    void setCurrentPosition(const sf::Vector2f& position);
    sf::Vector2f velocity;
private:
    sf::Sprite carSprite;

    sf::Vector2f current_position;
    sf::Vector2f previous_position;

    float rotation_angle;
    float angular_velocity;

    float acceleration;
    float angular_acceleration;

    float acceleration_constant;
    float angular_acceleration_constant;
    float max_speed;

    float angular_damping;
    float friction;
    float friction_coefficient;

    float maxSpeedValue;
    float handlingValue;
    float accelerationValue;

    std::string name;
    sf::Texture logoTexture;
    float weight;
    float power;
    float torque;
    std::string driveType;

};

#endif // CAR_H