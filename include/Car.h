//
// Created by Voric and tobisdev on 11/08/2024.
//

#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "SFML/Window/Keyboard.hpp"

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
    Car(b2World& world, const sf::Vector2f& position);
    ~Car();
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

private:
    sf::Sprite carSprite;
    sf::Vector2f current_position;
    sf::Vector2f previous_position;

    // Box2D body
    b2Body* body;

    // Car properties
    float maxSpeedValue;
    float handlingValue;
    float accelerationValue;

    // Input states
    float desiredSpeed;
    float desiredSteeringAngle;

    // Constants
    static constexpr float DEGTORAD = 0.0174532925199432957f;
    static constexpr float RADTODEG = 57.295779513082320876f;
};

#endif // CAR_H
