//
// Created by Voric on 11/08/2024.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class ResourceManager {
public:
    static ResourceManager& getInstance();

    void loadFont(const std::string& name, const std::string& filename);
    sf::Font& getFont(const std::string& name);

private:
    ResourceManager() {}
    std::map<std::string, sf::Font> fonts;
};

#endif //RESOURCEMANAGER_H
