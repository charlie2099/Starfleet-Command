#ifndef STARFLEET_COMMAND_STARSHIP_HPP
#define STARFLEET_COMMAND_STARSHIP_HPP
#include "../SpriteComponent.hpp"

class Starship
{
 public:
    Starship() = default;
    ~Starship() = default;

    /// General
    virtual void render(sf::RenderWindow& window);

    /// Mutators
    void setHealth(float health);
    void setDamage(float damage);
    void setSpeed(float speed);
    void setAcceleration(float acceleration);

    /// Accessors
    float getHealth() const;
    float getDamage() const;
    float getSpeed() const;
    float getAcceleration() const;

 private:
    //SpriteComponent spriteComponent;

    float health_ = 0.0F;
    float damage_ = 0.0F;
    float speed_ = 0.0F;
    float acceleration_ = 0.0F;
};

#endif //STARFLEET_COMMAND_STARSHIP_HPP
