#include "Utility/Cursor.hpp"

Chilli::Cursor::Cursor()
{
    for (int i = 0; i < _cursorTextures.size(); ++i)
    {
        _cursorTextures[i].loadFromFile("Resources/Textures/cursor_" + std::to_string(i) + ".png");
    }
    _type = Type::DEFAULT;
   _cursorSprite.setTexture(_cursorTextures[_type]);
   _cursorSprite.scale(0.5F, 0.5F);
}

void Chilli::Cursor::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
//    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
//    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse _position translated into world coordinates
//
//    _cursorSprite.setPosition(mousePosWorldCoords.x - _cursorSprite.getGlobalBounds().width/2,
//                               mousePosWorldCoords.y - _cursorSprite.getGlobalBounds().height/2);
}

void Chilli::Cursor::Render(sf::RenderWindow &window)
{
    window.draw(_cursorSprite);
}

void Chilli::Cursor::SetCursorPos(sf::RenderWindow &window, sf::View& view)
{
    //auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
    //auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos, view); // Mouse _position translated into world coordinates

    sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

    /*_cursorSprite.setPosition(mouse_pos.x - _cursorSprite.getGlobalBounds().width/2,
                               mouse_pos.y - _cursorSprite.getGlobalBounds().height/2);*/

    _cursorSprite.setPosition(mouse_pos.x - 3.0F, mouse_pos.y - 1.0F);
}

void Chilli::Cursor::SetCursorType(Chilli::Cursor::Type type, sf::Color color)
{
    _type = type;
    _cursorSprite.setTexture(_cursorTextures[_type]);
    _cursorSprite.setColor(color);
}


