#ifndef STARFLEET_COMMAND_GAMEOBJECT_HPP
#define STARFLEET_COMMAND_GAMEOBJECT_HPP
#include "../Components/IComponent.hpp"
#include "../Components/NewSpriteComponent.hpp"
#include <memory>
#include <vector>

class GameObject
{
public:
    GameObject() = default;

    virtual void EventHandler(sf::RenderWindow& window, sf::Event& event);
    virtual void Update(sf::RenderWindow &window, sf::Time deltaTime);
    virtual void Render(sf::RenderWindow& window);

    /// Not all GameObjects may contain a sprite or physics
    IComponent* AddComponent(std::unique_ptr<IComponent> component);

private:
    std::vector<std::unique_ptr<IComponent>> m_components;
};

#endif //STARFLEET_COMMAND_GAMEOBJECT_HPP
