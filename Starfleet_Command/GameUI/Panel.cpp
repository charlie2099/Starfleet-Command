#include "Panel.hpp"

Panel::Panel()
{
    loadTextures();
    loadFonts();

    // default origin and design for panel upon construction
    text.setString("Text");
    text.setFont(font_regular);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition(400, 400);

    panel.setTexture(&panel_texture);
    alignPanelToText();
}

void Panel::eventHandler(sf::RenderWindow &window, sf::Event &event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        /// BUG: If mouse click held down AND moved around, keeps firing "hello"
        if(panel.getGlobalBounds().contains(translated_pos) && !is_clicked)
        {
            setIsClicked(true);
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        setIsClicked(false);
    }
}

void Panel::update(sf::RenderWindow &window, sf::Time /*deltaTime*/)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    if(panel.getGlobalBounds().contains(translated_pos))
    {
        setIsHoveredOver(true);
    }
    else
    {
        setIsHoveredOver(false);
    }
}

void Panel::render(sf::RenderWindow& window)
{
    window.draw(panel);
    window.draw(text);
}

void Panel::setPanelColour(sf::Color color)
{
    panel.setFillColor(color);
}

void Panel::setPadding(float padding)
{
    panel_offset = padding;
    alignPanelToText();
}

void Panel::setPosition(float x, float y)
{
    text.setPosition(x, y);
    auto panel_xpos = text.getPosition().x - panel_offset;
    auto panel_ypos = (text.getGlobalBounds().top + text.getGlobalBounds().height / 2) - panel.getGlobalBounds().height / 2;
    panel.setPosition(panel_xpos, panel_ypos);
}

void Panel::setText(const std::string& text_str)
{
    text.setString(text_str);
    alignPanelToText();
}

void Panel::setText(const std::string& text_str, sf::Color colour)
{
    text.setString(text_str);
    text.setFillColor(colour);
    alignPanelToText();
}

bool Panel::loadTextures()
{
    if (!panel_texture.loadFromFile("images/panel_image.png"))
    {
        return false;
    }
    return true;
}

/// Unnecessary to load fonts which may not even be used
bool Panel::loadFonts()
{
    if(!font_regular.loadFromFile("fonts/Orbitron/Orbitron-Regular.ttf"))
    {
        return false;
    }
    /*if(!font_bold.loadFromFile("fonts/Orbitron/Orbitron-Bold.ttf"))
    {
        return false;
    }*/
    return true;
}

void Panel::alignPanelToText()
{
    auto panel_width = text.getGlobalBounds().width + panel_offset * 2;
    auto panel_height = text.getGlobalBounds().height + panel_offset;
    panel.setSize({panel_width, panel_height});

    auto panel_xpos = text.getPosition().x - panel_offset;
    auto panel_ypos = (text.getGlobalBounds().top + text.getGlobalBounds().height / 2) - panel.getGlobalBounds().height / 2;
    panel.setPosition(panel_xpos, panel_ypos);
}

void Panel::setIsHoveredOver(bool hovered_over)
{
    is_hovered_over = hovered_over;
}

bool Panel::isHoveredOver() const
{
    return is_hovered_over;
}

void Panel::setIsClicked(bool clicked)
{
    is_clicked = clicked;
}

bool Panel::isClicked() const
{
    return is_clicked;
}






