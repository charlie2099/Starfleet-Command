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

    void eventHandler(sf::RenderWindow& window, sf::Event& event);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    // Panel
    void setPanelColour(sf::Color color);
    void setPadding(float padding);
    void setSize(float width, float height);
    void setPosition(float x, float y);
    sf::FloatRect getPanelSize();
    sf::Vector2f getPanelPosition();

    // Text
    void setText(const std::string& text_str);
    void setText(const std::string& text_str, sf::Color colour);
    void setTextSize(int text_size);
    enum class TextAlign { CENTRE, OFFSET };
    void setTextOffset(TextAlign alignment, float offset);
    enum class TextFont { REGULAR, BOLD };
    void setFont(TextFont text_font);
    sf::Text &getText();
    sf::FloatRect getTextSize();
    sf::Vector2f getTextPosition();

    /// Button adaptation
    //Button &getButton();
    bool isClicked() const;
    bool isHoveredOver() const;

private:
    bool loadTextures();
    bool loadFonts();
    void centreAlignPanelToText();

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
