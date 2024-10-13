//
// Created by Voric on 11/08/2024.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

class ResourceManager {
public:
    static ResourceManager& getInstance();

    void loadFont(const std::string& name, const std::string& filename);
    sf::Font& getFont(const std::string& name);

    bool loadTexture(const std::string &name, const std::string &filename);

    void setTexture(const std::string &name, const std::string &filename);

    sf::Texture& getTexture(const std::string& name);

    void loadTexturesInBulk(const std::string& path, const std::string& prefix, const std::string& postfix);
    const std::vector<sf::Texture>& getBulkTextures();

private:
    ResourceManager() = default;

    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::Texture> textures;

    std::vector<sf::Texture> bulkTextures;
};

#endif // RESOURCEMANAGER_H
