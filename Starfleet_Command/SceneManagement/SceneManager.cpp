#include "SceneManager.hpp"

bool SceneManager::init()
{
    current_scene = std::make_unique<MenuScene>();
    return current_scene->Init();
}

void SceneManager::eventHandler(sf::RenderWindow& window, sf::Event& event)
{
    current_scene->EventHandler(window, event);
}

void SceneManager::update(sf::RenderWindow &window, sf::Time deltaTime)
{
    if (current_scene->GetScene() != current_ID)
    {
        changeScene(current_scene->GetScene());
    }
    current_scene->Update(window, deltaTime);
}

void SceneManager::render(sf::RenderWindow& window)
{
    current_scene->Render(window);
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
        case Scene::ID::GAME:
            //current_scene = std::make_unique<GameScene>();
            current_scene = std::make_unique<GameScene>();
            break;
    }
    current_scene->SetScene(id);
    current_scene->Init();
}




