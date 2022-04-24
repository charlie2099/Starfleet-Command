#include "Starship.hpp"

Starship::Starship(Type type) : ship_type(type)
{
    switch(type)
    {
        case Type::FIGHTER:
            _spriteComponent.LoadSprite("images/starfleet_ship_fighter.png");
            _spriteComponent.GetSprite().scale({0.05F, 0.05F});
            _health = 100;
            _speed = 80;
            _damage = 20;
            _fireRate = 0.25f;
            _projectileType = Projectile::Type::LASER_BLUE_REGULAR;
            break;
        case Type::REPAIR:
            _spriteComponent.LoadSprite("images/starfleet_ship_repair.png");
            _spriteComponent.GetSprite().scale({0.05F, 0.05F});
            _health = 150;
            _speed = 70;
            _damage = 0;
            _fireRate = 2.0f;
            _projectileType = Projectile::Type::LASER_BLUE_SMALL;
            break;
        case Type::SCOUT:
            _spriteComponent.LoadSprite("images/starfleet_ship_scout.png");
            _spriteComponent.GetSprite().scale({0.30F, 0.30F});
            _health = 75;
            _speed = 100;
            _damage = 10;
            _fireRate = 1.0f;
            _projectileType = Projectile::Type::LASER_BLUE_SMALL;
            break;
        case Type::DESTROYER:
            _spriteComponent.LoadSprite("images/starfleet_ship_destroyer.png");
            _spriteComponent.GetSprite().scale({0.05F, 0.05F});
            _health = 250;
            _speed = 40;
            _damage = 150;
            _fireRate = 3.0f;
            _projectileType = Projectile::Type::LASER_BLUE_LARGE;
            break;
        case Type::BATTLESHIP:
            _spriteComponent.LoadSprite("images/starfleet_ship_battleship.png");
            _spriteComponent.GetSprite().scale({0.05F, 0.05F});
            _health = 500;
            _speed = 30;
            _damage = 75;
            _fireRate = 3.0f;
            _projectileType = Projectile::Type::LASER_BLUE_LARGE;
            break;
        case Type::FLAGSHIP:
            _spriteComponent.LoadSprite("images/starfleet_ship_flagship.png");
            _spriteComponent.GetSprite().scale({0.08F, 0.08F});
            _health = 5000;
            _speed = 10;
            _damage = 50;
            _fireRate = 1.0f;
            _projectileType = Projectile::Type::LASER_BLUE_LARGE;
            break;
    }

    _healthBar.SetMaxHealth(_health);
    _maxHealth = _health;

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = _spriteComponent.GetSprite().getLocalBounds().width / 2;
    centered_origin.y = _spriteComponent.GetSprite().getLocalBounds().height / 2;
    _spriteComponent.GetSprite().setOrigin(centered_origin);
}

void Starship::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    for(auto& projectiles : _projectile)
    {
        projectiles->Update(window, deltaTime);
    }

    _healthBar.Update(window, deltaTime);
    auto ship_bounds = _spriteComponent.GetSprite().getGlobalBounds();
    auto bar_bounds = _healthBar.GetSpriteComponent().GetSprite().getGlobalBounds();
    auto xPos = (_spriteComponent.GetPos().x) - (ship_bounds.width/2.0f + bar_bounds.width/2.0f);
    auto yPos = (_spriteComponent.GetPos().y + ship_bounds.height/2.0f) - (ship_bounds.height + bar_bounds.height*4);
    _healthBar.SetPos({xPos, yPos});

    if(_healthBar.GetHealth() < _maxHealth)
    {
        _healthBarIsVisible = true;
    }
}

void Starship::Render(sf::RenderWindow &window)
{
    for(auto& projectiles : _projectile)
    {
        projectiles->Render(window);
    }

    window.draw(_spriteComponent.GetSprite());

    if(_healthBarIsVisible)
    {
        _healthBar.Render(window);
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

void Starship::SetHealthBarVisibility(bool visible)
{
    _healthBarIsVisible = visible;
}

void Starship::MoveTowards(sf::Vector2f target, sf::Time deltaTime)
{
    auto& ship_sprite = _spriteComponent.GetSprite();

    sf::Vector2f ship_dir = Chilli::Vector::Normalize(target - ship_sprite.getPosition());
    sf::Vector2f ship_move = ship_dir * _speed;
    float ship_rot = atan2(ship_dir.y, ship_dir.x) * 180 / 3.141;

    ship_sprite.move(ship_move * deltaTime.asSeconds());
    ship_sprite.setRotation(ship_rot);
}

void Starship::ShootAt(Projectile::Type projectile, float fireRate, sf::Vector2f target)
{
    if(timePassed < clock.getElapsedTime().asSeconds())
    {
        timePassed = clock.getElapsedTime().asSeconds();
    }

    if(clock.getElapsedTime().asSeconds() >= timePassed)
    {
        auto spawnPos = _spriteComponent.GetPos();
        _projectile.emplace_back(std::make_unique<Projectile>(projectile, spawnPos, target));

        timePassed += fireRate;
    }

    //std::cout << "Projectiles: " << _projectile.size() << std::endl;
    //std::cout << "Elapsed Time: " << clock.getElapsedTime().asSeconds() << std::endl;
}







