#ifndef STARFLEET_COMMAND_IEFFECT_HPP
#define STARFLEET_COMMAND_IEFFECT_HPP
#include <SFML/Graphics/RenderWindow.hpp>

class IEffect
{
public:
    virtual void Update(sf::RenderWindow &window, sf::Time &deltaTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual bool IsFinished() = 0;
};

#endif //STARFLEET_COMMAND_IEFFECT_HPP
