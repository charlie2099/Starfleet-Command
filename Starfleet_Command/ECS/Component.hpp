#ifndef STARFLEET_COMMAND_COMPONENT_HPP
#define STARFLEET_COMMAND_COMPONENT_HPP
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject; // forward declaration

// base class for all components to come
class Component
{
 public:
    explicit Component(GameObject* owner) : owner(owner){}

    virtual void Awake() {};
    virtual void Start() {};
    virtual void Update(sf::Time deltaTime) {};
    virtual void LateUpdate(sf::Time deltaTime) {};
    virtual void Render(sf::RenderWindow& window) {};

 protected:
    GameObject* owner;
};

#endif //STARFLEET_COMMAND_COMPONENT_HPP
