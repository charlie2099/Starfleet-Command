#ifndef STARFLEET_COMMAND_STARSHIP_HPP
#define STARFLEET_COMMAND_STARSHIP_HPP
#include "../Components/SpriteComponent.hpp"
#include "Projectile.hpp"
#include "../Utility/Vector.hpp"

class Starship
{
 public:
    enum class Type
    {
        FIGHTER,
        REPAIR,
        DESTROYER,
        BATTLESHIP,
        FLAGSHIP
    };
    explicit Starship(Type type);
    ~Starship() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    // Functionality
    void MoveTowards(sf::Vector2f target, sf::Time deltaTime);

    /// Modifiers
    void SetHealth(float health);
    void SetDamage(float damage);
    void SetSpeed(float speed); // Entity class?
    void SetAcceleration(float acceleration);

    /// Accessors
    SpriteComponent &GetSpriteComponent();
    std::vector<std::unique_ptr<Projectile>>& GetProjectile();
    float GetHealth() const;
    float GetDamage() const;
    float GetSpeed() const;
    float GetAcceleration() const;

 private:
    SpriteComponent spriteComponent;
    std::vector<std::unique_ptr<Projectile>> projectile{};
    Type ship_type{};
    float health_ = 0.0F;
    float damage_ = 0.0F;
    float _speed = 0.0F;
    float acceleration_ = 0.0F;
};

#endif //STARFLEET_COMMAND_STARSHIP_HPP
