#ifndef STARFLEET_COMMAND_SUPPORTFRIGATE_HPP
#define STARFLEET_COMMAND_SUPPORTFRIGATE_HPP
#include <SFML/System/Vector2.hpp>
#include "Sprites/UI/HealthBar.hpp"
#include "Utility/Vector.hpp"
#include "Interfaces/IHealer.hpp"

class SupportFrigate : public Starship, public IHealer
{
public:
    explicit SupportFrigate(int spawnSpacelane, const std::string& starshipTypeName);
    void ShootHealAt(const std::unique_ptr<Starship> &friendlyStarship) override;
    int GetMaxHeal() const { return _maxHealAmount; }

private:
    sf::Clock _healingProjectileSpawnTimerClock;
    float _healingProjectileSpawnTimer = 0;
    int _maxHealAmount = 100;
};

#endif //STARFLEET_COMMAND_SUPPORTFRIGATE_HPP
