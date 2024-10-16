 //
// Created by Voric and tobisdev on 11/08/2024.
//

#include "../include/GameState.h"
#include "../include/PauseState.h"
#include "../include/DeathState.h"
#include "../include/Car.h"
#include "../include/Game.h"

#define M_PI 3.141592653589793238462643383279502884197169399375105820974944
bool getLineIntersection(sf::Vector2f p0, sf::Vector2f p1,
                         sf::Vector2f p2, sf::Vector2f p3,
                         sf::Vector2f& intersectionPoint) {
    sf::Vector2f s1 = p1 - p0;
    sf::Vector2f s2 = p3 - p2;

    float s, t;
    float denominator = (-s2.x * s1.y + s1.x * s2.y);

    if (fabs(denominator) < 1e-6)
        return false;
    //wenn das ned geht tot
    s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / denominator;
    t = ( s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / denominator;

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) { // https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
        intersectionPoint = p0 + (t * s1);
        return true;
    }

    return false;
}

GameState::GameState(Game& game, const std::string& levelFile) : car(game.getCar()) {
    initializeCar();
    initialiazeRays();
    placedTileSprites.clear();
    placedTileIDs.clear();

    ResourceManager& resourceManager = ResourceManager::getInstance();
    resourceManager.loadTilesFromCSV("resources/Tiles/Tiles.csv");
    tiles = resourceManager.getTiles();

    loadLevelFromCSV(levelFile, game);
}

void GameState::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.window.close();
        }
        if (isPauseKeyPressed(event)) {
            game.pushState(std::make_shared<PauseState>());
        }
    }
    car.handleInput();
}

void GameState::loadLevelFromCSV(const std::string& filename, Game &game) {

    std::cout << "Level loading...\n";

    std::ifstream file(filename);
    std::string line;
    int idx = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        char comma;
        int x, y;

        std::cout << "idx: " << idx << "\n";

        if(idx == 0){
            ss >> x >> comma >> y;

            // read the boundaries from the file
            boundaries = {x, y};

            // Resize the vectors so they contain the necessary number of elements
            placedTileIDs.resize(x, std::vector<int>(y, -1));
            placedTileSprites.resize(x, std::vector<sf::Sprite>(y));
        }else{
            int texture;

            ss >> x >> comma >> y >> comma >> texture;

            std::cout << "pos: [" << x << "/" << y << "], texture: " << texture << "\n";

            if (x < 0 || x > boundaries.x || y < 0 || y > boundaries.y){
                std::cerr << "The file seems to be corrupt!\n";
                return; // Return because the tiles are out of bounds!
            }

            sf::Sprite s;
            s.setTexture(tiles[texture].getTexture());
            s.setScale(game.getTileSize() / s.getLocalBounds().height, game.getTileSize() / s.getLocalBounds().height);
            s.setPosition(game.getTileSize() * x, game.getTileSize() * y);

            placedTileSprites[x][y] = s;
            placedTileIDs[x][y] = texture;
        }
        idx++;
    }
}

void GameState::initialiazeRays() {
    rayDistances.resize(5, 0.0f);
    rays.resize(5);
    collisionMarkers.reserve(5);
}

void GameState::performRaycasts(Game& game) {
    float rotation_angle = car.getRotationAngle();
    sf::Vector2f carPosition = car.getCurrentPosition();

    std::vector<float> rayAngles = {
        rotation_angle - 90.0f,
        rotation_angle + 90.0f,
        rotation_angle,
        rotation_angle - 45.0f,
        rotation_angle + 45.0f
    };

    for (auto& angle : rayAngles) {
        if (angle < 0.0f) angle += 360.0f;
        if (angle >= 360.0f) angle -= 360.0f;
    }

    float maxRayLength = 1000000.0f;

    collisionMarkers.clear();

    for (size_t i = 0; i < rayAngles.size(); ++i) {
        float angle = rayAngles[i];
        float radian_angle = angle * (M_PI / 180.0f);
        sf::Vector2f direction(std::sin(radian_angle), -std::cos(radian_angle));

        sf::Vector2f rayEnd = carPosition + direction * maxRayLength;

        float minDistance = maxRayLength;
        sf::Vector2f closestPoint = rayEnd;

        for (const auto& wall : walls) {
            sf::FloatRect wallBounds = wall.getGlobalBounds();

            sf::Vector2f p1(wallBounds.left, wallBounds.top);
            sf::Vector2f p2(wallBounds.left + wallBounds.width, wallBounds.top);
            sf::Vector2f p3(wallBounds.left + wallBounds.width, wallBounds.top + wallBounds.height);
            sf::Vector2f p4(wallBounds.left, wallBounds.top + wallBounds.height);

            std::vector<std::pair<sf::Vector2f, sf::Vector2f>> edges = {
                {p1, p2},
                {p2, p3},
                {p3, p4},
                {p4, p1}
            };

            for (const auto& edge : edges) {
                sf::Vector2f intersectionPoint;
                if (getLineIntersection(carPosition, rayEnd, edge.first, edge.second, intersectionPoint)) {
                    float distance = sqrtf((intersectionPoint.x - carPosition.x) * (intersectionPoint.x - carPosition.x) +
                                           (intersectionPoint.y - carPosition.y) * (intersectionPoint.y - carPosition.y));
                    if (distance < minDistance) {
                        minDistance = distance;
                        closestPoint = intersectionPoint;
                    }
                }
            }
        }

        rayDistances[i] = minDistance;

        sf::VertexArray ray(sf::Lines, 2);
        ray[0].position = carPosition;
        ray[0].color = sf::Color(0, 255, 0, 255);;
        ray[1].position = closestPoint;
        ray[1].color = sf::Color(0, 255, 0, 255);
        rays[i] = ray;

        sf::VertexArray collisionMarker(sf::Lines, 4);

        float markerSize = 15.0f;

        sf::Color markerColor(0, 255, 80, 255); // RGBA: Grey with 50% transparency

        collisionMarker[0].position = closestPoint + sf::Vector2f(-markerSize, -markerSize);
        collisionMarker[0].color = markerColor;
        collisionMarker[1].position = closestPoint + sf::Vector2f(markerSize, markerSize);
        collisionMarker[1].color = markerColor;

        collisionMarker[2].position = closestPoint + sf::Vector2f(markerSize, -markerSize);
        collisionMarker[2].color = markerColor;
        collisionMarker[3].position = closestPoint + sf::Vector2f(-markerSize, markerSize);
        collisionMarker[3].color = markerColor;

        collisionMarkers.push_back(collisionMarker);
    }
}


