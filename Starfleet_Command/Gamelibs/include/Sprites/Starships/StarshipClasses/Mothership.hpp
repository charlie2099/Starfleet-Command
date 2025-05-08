#ifndef STARFLEET_COMMAND_MOTHERSHIP_HPP
#define STARFLEET_COMMAND_MOTHERSHIP_HPP
#include <SFML/System/Vector2.hpp>
#include "Sprites/Starships/Starship.hpp"
#include "Sprites/UI/HealthBar.hpp"

class Mothership : public Starship
{
public:
    explicit Mothership(int spacelane);
    void Update(sf::RenderWindow& window, sf::Time deltaTime) override;
    bool CanEngageWith(const std::unique_ptr<Starship> &starship) override;
    void TakeDamage(float damageAmount) override;
    void SetDamageLocation(sf::Vector2<float> location) { _damageLocation = location; }; /// Make this a virtual method in Starship?

private:
    sf::Vector2<float> _damageLocation;
    bool _isDamaged = false;
    float _damageTimer = 0.0F;
};

#endif //STARFLEET_COMMAND_MOTHERSHIP_HPP
