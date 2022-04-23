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
            _damage = 20;
            break;
        case Type::REPAIR:
            spriteComponent.LoadSprite("images/starfleet_ship_repair.png");
            spriteComponent.GetSprite().scale({0.05F, 0.05F});
            _health = 150;
            _speed = 70;
            _damage = 0;
            break;
        case Type::SCOUT:
            spriteComponent.LoadSprite("images/starfleet_ship_scout.png");
            spriteComponent.GetSprite().scale({0.30F, 0.30F});
            _health = 75;
            _speed = 100;
            _damage = 10;
            break;
        case Type::DESTROYER:
            spriteComponent.LoadSprite("images/starfleet_ship_destroyer.png");
            spriteComponent.GetSprite().scale({0.05F, 0.05F});
            _health = 250;
            _speed = 40;
            _damage = 150;
            break;
        case Type::BATTLESHIP:
            spriteComponent.LoadSprite("images/starfleet_ship_battleship.png");
            spriteComponent.GetSprite().scale({0.05F, 0.05F});
            _health = 500;
            _speed = 30;
            _damage = 75;
            break;
        case Type::FLAGSHIP:
            spriteComponent.LoadSprite("images/starfleet_ship_flagship.png");
            spriteComponent.GetSprite().scale({0.08F, 0.08F});
            _health = 5000;
            _speed = 10;
            _damage = 50;
            break;
    }
    //spriteComponent.GetSprite().scale({0.05F, 0.05F});

    _healthBar.emplace_back(HealthBar());
    _healthBar[0].SetMaxHealth(_health); // TODO: This doesn't need to be a vector!

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = spriteComponent.GetSprite().getLocalBounds().width / 2;
    centered_origin.y = spriteComponent.GetSprite().getLocalBounds().height / 2;
    spriteComponent.GetSprite().setOrigin(centered_origin);
}

void Starship::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    for(auto& projectiles : _projectile)
    {
        projectiles->Update(window, deltaTime);
    }

    for(auto& bar : _healthBar)
    {
        bar.Update(window, deltaTime);
        auto ship_bounds = spriteComponent.GetSprite().getGlobalBounds();
        auto bar_bounds = bar.GetSpriteComponent().GetSprite().getGlobalBounds();
        auto xPos = (spriteComponent.GetPos().x) - (ship_bounds.width/2.0f + bar_bounds.width/2.0f);
        auto yPos = (spriteComponent.GetPos().y + ship_bounds.height/2.0f) - (ship_bounds.height + bar_bounds.height*4);
        bar.SetPos({xPos, yPos});
    }
}

void Starship::Render(sf::RenderWindow &window)
{
    for(auto& projectiles : _projectile)
    {
        projectiles->Render(window);
    }

    window.draw(spriteComponent.GetSprite());

    for(auto& health : _healthBar)
    {
        if(_healthBarIsVisible)
        {
            health.Render(window);
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
    return _projectile;
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

void Starship::ShootAt(Projectile::Type projectile, float fireRate, sf::Vector2f target)
{
    sf::Clock clock;
    if(clock.getElapsedTime().asSeconds() <= timePassed)
    {
        auto spawnPos = spriteComponent.GetPos();
        _projectile.emplace_back(std::make_unique<Projectile>(projectile, spawnPos, target));

        timePassed += fireRate;
    }

    //std::cout << "Elapsed Time: " << clock.getElapsedTime().asSeconds() << std::endl;
}

void Starship::SetHealthBarVisibility(bool visible)
{
    _healthBarIsVisible = visible;
}






