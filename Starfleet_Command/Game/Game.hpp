#ifndef STARFLEET_COMMAND_GAME_HPP
#define STARFLEET_COMMAND_GAME_HPP
#include "Scenes/MenuScene.hpp"
#include "Scenes/SceneManager.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Game // Rename to Engine?
{
 public:
    Game();
    ~Game() = default;
    void Run();

 private:
    void ProcessEvents(sf::Event& event);
    void Update(sf::Time deltaTime);
    void Render();

    void InitWindow();
    void InitSceneManager();

    sf::RenderWindow window;
    std::unique_ptr<SceneManager> scene_manager;
};

#endif //STARFLEET_COMMAND_GAME_HPP
