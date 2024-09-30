//
// Created by Devrim on 30.09.2024.
//

#include "../include/LevelLoader.h"


LevelLoader::LevelLoader(const std::string& filename) {
    loadWallFromCSV(filename);  // Beim Initialisieren wird die CSV geladen
}

void LevelLoader::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.window.close();
        }
    }
}

void LevelLoader::update(Game& game) {
    // Keine speziellen Updates für die geladenen Wände
}

void LevelLoader::render(Game& game) {
    game.window.clear();

    // Zeichne alle Wandsegmente
    for (const auto& wall : walls) {
        game.window.draw(wall);
    }

    game.window.display();
}

void LevelLoader::loadWallFromCSV(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Fehler beim Öffnen der Datei zum Laden" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string xStr, yStr;

        if (std::getline(ss, xStr, ',') && std::getline(ss, yStr, ',')) {
            float x = std::stof(xStr);
            float y = std::stof(yStr);

            // Erstelle ein Wandsegment für jede Koordinate
            sf::RectangleShape wallSegment;
            wallSegment.setPosition(x, y);
            wallSegment.setSize({5.0f, 5.0f});  // Kleine Punkte der Wand
            wallSegment.setFillColor(sf::Color::Red);

            walls.push_back(wallSegment);
        }
    }

    file.close();
}
