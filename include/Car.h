//
// Created by Voric on 11/08/2024.
//

#ifndef CAR_H
#define CAR_H

class Car {
public:
    Car();

    void handleInput();
    void update();
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape carShape;
    float speed;
    sf::Vector2f direction;
};

#endif //CAR_H
