#include "SceneManager.hpp"

bool SceneManager::init()
{
    //changeScene(Scene::ID::MENU);
    current_scene = std::make_unique<MenuScene>();
    return current_scene->init();
}

void SceneManager::eventHandler(sf::RenderWindow& window, sf::Event& event)
{
    current_scene->eventHandler(window, event);
}

void SceneManager::update(sf::RenderWindow &window, sf::Time deltaTime)
{
    if (current_scene->getScene() != current_ID)
    {
        changeScene(current_scene->getScene());
    }
    current_scene->update(window, deltaTime);
}

void SceneManager::render(sf::RenderWindow& window)
{
    current_scene->render(window);
}

void SceneManager::changeScene(Scene::ID id)
{
    current_scene = nullptr;
    current_ID    = id;

    switch (id)
    {
        case Scene::ID::MENU:
            current_scene = std::make_unique<MenuScene>();
            break;
        case Scene::ID::SHIPYARD:
            current_scene = std::make_unique<ShipyardScene>();
            break;
        case Scene::ID::GAME:
            current_scene = std::make_unique<GameScene>();
            break;
    }
    current_scene->setScene(id);
    current_scene->init();
}




