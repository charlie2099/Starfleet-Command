#ifndef STARFLEET_COMMAND_PANEL_HPP
#define STARFLEET_COMMAND_PANEL_HPP
#include <SFML/Graphics.hpp>

///* Panels will adjust in size to fit text of any
///  string length given to it. Padding can be
///  customised as desired.*/
class Panel
{
 public:
    Panel();  /// Create the panel in the constructor;
    ~Panel() = default;

    void render(sf::RenderWindow& window);

    // Panel
    void setPanelColour(sf::Color color);
    void setPadding(float width, float height);
    void setPosition(float x, float y);

    // Text
    void setText(sf::Text text);
    void setText(sf::Text text, sf::Color colour);

 private:
    bool loadTextures();
    bool loadFonts();
    sf::RectangleShape panel;
    sf::Texture panel_texture;
    sf::Text text;
    sf::Font font_regular;
    sf::Font font_bold;
};

#endif //STARFLEET_COMMAND_PANEL_HPP
