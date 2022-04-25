#include "Cursor.hpp"

Chilli::Cursor::Cursor()
{
    for (int i = 0; i < _cursor_textures.size(); ++i)
    {
        _cursor_textures[i].loadFromFile("images/crosshair" + std::to_string(i) + ".png");
    }
    _type = Type::DEFAULT;
   _cursor_sprite.setTexture(_cursor_textures[_type]);
   _cursor_sprite.scale(0.15F, 0.15F);
}

void Chilli::Cursor::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
//    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
//    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
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
    //auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    //auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos, view); // Mouse position translated into world coordinates

    sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

    _cursor_sprite.setPosition(mouse_pos.x - _cursor_sprite.getGlobalBounds().width/2,
                               mouse_pos.y - _cursor_sprite.getGlobalBounds().height/2);
}

void Chilli::Cursor::SetCursorType(Chilli::Cursor::Type type, sf::Color color)
{
    _type = type;
    _cursor_sprite.setTexture(_cursor_textures[_type]);
    _cursor_sprite.setColor(color);
}


