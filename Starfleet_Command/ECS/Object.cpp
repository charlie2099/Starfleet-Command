#include "Object.hpp"

void Object::awake()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->awake();
    }
}

void Object::start()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->start();
    }
}

void Object::update(sf::Time deltaTime)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->update(deltaTime);
    }
}

void Object::lateUpdate(sf::Time deltaTime)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->lateUpdate(deltaTime);
    }
}

void Object::render(sf::RenderWindow& window)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->render(window);
    }
}