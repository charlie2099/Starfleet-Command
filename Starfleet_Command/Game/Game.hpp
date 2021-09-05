#ifndef STARFLEET_COMMAND_GAME_HPP
#define STARFLEET_COMMAND_GAME_HPP
#include <iostream>
#include "../SceneManagement/Scenes/MenuScene.hpp"
#include "../SceneManagement/Scenes/GameScene.hpp"
#include "../SceneManagement/Scenes/ShipyardScene.hpp"
#include "../SceneManagement/SceneManager.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game
{
 public:
    Game();
    ~Game() = default;
    void run();

 private:
    void processEvents(sf::Event& event);
    void update(sf::Time deltaTime);
    void render();

    void initWindow();
    void initSceneManager();

    sf::RenderWindow window;
    std::unique_ptr<SceneManager> scene_manager;
};

#endif //STARFLEET_COMMAND_GAME_HPP