void GameState::update(Game& game) {
    car.update(game.dt);
    performRaycasts(game);

    timeSinceLastPrint += game.dt;
    if (timeSinceLastPrint >= 1.0f) {
        std::cout << "Ray distances: ";
        for (size_t i = 0; i < rayDistances.size(); ++i) {
            std::cout << rayDistances[i] << " ";
        }
        std::cout << std::endl;

        timeSinceLastPrint = 0.0f;
    }

    sf::FloatRect carBounds = car.getBounds();

    for (const auto& wall : walls) {
        if (carBounds.intersects(wall.getGlobalBounds())) {
            game.changeState(std::make_shared<DeathState>());
            return;
        }
    }
}

void GameState::debugDrawing(Game& game) {
    walls.clear();

    float thickness = 5.0f;
    sf::Vector2u windowSize = game.window.getSize();

    sf::RectangleShape topWall(sf::Vector2f(windowSize.x, thickness));
    topWall.setPosition(0, 0);
    topWall.setFillColor(sf::Color::Red);
    walls.push_back(topWall);

    sf::RectangleShape bottomWall(sf::Vector2f(windowSize.x, thickness));
    bottomWall.setPosition(0, windowSize.y - thickness);
    bottomWall.setFillColor(sf::Color::Red);
    walls.push_back(bottomWall);

    sf::RectangleShape leftWall(sf::Vector2f(thickness, windowSize.y));
    leftWall.setPosition(0, 0);
    leftWall.setFillColor(sf::Color::Red);
    walls.push_back(leftWall);

    sf::RectangleShape rightWall(sf::Vector2f(thickness, windowSize.y));
    rightWall.setPosition(windowSize.x - thickness, 0);
    rightWall.setFillColor(sf::Color::Red);
    walls.push_back(rightWall);

    for (const auto& wall : walls) {
        game.window.draw(wall);
    }
}

void GameState::render(Game& game) {
    game.window.clear();
    for (const auto &tileX : placedTileSprites) {
        for(const auto &tileY : tileX) {
            game.window.draw(tileY);
        }
    }

    car.render(game.window);

    for (const auto& ray : rays) {
        game.window.draw(ray);
    }

    for (const auto& collisionMarker : collisionMarkers) {
        game.window.draw(collisionMarker);
    }

    debugDrawing(game);

}

void GameState::initializeCar() {
    sf::Sprite &carSprite = car.getCarSprite();
    carSprite.setOrigin(carSprite.getLocalBounds().width / 2, carSprite.getLocalBounds().height / 2);
    carSprite.setPosition(400, 400);
    car.resetVelocity();
    car.resetAngularAcceleration();
    car.resetRotationAngle();
    car.setPreviousPosition({carSprite.getPosition().x, carSprite.getPosition().y});
    car.setCurrentPosition({carSprite.getPosition().x, carSprite.getPosition().y});
}

bool GameState::isPauseKeyPressed(const sf::Event& event) const {
    return (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P);
}

sf::RectangleShape GameState::createRoad(Game& game) const {
    sf::RectangleShape road(sf::Vector2f(game.window.getSize().x - 20, game.window.getSize().y - 20));
    road.setPosition(10, 10);
    road.setFillColor(sf::Color{80, 80, 80});
    return road;
}
