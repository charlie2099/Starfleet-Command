#ifndef STARFLEET_COMMAND_ICOMPONENT_HPP
#define STARFLEET_COMMAND_ICOMPONENT_HPP
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

/*
 * Interface for all components to inherit methods from
 */
class IComponent
{
public:
    virtual void EventHandler(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void Update(sf::RenderWindow &window, sf::Time deltaTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
};

#endif //STARFLEET_COMMAND_ICOMPONENT_HPP
