#include "GameObject.hpp"

IComponent* GameObject::AddComponent(std::unique_ptr<IComponent> component)
{
    m_components.push_back(std::move(component));
    return m_components.back().get();
}

void GameObject::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    for(auto& component : m_components)
    {
        component->EventHandler(window, event);
    }
}

void GameObject::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    for (auto& component : m_components)
    {
        component->Update(window, deltaTime);
    }
}

void GameObject::Render(sf::RenderWindow& window)
{
    for (auto& component : m_components)
    {
        component->Render(window);
    }
}






