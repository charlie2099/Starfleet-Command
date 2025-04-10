#ifndef STARFLEET_COMMAND_CURSOR_HPP
#define STARFLEET_COMMAND_CURSOR_HPP
#include <array>
#include <SFML/Graphics.hpp>

namespace Chilli
{
    class Cursor
    {
    public:
        enum Type
        {
            DEFAULT = 0,
            SELECTED = 1,
            /*LOCK_ON,*/
            ENUM_LENGTH = 2
        };

    public:
        Cursor();
        ~Cursor() = default;
        void Update(sf::RenderWindow &window, sf::Time deltaTime);
        void Render(sf::RenderWindow& window);

        void SetCursorPos(sf::RenderWindow &window, sf::View& view);
        void SetCursorType(Type type, sf::Color color);

    private:
        std::array<sf::Texture, Type::ENUM_LENGTH> _cursorTextures;
        sf::Sprite _cursorSprite;
        Type _type;
        //int count = Enum.GetValues( typeof( ContentAlignment ) ).Length;
    };
}

#endif //STARFLEET_COMMAND_CURSOR_HPP
