#ifndef STARFLEET_COMMAND_STARSHIPFIGHTER_HPP
#define STARFLEET_COMMAND_STARSHIPFIGHTER_HPP
#include <SFML/System/Vector2.hpp>
#include "Interfaces/IStarship.hpp"
#include "Sprites/UI/HealthBar.hpp"

class StarshipFighter : public IStarship
{
public:
    StarshipFighter();
    void Update(sf::RenderWindow& window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;

    void SetDamage(float damage) override;
    void SetSpeed(float speed) override;
    void SetHealthBarVisibility(bool visible) override;

    SpriteComponent& GetSpriteComponent() override;
    HealthComponent& GetHealthComponent() override;
    std::unique_ptr<HealthBar>& GetHealthBar();
    const float GetSpeed() override;
    const float GetMaxHealth() override;
    bool IsHealthBarVisible() override;

private:
    std::unique_ptr<HealthBar> _healthBar;
};

#endif //STARFLEET_COMMAND_STARSHIPFIGHTER_HPP
