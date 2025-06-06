#include "Utility/Vector.hpp"

sf::Vector2f Chilli::Vector::Normalize(sf::Vector2f vec)
{
    float magnitude = sqrtf(vec.x * vec.x + vec.y * vec.y);
    if (magnitude != 0) {
        vec.x /= magnitude;
        vec.y /= magnitude;
    }
    return vec;
}

double Chilli::Vector::Distance(sf::Vector2f a, sf::Vector2f b)
{
    return std::sqrt((a.x - b.x) * (a.x - b.x)  + (a.y - b.y) * (a.y - b.y));
}

bool Chilli::Vector::BoundsCheck(sf::Vector2<float> mouse_vec, sf::FloatRect sprite_bounds)
{
    return (mouse_vec.x > sprite_bounds.left and
    mouse_vec.y > sprite_bounds.top and
    mouse_vec.x < sprite_bounds.left + sprite_bounds.width and
    mouse_vec.y < sprite_bounds.top + sprite_bounds.height);
}

float Chilli::Vector::DotProduct(sf::Vector2f v1, sf::Vector2f v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}
