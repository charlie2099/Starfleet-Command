#ifndef STARFLEET_COMMAND_SUPPORTFRIGATE_HPP
#define STARFLEET_COMMAND_SUPPORTFRIGATE_HPP
#include <SFML/System/Vector2.hpp>
#include "Sprites/UI/HealthBar.hpp"
#include "Utility/Vector.hpp"
#include "Interfaces/IHealer.hpp"

class SupportFrigate : public Starship, public IHealer
{
public:
    explicit SupportFrigate(int spacelane);
    bool CanEngageWith(const std::unique_ptr<Starship> &starship) override;
    void ShootHealAt(const std::unique_ptr<Starship> &friendlyStarship) override;

private:
    sf::Clock _healingProjectileSpawnTimerClock;
    float _healingProjectileSpawnTimer = 0;
};

#endif //STARFLEET_COMMAND_SUPPORTFRIGATE_HPP
