#include "Sprites/GameObject.hpp"

Component* GameObject::AddComponent(std::unique_ptr<Component> component)
{
    components.push_back(std::move(component));
    return components.back().get();
}

void GameObject::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    for (auto& component : components)
    {
        component->EventHandler(window, event);
    }
}

void GameObject::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    for (auto& component : components)
    {
        component->Update(window, deltaTime);
    }
}

void GameObject::Render(sf::RenderWindow &window)
{
    for (auto& component : components)
    {
        component->Render(window);
    }
}
