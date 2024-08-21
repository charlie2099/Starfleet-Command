#ifndef STARFLEET_COMMAND_TEXTELEMENT_HPP
#define STARFLEET_COMMAND_TEXTELEMENT_HPP
#include <SFML/Graphics/Text.hpp>
#include "UIElement.hpp"

/**
 * // QUESTION: Is this class even necessary? Just seems like a useless wrapper around a text object.
 */
class TextElement : public UIElement
{
public:
    TextElement(std::string& text, sf::Font& font, int textSize, sf::Vector2f& pos, sf::Vector2f& size);

    enum class TextHorizontalAlignment { LEFT, CENTRE, RIGHT  };
    enum class TextVerticalAlignment { TOP, CENTRE, BOTTOM  };

    void EventHandler(sf::RenderWindow &window, sf::Event &event) override;
    void Update(sf::RenderWindow &window) override;
    void Render(sf::RenderWindow &window) override;

    void SetPosition(sf::Vector2f &pos) override;
    void SetText(std::string& text);
    void SetTextSize(int size);
    void SetColour(sf::Color& colour);
    void SetFont(sf::Font& font);
    void SetStyle(sf::Text::Style style);
    void SetTextAlignment(TextHorizontalAlignment horizontalAlignment, TextVerticalAlignment verticalAlignment);

private:
    TextHorizontalAlignment _textHorizontalAlignment;
    TextVerticalAlignment _textVerticalAlignment;
    sf::Text _text;
};

#endif //STARFLEET_COMMAND_TEXTELEMENT_HPP
