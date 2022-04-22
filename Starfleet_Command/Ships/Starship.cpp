#include "Starship.hpp"

Starship::Starship(Type type) : ship_type(type)
{
    switch(type)
    {
        case Type::FIGHTER:
            spriteComponent.LoadSprite("images/starfleet_ship_fighter.png");
            spriteComponent.GetSprite().scale({0.05F, 0.05F});
            _health = 100;
            _speed = 80;
            break;
        case Type::REPAIR:
            spriteComponent.LoadSprite("images/starfleet_ship_repair.png");
            spriteComponent.GetSprite().scale({0.05F, 0.05F});
            _health = 150;
            _speed = 70;
            break;
        case Type::SCOUT:
            spriteComponent.LoadSprite("images/starfleet_ship_scout.png");
            spriteComponent.GetSprite().scale({0.30F, 0.30F});
            _health = 75;
            _speed = 100;
            break;
        case Type::DESTROYER:
            spriteComponent.LoadSprite("images/starfleet_ship_destroyer.png");
            spriteComponent.GetSprite().scale({0.05F, 0.05F});
            _health = 250;
            _speed = 40;
            break;
        case Type::BATTLESHIP:
            spriteComponent.LoadSprite("images/starfleet_ship_battleship.png");
            spriteComponent.GetSprite().scale({0.05F, 0.05F});
            _health = 500;
            _speed = 30;
            break;
        case Type::FLAGSHIP:
            spriteComponent.LoadSprite("images/starfleet_ship_flagship.png");
            spriteComponent.GetSprite().scale({0.10F, 0.10F});
            _health = 5000;
            _speed = 10;
            break;
    }
    //spriteComponent.GetSprite().scale({0.05F, 0.05F});

    _healthBar.emplace_back(HealthBar());
    _healthBar[0].SetMaxHealth(_health);

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = spriteComponent.GetSprite().getLocalBounds().width / 2;
    centered_origin.y = spriteComponent.GetSprite().getLocalBounds().height / 2;
    spriteComponent.GetSprite().setOrigin(centered_origin);
}

void Starship::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    if(_healthBar[0].GetHealth() <= 0)
    {
        _isDead = true;
    }

    if(!_isDead)
    {
        for(auto& bar : _healthBar)
        {
            bar.Update(window, deltaTime);
            auto ship_bounds = spriteComponent.GetSprite().getGlobalBounds();
            auto bar_bounds = bar.GetSpriteComponent().GetSprite().getGlobalBounds();
            auto xPos = (spriteComponent.GetPos().x) - (ship_bounds.width/2.0f + bar_bounds.width/2.0f);
            auto yPos = (spriteComponent.GetPos().y + ship_bounds.height/2.0f) - (ship_bounds.height + bar_bounds.height*4);
            bar.SetPos({xPos, yPos});
        }

        if(_healthBar[0].GetHealth() <= 0)
        {

        }
    }
}

void Starship::Render(sf::RenderWindow &window)
{
    if(!_isDead)
    {
        window.draw(spriteComponent.GetSprite());
        for(auto& health : _healthBar)
        {
            if(_healthBarIsVisible)
            {
                health.Render(window);
            }
        }
    }
}

void Starship::SetHealth(float health)
{
    _health = health;
}

void Starship::SetDamage(float damage)
{
    _damage = damage;
}

void Starship::SetSpeed(float speed)
{
    _speed = speed;
}

void Starship::SetAcceleration(float acceleration)
{
    _acceleration = acceleration;
}

float Starship::GetHealth() const
{
    return _health;
}

float Starship::GetDamage() const
{
    return _damage;
}

float Starship::GetSpeed() const
{
    return _speed;
}

float Starship::GetAcceleration() const
{
    return _acceleration;
}

SpriteComponent &Starship::GetSpriteComponent()
{
    return spriteComponent;
}

std::vector<std::unique_ptr<Projectile>>& Starship::GetProjectile()
{
    return projectile;
}

void Starship::MoveTowards(sf::Vector2f target, sf::Time deltaTime)
{
    auto& ship_sprite = spriteComponent.GetSprite();

    sf::Vector2f ship_dir = Chilli::Vector::Normalize(target - ship_sprite.getPosition());
    sf::Vector2f ship_move = ship_dir * _speed;
    float ship_rot = atan2(ship_dir.y, ship_dir.x) * 180 / 3.141;

    ship_sprite.move(ship_move * deltaTime.asSeconds());
    ship_sprite.setRotation(ship_rot);
}

void Starship::SetHealthBarVisibility(bool visible)
{
    _healthBarIsVisible = visible;
}





