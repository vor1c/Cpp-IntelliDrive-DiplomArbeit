//
// Created by Devrim on 30.09.2024.
//

#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "State.h"
#include "Game.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>

class LevelLoader : public State {
public:
    LevelLoader(const std::string& filename);  // Konstruktor, der die CSV lädt
    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    std::vector<sf::RectangleShape> walls;  // Wandsegmente aus der CSV

    void loadWallFromCSV(const std::string& filename);  // Funktion zum Laden der CSV-Daten
};

#endif // LEVELLOADER_H
