#ifndef STARFLEET_COMMAND_STARSHIP_HPP
#define STARFLEET_COMMAND_STARSHIP_HPP
#include "../Components/SpriteComponent.hpp"
#include "Projectile.hpp"

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

    /// General
    virtual void render(sf::RenderWindow& window);

    /// Modifiers
    void setHealth(float health);
    void setDamage(float damage);
    void setSpeed(float speed); // Entity class?
    void setAcceleration(float acceleration);

    /// Accessors
    SpriteComponent &getSpriteComponent();
    std::vector<std::unique_ptr<Projectile>>& getProjectile();
    float getHealth() const;
    float getDamage() const;
    float getSpeed() const;
    float getAcceleration() const;

 private:
    SpriteComponent spriteComponent;
    std::vector<std::unique_ptr<Projectile>> projectile{};
    Type ship_type{};
    float health_ = 0.0F;
    float damage_ = 0.0F;
    float speed_ = 0.0F;
    float acceleration_ = 0.0F;
};

#endif //STARFLEET_COMMAND_STARSHIP_HPP
