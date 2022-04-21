#include <iostream>
#include "Panel.hpp"

Panel::Panel()
{
    LoadTextures();
    LoadFonts();

    // default design for panels upon construction
    text.setString("Text");
    text.setFont(font_regular);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(400, 400);

    panel.setTexture(&panel_texture);
    CentreAlignPanelToText();
}

void Panel::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    if (event.type == sf::Event::MouseButtonPressed && is_hovered_over/* && event.mouseButton.button == sf::Mouse::Left*/)
    {
        is_clicked = true;
    }
    else if (event.type == sf::Event::MouseButtonReleased/* && event.mouseButton.button == sf::Mouse::Left*/)
    {
        is_clicked = false;
    }
}

void Panel::Update(sf::RenderWindow &window)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    if(panel.getGlobalBounds().contains(translated_pos))
    {
        is_hovered_over = true;
    }
    else
    {
        is_hovered_over = false;
    }
}

void Panel::Render(sf::RenderWindow& window)
{
    window.draw(panel);
    window.draw(text);
}

void Panel::SetPanelColour(sf::Color color)
{
    panel.setFillColor(color);
}

void Panel::SetPadding(float padding)
{
    panel_w = padding;
    panel_h = padding;
    CentreAlignPanelToText();
}

void Panel::SetSize(float width, float height)
{
    panel_w = width;
    panel_h = height;
    auto panel_width = text.getGlobalBounds().width + panel_w * 2;
    auto panel_height = text.getGlobalBounds().height + panel_h;
    panel.setSize({panel_width, panel_height});
    CentreAlignPanelToText();
}

void Panel::SetPosition(float x, float y)
{
    text.setPosition(x, y);
    CentreAlignPanelToText();
}

void Panel::SetText(const std::string& text_str)
{
    text.setString(text_str);
    CentreAlignPanelToText();
}

void Panel::SetText(const std::string& text_str, sf::Color colour)
{
    text.setString(text_str);
    text.setFillColor(colour);
    CentreAlignPanelToText();
}

void Panel::SetTextSize(int text_size)
{
    text.setCharacterSize(text_size);
    CentreAlignPanelToText();
}

void Panel::SetTextOffset(TextAlign alignment, float offset)
{
    textAlign = alignment;
    text_offset = offset;
    CentreAlignPanelToText();
}

void Panel::SetFont(Panel::TextFont text_font)
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

bool Panel::LoadTextures()
{
    if (!panel_texture.loadFromFile("images/panel_image1.png"))
    {
        return false;
    }
    return true;
}

/// Unnecessary to load fonts which may not even be used
bool Panel::LoadFonts()
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

void Panel::CentreAlignPanelToText()
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

bool Panel::IsHoveredOver() const
{
    return is_hovered_over;
}

bool Panel::IsClicked() const
{
    return is_clicked;
}

sf::Text& Panel::GetText()
{
    return text;
}

sf::FloatRect Panel::GetTextSize()
{
    /// Panels adjust to accommodate text
    return text.getGlobalBounds();
}

sf::Vector2f Panel::GetTextPosition()
{
    /// Panels follow text position
    return text.getPosition();
}

sf::FloatRect Panel::GetPanelSize()
{
    /// Panels adjust to accommodate text
    return panel.getGlobalBounds();
}

sf::Vector2f Panel::GetPanelPosition()
{
    /// Panels follow text position
    return panel.getPosition();
}

/*Button &Panel::getButton()
{
    return button;
}*/



