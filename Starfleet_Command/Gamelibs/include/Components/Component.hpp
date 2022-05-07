#ifndef STARFLEET_COMMAND_COMPONENT_HPP
#define STARFLEET_COMMAND_COMPONENT_HPP
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject;

class Component
{
 public:
    //explicit Component(GameObject* owner) : owner(owner){}

    virtual void EventHandler(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void Update(sf::RenderWindow &window, sf::Time deltaTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;

 protected:
    //GameObject* owner;
};

#endif //STARFLEET_COMMAND_COMPONENT_HPP
