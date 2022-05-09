#include "Sprites/Starships/StarshipClass.hpp"

#include <utility>

StarshipClass::StarshipClass(std::string texturePath, int health, int damage, std::unique_ptr<IBehaviour> behaviour)
: _texturePath(std::move(texturePath)), _maxHealth(health), _damage(damage)
{
    _behaviours.emplace_back(std::move(behaviour));
}
