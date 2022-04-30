#ifndef STARFLEET_COMMAND_COMPONENT_HPP
#define STARFLEET_COMMAND_COMPONENT_HPP
#include <SFML/Graphics/RenderWindow.hpp>

class Entity; // forward declaration

// base class for all m_components to come
class Component
{
 public:
    explicit Component(Entity* owner) : owner(owner){}

    virtual void Awake() {};
    virtual void Start() {};
    virtual void Update(sf::Time deltaTime) {};
    virtual void LateUpdate(sf::Time deltaTime) {};
    virtual void Render(sf::RenderWindow& window) {};

 protected:
    Entity* owner;
};

#endif //STARFLEET_COMMAND_COMPONENT_HPP
