#include "Sprites/Entity.hpp"

void Entity::Awake()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Awake();
    }
}

void Entity::Start()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Start();
    }
}

void Entity::Update(sf::Time deltaTime)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Update(deltaTime);
    }
}

void Entity::LateUpdate(sf::Time deltaTime)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->LateUpdate(deltaTime);
    }
}

void Entity::Render(sf::RenderWindow& window)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Render(window);
    }
}