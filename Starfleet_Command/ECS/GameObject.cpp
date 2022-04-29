#include "GameObject.hpp"

void GameObject::Awake()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Awake();
    }
}

void GameObject::Start()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Start();
    }
}

void GameObject::Update(sf::Time deltaTime)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Update(deltaTime);
    }
}

void GameObject::LateUpdate(sf::Time deltaTime)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->LateUpdate(deltaTime);
    }
}

void GameObject::Render(sf::RenderWindow& window)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Render(window);
    }
}