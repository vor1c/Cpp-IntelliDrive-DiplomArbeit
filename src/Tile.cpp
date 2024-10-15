//
// Created by Tobias on 15.10.2024.
//

#include "../include/Tile.h"

Tile::Tile(std::string path){
    texturePath = path;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Error loading texture from " << path << std::endl;
    }
}

void Tile::addCollisionPoint(const sf::Vector2f &point) {
    collisionPolygon.emplace_back(point);
}

void Tile::setTexturePath(const std::string &path) {
    texturePath = path;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Error loading texture from " << path << std::endl;
    }
}