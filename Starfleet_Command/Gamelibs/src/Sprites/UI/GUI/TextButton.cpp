#include <iostream>
#include "Sprites/UI/GUI/TextButton.hpp"

TextButton::TextButton()
{
    _panelTexture.loadFromFile("Resources/Textures/panel_image1.png");

    _text.setString("Text");
    _text.setFont(Chilli::CustomFonts::GetBoldFont());
    _text.setCharacterSize(14);
    _text.setFillColor(sf::Color::White);
    _text.setOutlineThickness(1);
    _text.setOutlineColor(sf::Color::Black);

    _panel.setTexture(&_panelTexture);
    CentreAlignPanelToText();
}

TextButton::TextButton(const std::string &filepath)
{
    _panelTexture.loadFromFile(filepath);

    _text.setString("");
    _text.setFont(Chilli::CustomFonts::GetBoldFont());
    _text.setCharacterSize(14);
    _text.setFillColor(sf::Color::White);
    _text.setOutlineThickness(1);
    _text.setOutlineColor(sf::Color::Black);

    _panel.setTexture(&_panelTexture);
    CentreAlignPanelToText();
}

void TextButton::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && _isMouseHoveredOver)
    {
        _isClicked = true;
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        _isClicked = false;
    }
}

void TextButton::Update(sf::RenderWindow &window)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _innerPosition relative to the window
    auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse _innerPosition translated into world coordinates

    if(_panel.getGlobalBounds().contains(translated_pos))
    {
        _isMouseHoveredOver = true;
    }
    else
    {
        _isMouseHoveredOver = false;
    }
}

void TextButton::Render(sf::RenderWindow& window)
{
    window.draw(_panel);
    window.draw(_text);
}

void TextButton::SetPanelColour(sf::Color color)
{
    _panel.setFillColor(color);
}

void TextButton::SetPadding(float padding)
{
    _panelWidth = padding;
    _panelHeight = padding;
    CentreAlignPanelToText();
}

void TextButton::SetSize(float width, float height)
{
    _panelWidth = width;
    _panelHeight = height;
    auto panel_width = _text.getGlobalBounds().width + _panelWidth * 2;
    auto panel_height = _text.getGlobalBounds().height + _panelHeight;
    _panel.setSize({panel_width, panel_height});
    CentreAlignPanelToText();
}

void TextButton::SetPosition(float x, float y)
{
    _text.setPosition(x, y);
    CentreAlignPanelToText();
}

void TextButton::SetText(const std::string& text_str)
{
    _text.setString(text_str);
    CentreAlignPanelToText();
}

void TextButton::SetText(const std::string& text_str, sf::Color colour)
{
    _text.setString(text_str);
    _text.setFillColor(colour);
    CentreAlignPanelToText();
}

void TextButton::SetTextSize(int text_size)
{
    _text.setCharacterSize(text_size);
    CentreAlignPanelToText();
}

void TextButton::SetTextOffset(TextAlign alignment, float offset)
{
    _textAlign = alignment;
    _textOffset = offset;
    CentreAlignPanelToText();
}

void TextButton::SetFont(const sf::Font& font)
{
    _text.setFont(font);
}

void TextButton::CentreAlignPanelToText()
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



