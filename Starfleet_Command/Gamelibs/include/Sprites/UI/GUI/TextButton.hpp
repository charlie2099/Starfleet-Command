#ifndef STARFLEET_COMMAND_TEXTBUTTON_HPP
#define STARFLEET_COMMAND_TEXTBUTTON_HPP
#include "Utility/CustomFonts.hpp"
#include <SFML/Graphics.hpp>

/*
 * Panels will adjust in size to fit text of any string length given to it.
 * Padding can be customised as desired.
 */
class TextButton
{
 public:
    TextButton();
    explicit TextButton(const std::string& filepath);
    ~TextButton() = default;

    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow& window);
    void Render(sf::RenderWindow& window);

    /// TextButton
    void SetPanelColour(sf::Color color);
    void SetPadding(float padding);
    void SetSize(float width, float height);
    void SetPosition(float x, float y);
    sf::FloatRect GetPanelSize() { return _panel.getGlobalBounds(); }
    sf::Vector2f GetPanelPosition() { return _panel.getPosition(); }

    /// Text
    void SetText(const std::string& text_str);
    void SetText(const std::string& text_str, sf::Color colour);
    void SetTextSize(int text_size);
    enum class TextAlign { CENTRE, OFFSET };
    void SetTextOffset(TextAlign alignment, float offset);
    void SetFont(const sf::Font& font);
    sf::Text &GetText() { return _text; }
    sf::FloatRect GetTextSize() { return _text.getGlobalBounds(); }
    sf::Vector2f GetTextPosition() { return _text.getPosition(); }

    bool IsClicked() const { return _isClicked; }
    bool IsMouseOver() const { return _isMouseHoveredOver; }

private:
    void CentreAlignPanelToText();

    sf::RectangleShape _panel;
    sf::Texture _panelTexture;
    sf::Text _text;
    TextAlign _textAlign = TextAlign::CENTRE;

    float _panelWidth = 50.0F;
    float _panelHeight = 50.0F;
    float _textOffset = 0.0F;

    bool _isClicked = false;
    bool _isMouseHoveredOver = false;
};

#endif //STARFLEET_COMMAND_TEXTBUTTON_HPP
