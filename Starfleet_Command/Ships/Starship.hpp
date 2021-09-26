#ifndef STARFLEET_COMMAND_STARSHIP_HPP
#define STARFLEET_COMMAND_STARSHIP_HPP
#include "../Components/SpriteComponent.hpp"

class Starship
{
 public:
    ~Starship() = default;

    enum class Type
    {
        FIGHTER,
        REPAIR,
        DESTROYER,
        BATTLESHIP,
        FLAGSHIP
    };
    explicit Starship(Type type);

    /// General
    virtual void render(sf::RenderWindow& window);

    /// Modifiers
    void setHealth(float health);
    void setDamage(float damage);
    void setSpeed(float speed); // Entity class?
    void setAcceleration(float acceleration);

    /// Accessors
    SpriteComponent &getSpriteComponent();
    float getHealth() const;
    float getDamage() const;
    float getSpeed() const;
    float getAcceleration() const;

 private:
    SpriteComponent spriteComponent;
    Type ship_type{};
    float health_ = 0.0F;
    float damage_ = 0.0F;
    float speed_ = 0.0F;
    float acceleration_ = 0.0F;
};

#endif //STARFLEET_COMMAND_STARSHIP_HPP
