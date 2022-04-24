#ifndef STARFLEET_COMMAND_SCENEMANAGER_HPP
#define STARFLEET_COMMAND_SCENEMANAGER_HPP
#include "Scene.hpp"
#include "Scenes/MenuScene.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/OptionsScene.hpp"

class SceneManager
{
 public:
    SceneManager() = default;
    ~SceneManager() = default;

    bool Init();
    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow &window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void ChangeScene(Scene::ID id);

 private:
    std::unique_ptr<Scene> current_scene;
    Scene::ID current_ID{};

    /// Same background across all scenes
    //sf::Texture _background_texture;
    //sf::Sprite _background_sprite;
};

#endif //STARFLEET_COMMAND_SCENEMANAGER_HPP
