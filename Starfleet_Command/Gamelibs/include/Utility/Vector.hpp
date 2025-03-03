#ifndef STARFLEET_COMMAND_VECTOR_HPP
#define STARFLEET_COMMAND_VECTOR_HPP
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cmath>

namespace Chilli
{
    class Vector
    {
    public:
        static sf::Vector2f Normalize(sf::Vector2f vec);
        static double Distance(sf::Vector2f a, sf::Vector2f b);
        static float DotProduct(sf::Vector2f v1, sf::Vector2f  v2);
        static bool BoundsCheck(sf::Vector2<float> mouse_vec, sf::FloatRect sprite_bounds);
    };
}

#endif //STARFLEET_COMMAND_VECTOR_HPP
