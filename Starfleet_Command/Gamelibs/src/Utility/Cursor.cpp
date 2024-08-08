#include "Utility/Cursor.hpp"

Chilli::Cursor::Cursor()
{
    for (int i = 0; i < _cursor_textures.size(); ++i)
    {
        _cursor_textures[i].loadFromFile("Resources/Textures/cursor_" + std::to_string(i) + ".png");
    }
    _type = Type::DEFAULT;
   _cursor_sprite.setTexture(_cursor_textures[_type]);
   _cursor_sprite.scale(0.5F, 0.5F);
}

void Chilli::Cursor::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
//    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
//    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse _position translated into world coordinates
//
//    _cursor_sprite.setPosition(mousePosWorldCoords.x - _cursor_sprite.getGlobalBounds().width/2,
//                               mousePosWorldCoords.y - _cursor_sprite.getGlobalBounds().height/2);
}

void Chilli::Cursor::Render(sf::RenderWindow &window)
{
    window.draw(_cursor_sprite);
}

void Chilli::Cursor::SetCursorPos(sf::RenderWindow &window, sf::View& view)
{
    //auto mouse_pos = sf::Mouse::getPosition(window); // Mouse _position relative to the window
    //auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos, view); // Mouse _position translated into world coordinates

    sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

    /*_cursor_sprite.setPosition(mouse_pos.x - _cursor_sprite.getGlobalBounds().width/2,
                               mouse_pos.y - _cursor_sprite.getGlobalBounds().height/2);*/

    _cursor_sprite.setPosition(mouse_pos.x - 3.0F, mouse_pos.y - 1.0F);
}

void Chilli::Cursor::SetCursorType(Chilli::Cursor::Type type, sf::Color color)
{
    _type = type;
    _cursor_sprite.setTexture(_cursor_textures[_type]);
    _cursor_sprite.setColor(color);
}


