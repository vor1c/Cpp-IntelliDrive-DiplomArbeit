//
// Created by Voric on 11/08/2024.
//

#include "../include/Car.h"

// https://en.sfml-dev.org/forums/index.php?topic=7068.0

Car::Car(){
    carSprite.setPosition(200, 200);
    previous_position = carSprite.getPosition();
};

void Car::setTexture(const sf::Texture& texture) {
    carSprite.setTexture(texture);
    carSprite.setOrigin(carSprite.getLocalBounds().width / 2, carSprite.getLocalBounds().height / 2);

}

void Car::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        acceleration = {0, acceleration_constant};
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        acceleration = {0, -acceleration_constant};
    }else{
        acceleration = {0,0};
    }
}

void Car::update(float dt) {
    std::cout << "Position: [ " << carSprite.getPosition().x << " / " << carSprite.getPosition().y <<  " ]\n";

    sf::Vector2f newPosition = 2.0f * carSprite.getPosition() - previous_position + (acceleration * dt);

    sf::Vector2f velocity = newPosition - carSprite.getPosition();

    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    if (speed > max_speed) {
        velocity *= (max_speed / speed);

        newPosition = carSprite.getPosition() + velocity;
    }

    previous_position = carSprite.getPosition();
    carSprite.setPosition(newPosition);
}

void Car::render(sf::RenderWindow& window) {
    window.draw(carSprite);
}

sf::FloatRect Car::getBounds() const {
    return carSprite.getGlobalBounds();
}