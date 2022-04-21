#include "Vector.hpp"

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
