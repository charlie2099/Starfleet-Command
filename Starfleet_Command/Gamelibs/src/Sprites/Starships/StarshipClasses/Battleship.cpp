#include "Sprites/Starships/StarshipClasses/Battleship.hpp"

Battleship::Battleship()
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_battleship.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(500);
    _speed = 30;
    _trainingSpeed = 0.8f;
    _damage = 75;
    _damageScaleFactor = 0.75f;
    _fireRate = 3.0f;
    _shipCost = 750;
    _projectileType = Projectile::Type::LASER_BLUE_LARGE;

    _healthBar = std::make_unique<HealthBar>(_healthComponent);
    _healthBar->SetMaxHealth(_healthComponent.GetHealth());
    _maxHealth = _healthComponent.GetHealth();

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = _spriteComponent.GetSprite().getLocalBounds().width / 2;
    centered_origin.y = _spriteComponent.GetSprite().getLocalBounds().height / 2;
    _spriteComponent.GetSprite().setOrigin(centered_origin);

    //auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    //_healthComponent.AddBasicObserver({HealthComponent::HEALTH_DEPLETED, callbackFnc1});
}

void Battleship::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    for(auto& projectiles : _projectile)
    {
        projectiles->Update(window, deltaTime);
    }

    _healthComponent.Update(window, deltaTime);

    auto ship_bounds = _spriteComponent.GetSprite().getGlobalBounds();
    auto bar_bounds = _healthBar->GetSpriteComponent().GetSprite().getGlobalBounds();
    auto xPos = (_spriteComponent.GetPos().x) - (ship_bounds.width/2.0f + bar_bounds.width/2.0f);
    auto yPos = (_spriteComponent.GetPos().y + ship_bounds.height/2.0f) - (ship_bounds.height + bar_bounds.height*4);
    _healthBar->Update(window, deltaTime);
    _healthBar->SetPos({xPos, yPos});

    if(_healthBar->GetHealth() < _maxHealth/* && _healthBar->GetHealth() > 0*/)
    {
        _healthBarIsVisible = true;
    }
    /* else if(_healthBar->GetHealth() <= 0)
     {
         _healthBarIsVisible = false;
     }*/
}

void Battleship::Render(sf::RenderWindow &window)
{
    for(auto& projectiles : _projectile)
    {
        projectiles->Render(window);
    }

    _spriteComponent.Render(window);
    _healthComponent.Render(window);

    if(_healthBarIsVisible)
    {
        _healthBar->Render(window);
    }
}

void Battleship::MoveTowards(sf::Vector2f target, sf::Time deltaTime)
{
    auto& ship_sprite = _spriteComponent.GetSprite();

    sf::Vector2f ship_dir = Chilli::Vector::Normalize(target - ship_sprite.getPosition());
    sf::Vector2f ship_move = ship_dir * _speed;
    float ship_rot = atan2(ship_dir.y, ship_dir.x) * 180 / 3.141;

    ship_sprite.move(ship_move * deltaTime.asSeconds());
    ship_sprite.setRotation(ship_rot);
}

void Battleship::ShootAt(Projectile::Type projectile, float fireRate, sf::Vector2f target)
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
}

void Battleship::SetHealth(float health)
{
    _healthComponent.SetHealth(health);
}

void Battleship::SetHealthBarVisibility(bool visible)
{
    _healthBarIsVisible = visible;
}

void Battleship::SetDamage(float damage)
{
    _damage = damage;
}

void Battleship::SetSpeed(float speed)
{
    _speed = speed;
}

void Battleship::SetAcceleration(float acceleration)
{
    _acceleration = acceleration;
}

