#include <iostream>
#include "Sprites/UI/Panel.hpp"

Panel::Panel()
{
    LoadTextures();
    LoadFonts();
    InitText();
    _panel.setTexture(&_panelTexture);
    CentreAlignPanelToText();
}

void Panel::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
    auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse _position translated into world coordinates

    if (event.type == sf::Event::MouseButtonPressed && _isHoveredOver/* && event.mouseButton.button == sf::Mouse::Left*/)
    {
        _isClicked = true;
    }
    else if (event.type == sf::Event::MouseButtonReleased/* && event.mouseButton.button == sf::Mouse::Left*/)
    {
        _isClicked = false;
    }
}

void Panel::Update(sf::RenderWindow &window)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
    auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse _position translated into world coordinates

    if(_panel.getGlobalBounds().contains(translated_pos))
    {
        _isHoveredOver = true;
    }
    else
    {
        _isHoveredOver = false;
    }
}

void Panel::Render(sf::RenderWindow& window)
{
    window.draw(_panel);
    window.draw(_text);
}

void Panel::SetPanelColour(sf::Color color)
{
    _panel.setFillColor(color);
}

void Panel::SetPadding(float padding)
{
    _panelWidth = padding;
    _panelHeight = padding;
    CentreAlignPanelToText();
}

void Panel::SetSize(float width, float height)
{
    _panelWidth = width;
    _panelHeight = height;
    auto panel_width = _text.getGlobalBounds().width + _panelWidth * 2;
    auto panel_height = _text.getGlobalBounds().height + _panelHeight;
    _panel.setSize({panel_width, panel_height});
    CentreAlignPanelToText();
}

void Panel::SetPosition(float x, float y)
{
    _text.setPosition(x, y);
    CentreAlignPanelToText();
}

void Panel::SetText(const std::string& text_str)
{
    _text.setString(text_str);
    CentreAlignPanelToText();
}

void Panel::SetText(const std::string& text_str, sf::Color colour)
{
    _text.setString(text_str);
    _text.setFillColor(colour);
    CentreAlignPanelToText();
}

void Panel::SetTextSize(int text_size)
{
    _text.setCharacterSize(text_size);
    CentreAlignPanelToText();
}

void Panel::SetTextOffset(TextAlign alignment, float offset)
{
    _textAlign = alignment;
    _textOffset = offset;
    CentreAlignPanelToText();
}

void Panel::SetFont(Panel::TextFont text_font)
{
    _textFont = text_font;
    if(_textFont == TextFont::REGULAR)
    {
        _text.setFont(_fontRegular);
    }
    else if(_textFont == TextFont::BOLD)
    {
        _text.setFont(_fontBold);
    }
}

bool Panel::LoadTextures()
{
    if (!_panelTexture.loadFromFile("Resources/Textures/panel_image1.png"))
    {
        return false;
    }
    return true;
}

void Panel::InitText()
{
    _text.setString("Text");
    _text.setFont(_fontRegular);
    _text.setCharacterSize(40);
    _text.setFillColor(sf::Color::White);
    _text.setOutlineThickness(1);
    _text.setOutlineColor(sf::Color::Black);
    _text.setPosition(400, 400);
}

/// Unnecessary to load fonts which may not even be used
bool Panel::LoadFonts()
{
    if(!_fontRegular.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Regular.ttf"))
    {
        return false;
    }
    if(!_fontBold.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Bold.ttf"))
    {
        return false;
    }
    return true;
}

void Panel::CentreAlignPanelToText()
{
    // Update _panel size before re-centering _text
    auto panel_width = _text.getGlobalBounds().width + _panelWidth * 2;
    auto panel_height = _text.getGlobalBounds().height + _panelHeight;
    _panel.setSize({panel_width, panel_height});

    if(_textAlign == TextAlign::CENTRE)
    {
        auto panel_xpos = _text.getPosition().x - _panelWidth;
        auto panel_ypos = (_text.getGlobalBounds().top + _text.getGlobalBounds().height / 2) - _panel.getGlobalBounds().height / 2;
        _panel.setPosition(panel_xpos, panel_ypos);
    }
    else if(_textAlign == TextAlign::OFFSET)
    {
        auto panel_xpos = _text.getPosition().x - _panelWidth;
        auto panel_ypos = (_text.getPosition().y - _textOffset);
        _panel.setPosition(panel_xpos, panel_ypos);
    }
}

bool Panel::IsHoveredOver() const
{
    return _isHoveredOver;
}

bool Panel::IsClicked() const
{
    return _isClicked;
}

sf::Text& Panel::GetText()
{
    return _text;
}

sf::FloatRect Panel::GetTextSize()
{
    /// Panels adjust to accommodate _text
    return _text.getGlobalBounds();
}

sf::Vector2f Panel::GetTextPosition()
{
    /// Panels follow _text _position
    return _text.getPosition();
}

sf::FloatRect Panel::GetPanelSize()
{
    /// Panels adjust to accommodate _text
    return _panel.getGlobalBounds();
}

sf::Vector2f Panel::GetPanelPosition()
{
    /// Panels follow _text _position
    return _panel.getPosition();
}

/*Button &Panel::getButton()
{
    return button;
}*/



