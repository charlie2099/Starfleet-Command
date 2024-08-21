#include "TextElement.hpp"

TextElement::TextElement(std::string& text, sf::Font& font, int textSize, sf::Vector2f& pos, sf::Vector2f& size)
: _text(text, font, textSize), UIElement(pos, size)
{
    _text.setPosition(pos);
    _text.setOutlineColor(sf::Color::Black);
}

void TextElement::EventHandler(sf::RenderWindow& window, sf::Event& event)
{

}

void TextElement::Update(sf::RenderWindow& window)
{
    /*switch (_textHorizontalAlignment)
    {
        case TextHorizontalAlignment::LEFT:
            break;
        case TextHorizontalAlignment::CENTRE:
            break;
        case TextHorizontalAlignment::RIGHT:
            break;
    }

    switch (_textVerticalAlignment)
    {
        case TextVerticalAlignment::TOP:
            break;
        case TextVerticalAlignment::CENTRE:
            break;
        case TextVerticalAlignment::BOTTOM:
            break;
    }*/
}

void TextElement::Render(sf::RenderWindow& window)
{
    window.draw(_text);
}

void TextElement::SetPosition(sf::Vector2f &pos)
{
    UIElement::SetPosition(pos);
    _text.setPosition(pos);
}

void TextElement::SetText(std::string &text)
{
    _text.setString(text);
}

void TextElement::SetTextSize(int size)
{
    _text.setCharacterSize(size);
}

void TextElement::SetColour(sf::Color &colour)
{
    _text.setFillColor(colour);
}

void TextElement::SetFont(sf::Font &font)
{
    _text.setFont(font);
}

void TextElement::SetStyle(sf::Text::Style style)
{
    _text.setStyle(style);
}

void TextElement::SetTextAlignment(TextHorizontalAlignment horizontalAlignment,
                                   TextVerticalAlignment verticalAlignment)
{
    _textHorizontalAlignment = horizontalAlignment;
    _textVerticalAlignment = verticalAlignment;
}



