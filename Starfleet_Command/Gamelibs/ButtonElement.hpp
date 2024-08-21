#ifndef STARFLEET_COMMAND_BUTTONELEMENT_HPP
#define STARFLEET_COMMAND_BUTTONELEMENT_HPP
#include "UIElement.hpp"

class ButtonElement : public UIElement
{
public:
    ButtonElement(sf::Vector2f &pos, sf::Vector2f &size);

    void EventHandler(sf::RenderWindow &window, sf::Event &event) override;
    void Update(sf::RenderWindow &window) override;
    void Render(sf::RenderWindow &window) override;

    virtual bool IsMouseOver() const { return _isMouseOver; }
    virtual bool isPressed() const { return _isPressed; }

private:
    bool _isMouseOver;
    bool _isPressed;
};

#endif //STARFLEET_COMMAND_BUTTONELEMENT_HPP
