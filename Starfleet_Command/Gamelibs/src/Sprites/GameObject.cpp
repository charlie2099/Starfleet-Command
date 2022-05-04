#include <iostream>
#include "Sprites/GameObject.hpp"

/*void GameObject::AddComponent(const std::shared_ptr<IComponent>& component)
{
    m_components[std::type_index(typeid(*component))] = component;
}*/

/*template<typename T>
std::shared_ptr<T> GameObject::GetComponent()
{
    std::type_index index(typeid(T));
    if(m_components.count(std::type_index(typeid(T))))
    {
        return static_pointer_cast<T>(m_components[index]);
    }
    else
    {
        std::cout << "No component found: " <<std::endl;
        return nullptr;
    }
}*/

IComponent* GameObject::AddComponent(std::unique_ptr<IComponent> component)
{
    m_components.push_back(std::move(component));
    return m_components.back().get();
}

/*std::unique_ptr<IComponent> GameObject::GetComponent(std::unique_ptr<IComponent> component)
{
//    for (int i = 0; i < m_components.size(); ++i)
//    {
//        std::cout << "component found!: " << dynamic_cast<IComponent*>(m_components[i].get()) <<std::endl;
//    }

    return component;
}*/

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










