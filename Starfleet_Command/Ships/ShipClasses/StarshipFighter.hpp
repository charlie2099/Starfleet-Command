#ifndef STARFLEET_COMMAND_STARSHIPFIGHTER_HPP
#define STARFLEET_COMMAND_STARSHIPFIGHTER_HPP
#include <SFML/System/Vector2.hpp>
#include "../../Interfaces/IStarship.hpp"

class StarshipFighter : public IStarship
{
public:
    StarshipFighter();
    void Update(sf::RenderWindow& window, sf::Time time) override;
    void Render(sf::RenderWindow& window) override;

    void SetDamage(float damage) override;
    void SetSpeed(float speed) override;

    SpriteComponent& GetSpriteComponent() override;
    HealthComponent& GetHealthComponent() override;
    MovementComponent& GetMovementComponent() override;
    AnimationComponent& GetAnimationComponent() override;
    AudioComponent& GetAudioComponent() override;
    const float GetSpeed() override;
};

#endif //STARFLEET_COMMAND_STARSHIPFIGHTER_HPP
