//
// Created by Voric and tobisdev on 11/08/2024.
//

#include "../include/Car.h"
#include <iostream>
#include <cmath>

constexpr float MAX_SPEED = 900.0f; // Units: pixels per second
constexpr float MAX_ACCELERATION = 1000.0f; // Units: pixels per second squared
constexpr float MAX_STEERING_ANGLE = 30.0f; // Degrees

Car::Car(b2World& world)
    : m_world(world),
      body(nullptr),
      current_position(0.0f, 0.0f),
      previous_position(0.0f, 0.0f),
      maxSpeedValue(5.0f),
      handlingValue(5.0f),
      accelerationValue(5.0f),
      desiredSpeed(0.0f),
      desiredSteeringAngle(0.0f)
{

}

Car::~Car() {
    if (body) {
        m_world.DestroyBody(body);
        body = nullptr;
    }
}

void Car::handleInput() {
    desiredSpeed = 0.0f;
    desiredSteeringAngle = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        desiredSpeed = accelerationValue * (MAX_SPEED / 10.0f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        desiredSpeed = -accelerationValue * (MAX_SPEED / 10.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        desiredSteeringAngle = handlingValue * (MAX_STEERING_ANGLE / 10.0f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        desiredSteeringAngle = -handlingValue * (MAX_STEERING_ANGLE / 10.0f);
    }
}

void Car::resetVelocity() {
    body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
}

void Car::resetAngularAcceleration() {
    body->SetAngularVelocity(0.0f);
}

void Car::update(float dt) {
    // Get the current forward direction
    b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0.0f, -1.0f));

    // Apply acceleration
    float acceleration = desiredSpeed - b2Dot(body->GetLinearVelocity(), currentForwardNormal);
    acceleration = std::clamp(acceleration, -MAX_ACCELERATION * dt, MAX_ACCELERATION * dt);
    b2Vec2 force = acceleration * currentForwardNormal;
    body->ApplyForceToCenter(force, true);

    // Apply steering
    float currentAngle = body->GetAngle();
    float angleDifference = (desiredSteeringAngle * DEGTORAD) - currentAngle;
    angleDifference = std::clamp(angleDifference, -handlingValue * dt, handlingValue * dt);
    body->SetAngularVelocity(angleDifference / dt);

    // Update sprite position and rotation
    current_position.x = body->GetPosition().x;
    current_position.y = body->GetPosition().y;
    carSprite.setPosition(current_position);
    carSprite.setRotation(body->GetAngle() * RADTODEG);

    previous_position = current_position;
}

void Car::render(sf::RenderWindow& window) {
    window.draw(carSprite);
}

sf::FloatRect Car::getBounds() const {
    return carSprite.getGlobalBounds();
}

void Car::applyData(carData &data) {
    carSprite.setTexture(data.carTexture);

    maxSpeedValue = static_cast<float>(data.MaxSpeed);
    handlingValue = static_cast<float>(data.Handling);
    accelerationValue = static_cast<float>(data.Acceleration);

    // Ensure the texture has valid dimensions
    sf::FloatRect spriteBounds = carSprite.getLocalBounds();
    if (spriteBounds.width == 0 || spriteBounds.height == 0) {
        std::cerr << "Error: Car sprite has zero dimensions." << std::endl;
        return;
    }

    // Create Box2D body
    if (body != nullptr) {
        m_world.DestroyBody(body);
        body = nullptr;
    }

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(current_position.x / SCALE, current_position.y / SCALE);
    bodyDef.angle = 0.0f;
    body = m_world.CreateBody(&bodyDef);

    // Define the shape of the car (rectangle)
    b2PolygonShape carShape;
    carShape.SetAsBox(
        (spriteBounds.width / 2.0f) / SCALE,
        (spriteBounds.height / 2.0f) / SCALE
    );

    // Define the fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &carShape;
    fixtureDef.density = data.weight;
    fixtureDef.friction = 0.3f; // Adjust based on car properties

    body->CreateFixture(&fixtureDef);
}

float Car::getRotationAngle() const {
    return body->GetAngle() * RADTODEG;
}

sf::Vector2f Car::getCurrentPosition() const {
    return current_position;
}

void Car::setPreviousPosition(const sf::Vector2f& position) {
    previous_position = position;
}

void Car::setCurrentPosition(const sf::Vector2f& position) {
    current_position = position;
    body->SetTransform(b2Vec2(position.x, position.y), body->GetAngle());
}

sf::Sprite& Car::getCarSprite() {
    return carSprite;
}

void Car::resetRotationAngle() {
    body->SetTransform(body->GetPosition(), 0.0f);
}
