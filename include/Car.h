//
// Created by Voric on 11/08/2024.
//

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
    void setTexture(const sf::Texture& texture);  // Add this method

private:
    sf::Sprite carSprite;  // Change to sprite
    float speed;
    sf::Vector2f direction;
};

#endif //CAR_H
