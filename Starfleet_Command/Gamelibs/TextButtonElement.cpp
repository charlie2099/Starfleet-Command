#include "TextButtonElement.hpp"

TextButtonElement::TextButtonElement(sf::Vector2f &pos, sf::Vector2f &size) : ButtonElement(pos, size)
{}

void TextButtonElement::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    ButtonElement::EventHandler(window, event);
}

void TextButtonElement::Update(sf::RenderWindow &window)
{
    ButtonElement::Update(window);
}

void TextButtonElement::Render(sf::RenderWindow &window)
{
    ButtonElement::Render(window);
}

bool TextButtonElement::IsMouseOver() const
{
    return ButtonElement::IsMouseOver();
}

bool TextButtonElement::isPressed() const
{
    return ButtonElement::isPressed();
}
