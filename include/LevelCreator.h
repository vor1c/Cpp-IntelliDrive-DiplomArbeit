//
// Created by Devrim on 30.09.2024.
//

#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include "State.h"
#include "Game.h"
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

class LevelCreator : public State {
public:
    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    void saveWallToCSV(const std::string& filename);  // Speichern der Wanddaten in einer CSV
    void clearDrawing(); // Löschen der gezeichneten Punkte
    LevelCreator(Game &game);

    void createSaveButton(Game& game); // Erstellen des Save-Buttons

private:
    std::vector<sf::Vector2f> wallPoints;  // Punkte der Wand, die mit der Maus gezeichnet werden
    sf::RectangleShape currentWallSegment; // Aktuelles Wandsegment
    bool isDrawing = false;                // Zeichnet der Spieler gerade?
    sf::RectangleShape saveButton;         // Save-Button
    sf::Text buttonText;                   // Text für den Save-Button
    sf::Font font;                         // Schriftart für den Button

    // Neues Fenster für die Dateinamen-Eingabe
    sf::RenderWindow nameInputWindow;
    std::string inputFileName;             // Eingabewert für den Dateinamen
};

#endif // LEVELCREATOR_H
