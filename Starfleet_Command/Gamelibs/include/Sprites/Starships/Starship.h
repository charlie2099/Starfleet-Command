#ifndef STARFLEET_COMMAND_STARSHIP_H
#define STARFLEET_COMMAND_STARSHIP_H
#include "Components/SpriteComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "StarshipClass.hpp"

class Starship
{
public:
    explicit Starship(std::unique_ptr<StarshipClass>& starshipClass);
    void Render(sf::RenderWindow& window);

    // AddBehaviour()
    std::unique_ptr<StarshipClass>& GetStarshipClass() { return _starshipClass; };
    SpriteComponent& GetSpriteComponent() { return _spriteComponent; };
    int GetHealth() const { return _healthComponent.GetHealth(); };
    int GetDamage() const { return _damage; };

private:
    std::unique_ptr<StarshipClass> _starshipClass;
    HealthComponent _healthComponent;
    SpriteComponent _spriteComponent;
    int _damage;
};

#endif //STARFLEET_COMMAND_STARSHIP_H
