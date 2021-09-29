#ifndef STARFLEET_COMMAND_COMPONENT_HPP
#define STARFLEET_COMMAND_COMPONENT_HPP
#include <SFML/Graphics/RenderWindow.hpp>

class Object; // forward declaration

// base class for all components to come
class Component
{
 public:
    explicit Component(Object* owner) : owner(owner){}

    virtual void awake() {};
    virtual void start() {};
    virtual void update(sf::Time deltaTime) {};
    virtual void lateUpdate(sf::Time deltaTime) {};
    virtual void render(sf::RenderWindow& window) {};

 protected:
    Object* owner;
};

#endif //STARFLEET_COMMAND_COMPONENT_HPP
