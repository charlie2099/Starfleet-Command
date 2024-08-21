#ifndef STARFLEET_COMMAND_TEXTBUTTONELEMENT_HPP
#define STARFLEET_COMMAND_TEXTBUTTONELEMENT_HPP
#include "ButtonElement.hpp"

class TextButtonElement : public ButtonElement
{
public:
    TextButtonElement(sf::Vector2f &pos, sf::Vector2f &size);
    void EventHandler(sf::RenderWindow &window, sf::Event &event) override;
    void Update(sf::RenderWindow &window) override;
    void Render(sf::RenderWindow &window) override;

    bool IsMouseOver() const override;
    bool isPressed() const override;

};

#endif //STARFLEET_COMMAND_TEXTBUTTONELEMENT_HPP
