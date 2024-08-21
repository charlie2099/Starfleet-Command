#ifndef STARFLEET_COMMAND_PANEL_HPP
#define STARFLEET_COMMAND_PANEL_HPP
#include <SFML/Graphics.hpp>
#include "Sprites/UI/GUI/Button.hpp"

///* Panels will adjust in size to fit _text of any
///  string length given to it. Padding can be
///  customised as desired.*/
class Panel
{
 public:
    Panel();
    ~Panel() = default;

    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow& window);
    void Render(sf::RenderWindow& window);

    // Panel
    void SetPanelColour(sf::Color color);
    void SetPadding(float padding);
    void SetSize(float width, float height);
    void SetPosition(float x, float y);
    sf::FloatRect GetPanelSize();
    sf::Vector2f GetPanelPosition();

    // Text
    void SetText(const std::string& text_str);
    void SetText(const std::string& text_str, sf::Color colour);
    void SetTextSize(int text_size);
    enum class TextAlign { CENTRE, OFFSET };
    void SetTextOffset(TextAlign alignment, float offset);
    enum class TextFont { REGULAR, BOLD };
    void SetFont(TextFont text_font);
    sf::Text &GetText();
    sf::FloatRect GetTextSize();
    sf::Vector2f GetTextPosition();

    bool IsClicked() const;
    bool IsHoveredOver() const;

private:
    bool LoadTextures();
    bool LoadFonts();
    void InitText();
    void CentreAlignPanelToText();

    //Button button;
    sf::RectangleShape _panel;
    sf::Texture _panelTexture;
    sf::Text _text;
    sf::Font _fontRegular;
    sf::Font _fontBold;
    TextAlign _textAlign = TextAlign::CENTRE;
    TextFont _textFont = TextFont::REGULAR;

    float _panelWidth = 50.0F;
    float _panelHeight = 50.0F;
    float _textOffset = 0.0F;
    bool _isClicked = false;
    bool _isHoveredOver = false;
};

#endif //STARFLEET_COMMAND_PANEL_HPP
