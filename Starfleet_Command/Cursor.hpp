#ifndef STARFLEET_COMMAND_CURSOR_HPP
#define STARFLEET_COMMAND_CURSOR_HPP
#include <SFML/Graphics.hpp>

namespace Chilli
{
    class Cursor
    {
    public:
        enum Type
        {
            DEFAULT,
            SELECTED,
            LOCK_ON,
            ENUM_LENGTH
        };

    public:
        Cursor();
        ~Cursor() = default;
        void Update(sf::RenderWindow &window, sf::Time deltaTime);
        void Render(sf::RenderWindow& window);

        void SetCursorType(Type type, sf::Color color);

    private:
        std::array<sf::Texture, Type::ENUM_LENGTH> _cursor_textures;
        sf::Sprite _cursor_sprite;
        Type _type;
        //int count = Enum.GetValues( typeof( ContentAlignment ) ).Length;
    };
}

#endif //STARFLEET_COMMAND_CURSOR_HPP
