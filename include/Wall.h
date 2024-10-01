//
// Created by Devrim on 30.09.2024.
//

#ifndef WALL_H
#define WALL_H
#pragma once
#include <SFML/Graphics.hpp>

class Wall : public sf::Drawable {
public:
    sf::RectangleShape shape;

    Wall(const sf::RectangleShape& rectangle) : shape(rectangle) {}

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(shape, states);
    }
};


#endif //WALL_H
