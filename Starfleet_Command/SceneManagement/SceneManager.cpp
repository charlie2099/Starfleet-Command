#include "SceneManager.hpp"

bool SceneManager::Init()
{
    current_scene = std::make_unique<MenuScene>();
    return current_scene->Init();
}

void SceneManager::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    current_scene->EventHandler(window, event);
}

void SceneManager::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    if (current_scene->GetScene() != current_ID)
    {
        ChangeScene(current_scene->GetScene());
    }
    current_scene->Update(window, deltaTime);
}

void SceneManager::Render(sf::RenderWindow& window)
{
    current_scene->Render(window);
}

void SceneManager::ChangeScene(Scene::ID id)
{
    current_scene = nullptr;
    current_ID    = id;

    switch (id)
    {
        case Scene::ID::MENU:
            current_scene = std::make_unique<MenuScene>();
            break;
        case Scene::ID::GAME:
            current_scene = std::make_unique<GameScene>();
            break;
        case Scene::ID::OPTIONS:
            current_scene = std::make_unique<OptionsScene>();
            break;
    }
    current_scene->SetScene(id);
    current_scene->Init();
}




