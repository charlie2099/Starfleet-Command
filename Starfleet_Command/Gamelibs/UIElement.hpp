#ifndef STARFLEET_COMMAND_UIELEMENT_HPP
#define STARFLEET_COMMAND_UIELEMENT_HPP
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * Base class for all UI elements
 */
class UIElement
{
public:
    UIElement(sf::Vector2f& pos, sf::Vector2f& size) : _position(pos), _size(size) {}
    ~UIElement() = default;

   virtual void EventHandler(sf::RenderWindow& window, sf::Event& event) = 0;
   virtual void Update(sf::RenderWindow& window) = 0;
   virtual void Render(sf::RenderWindow& window) = 0;

   virtual void SetPosition(sf::Vector2f& pos) { _position = pos;  }
   virtual void SetSize(sf::Vector2f& size) { _size = size;  }

    virtual sf::Vector2f GetPos() { return _position; }
    virtual sf::Vector2f GetSize() { return _size; }

protected:
    sf::Vector2f  _position;
    sf::Vector2f  _size;
};

#endif //STARFLEET_COMMAND_UIELEMENT_HPP
