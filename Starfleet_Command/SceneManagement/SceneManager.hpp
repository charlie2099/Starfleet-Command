#ifndef STARFLEET_COMMAND_SCENEMANAGER_HPP
#define STARFLEET_COMMAND_SCENEMANAGER_HPP
#include "Scene.hpp"
#include "../SceneManagement/Scenes/MenuScene.hpp"
#include "../SceneManagement/Scenes/GameScene.hpp"
#include "../SceneManagement/Scenes/ShipyardScene.hpp"

class SceneManager
{
 public:
    SceneManager() = default;
    ~SceneManager() = default;

    bool init();
    void eventHandler(sf::RenderWindow& window, sf::Event& event);
    void update(sf::RenderWindow &window, sf::Time deltaTime);
    void render(sf::RenderWindow& window);

    void changeScene(Scene::ID id);

 private:
    std::unique_ptr<Scene> current_scene;
    Scene::ID current_ID{};
};

#endif //STARFLEET_COMMAND_SCENEMANAGER_HPP
