#include <iostream>
#include "Panel.hpp"

Panel::Panel()
{
    loadTextures();
    loadFonts();

    // default design for panels upon construction
    text.setString("Text");
    text.setFont(font_regular);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(400, 400);

    panel.setTexture(&panel_texture);
    centreAlignPanelToText();
}

void Panel::eventHandler(sf::RenderWindow &window, sf::Event &event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    if (event.type == sf::Event::MouseButtonPressed/* && event.mouseButton.button == sf::Mouse::Left*/)
    {
        if(panel.getGlobalBounds().contains(translated_pos))
        {
            setIsClicked(true);
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased/* && event.mouseButton.button == sf::Mouse::Left*/)
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
    panel_w = padding;
    panel_h = padding;
    centreAlignPanelToText();
}

void Panel::setSize(float width, float height)
{
    panel_w = width;
    panel_h = height;
    auto panel_width = text.getGlobalBounds().width + panel_w * 2;
    auto panel_height = text.getGlobalBounds().height + panel_h;
    panel.setSize({panel_width, panel_height});
    centreAlignPanelToText();
}

void Panel::setPosition(float x, float y)
{
    text.setPosition(x, y);
    centreAlignPanelToText();
}

void Panel::setText(const std::string& text_str)
{
    text.setString(text_str);
    centreAlignPanelToText();
}

void Panel::setText(const std::string& text_str, sf::Color colour)
{
    text.setString(text_str);
    text.setFillColor(colour);
    centreAlignPanelToText();
}

void Panel::setTextSize(int text_size)
{
    text.setCharacterSize(text_size);
    centreAlignPanelToText();
}

void Panel::setTextOffset(TextAlign alignment, float offset)
{
    textAlign = alignment;
    text_offset = offset;
    centreAlignPanelToText();
}

void Panel::setFont(Panel::TextFont text_font)
{
    textFont = text_font;
    if(textFont == TextFont::REGULAR)
    {
        text.setFont(font_regular);
    }
    else if(textFont == TextFont::BOLD)
    {
        text.setFont(font_bold);
    }
}

bool Panel::loadTextures()
{
    if (!panel_texture.loadFromFile("images/panel_image1.png"))
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
    if(!font_bold.loadFromFile("fonts/Orbitron/Orbitron-Bold.ttf"))
    {
        return false;
    }
    return true;
}

void Panel::centreAlignPanelToText()
{
    // Update panel size before re-centering text
    auto panel_width = text.getGlobalBounds().width + panel_w * 2;
    auto panel_height = text.getGlobalBounds().height + panel_h;
    panel.setSize({panel_width, panel_height});

    if(textAlign == TextAlign::CENTRE)
    {
        auto panel_xpos = text.getPosition().x - panel_w;
        auto panel_ypos = (text.getGlobalBounds().top + text.getGlobalBounds().height / 2) - panel.getGlobalBounds().height / 2;
        panel.setPosition(panel_xpos, panel_ypos);
    }
    else if(textAlign == TextAlign::OFFSET)
    {
        auto panel_xpos = text.getPosition().x - panel_w;
        auto panel_ypos = (text.getPosition().y - text_offset);
        panel.setPosition(panel_xpos, panel_ypos);
    }
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

sf::FloatRect Panel::getTextSize()
{
    /// Panels adjust to accommodate text
    return text.getGlobalBounds();
}

sf::Vector2f Panel::getTextPosition()
{
    /// Panels follow text position
    return text.getPosition();
}

sf::FloatRect Panel::getPanelSize()
{
    /// Panels adjust to accommodate text
    return panel.getGlobalBounds();
}

sf::Vector2f Panel::getPanelPosition()
{
    /// Panels follow text position
    return panel.getPosition();
}


