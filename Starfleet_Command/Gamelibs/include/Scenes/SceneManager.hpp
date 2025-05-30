#ifndef STARFLEET_COMMAND_SCENEMANAGER_HPP
#define STARFLEET_COMMAND_SCENEMANAGER_HPP
#include "Scene.hpp"
#include "MenuScene.hpp"
#include "GameScene.hpp"
#include "SplashScene.hpp"
#include "VictoryScene.hpp"
#include "DefeatScene.hpp"

class SceneManager
{
 public:
    SceneManager() = default;
    ~SceneManager() = default;

    bool Init();
    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow &window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void SetPaused(bool paused);

 private:
    void ChangeScene(Scene::ID id);
    std::unique_ptr<Scene> current_scene;
    Scene::ID current_ID{};

    /// Same background across all scenes
    //sf::Texture _backgroundTexture;
    //sf::Sprite _backgroundSprite;
};

#endif //STARFLEET_COMMAND_SCENEMANAGER_HPP
