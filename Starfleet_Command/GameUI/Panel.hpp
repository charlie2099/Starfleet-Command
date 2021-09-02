#ifndef STARFLEET_COMMAND_PANEL_HPP
#define STARFLEET_COMMAND_PANEL_HPP
#include <SFML/Graphics.hpp>

///* Panels will adjust in size to fit text of any
///  string length given to it. Padding can be
///  customised as desired.*/
class Panel
{
 public:
    Panel();
    ~Panel() = default;

    void eventHandler(sf::RenderWindow& window, sf::Event& event);
    void update(sf::RenderWindow& window, sf::Time deltaTime);
    void render(sf::RenderWindow& window);

    // Panel
    void setPanelColour(sf::Color color);
    void setPadding(float padding);
    void setSize(float width, float height);
    void setPosition(float x, float y);

    // Text
    void setText(const std::string& text_str);
    void setText(const std::string& text_str, sf::Color colour);
    enum class TextAlign { CENTRE, OFFSET };
    void setTextOffset(TextAlign alignment, float offset);

    // Button adaptation
    void setIsClicked(bool clicked);
    bool isClicked() const;
    void setIsHoveredOver(bool hovered_over);
    bool isHoveredOver() const;

private:
    bool loadTextures();
    bool loadFonts();
    void centreAlignPanelToText();
    void offsetAlignTextToPanel();

    sf::RectangleShape panel;
    sf::Texture panel_texture;
    sf::Text text;
    sf::Font font_regular;
    sf::Font font_bold;
    TextAlign textAlign = TextAlign::CENTRE;

    float panel_offset = 50.0F;
    float text_offset = 0.0F;
    bool is_clicked = false;
    bool is_hovered_over = false;
};

#endif //STARFLEET_COMMAND_PANEL_HPP
