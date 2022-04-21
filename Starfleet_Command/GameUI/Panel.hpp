#ifndef STARFLEET_COMMAND_PANEL_HPP
#define STARFLEET_COMMAND_PANEL_HPP
#include <SFML/Graphics.hpp>
#include "Button.hpp"

///* Panels will adjust in size to fit text of any
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

    /// Button adaptation
    //Button &getButton();
    bool IsClicked() const;
    bool IsHoveredOver() const;

private:
    bool LoadTextures();
    bool LoadFonts();
    void CentreAlignPanelToText();

    //Button button;
    sf::RectangleShape panel;
    sf::Texture panel_texture;
    sf::Text text;
    sf::Font font_regular;
    sf::Font font_bold;
    TextAlign textAlign = TextAlign::CENTRE;
    TextFont textFont = TextFont::REGULAR;

    float panel_w = 50.0F;
    float panel_h = 50.0F;
    float text_offset = 0.0F;
    bool is_clicked = false;
    bool is_hovered_over = false;
};

#endif //STARFLEET_COMMAND_PANEL_HPP
