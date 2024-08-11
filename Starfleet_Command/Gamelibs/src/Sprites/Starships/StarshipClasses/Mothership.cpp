#include "Sprites/Starships/StarshipClasses/Mothership.hpp"

Mothership::Mothership()
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_5.png");
    _spriteComponent.GetSprite().scale({0.08F, 0.08F});
    _healthComponent.SetHealth(5000);
    _speed = 10;
    _damage = 50;
    _fireRate = 1.0f;
    _attackRange = 400.0F;
    _projectileSize = Projectile::LARGE;
    _projectileColour = Projectile::BLUE;
    _shipName = "Mothership";

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

void Mothership::Update(sf::RenderWindow &window, sf::Time deltaTime)
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

void Mothership::Render(sf::RenderWindow &window)
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

void Mothership::MoveTowards(sf::Vector2f target, sf::Time deltaTime)
{
    auto& ship_sprite = _spriteComponent.GetSprite();

    sf::Vector2f ship_dir = Chilli::Vector::Normalize(target - ship_sprite.getPosition());
    sf::Vector2f ship_move = ship_dir * _speed;
    float ship_rot = atan2(ship_dir.y, ship_dir.x) * 180 / 3.141;

    ship_sprite.move(ship_move * deltaTime.asSeconds());
    ship_sprite.setRotation(ship_rot);
}

void Mothership::ShootAt(float fireRate, sf::Vector2f target)
{
    if(_nextFireTime < _clock.getElapsedTime().asSeconds())
    {
        _nextFireTime = _clock.getElapsedTime().asSeconds();
    }

    if(_clock.getElapsedTime().asSeconds() >= _nextFireTime)
    {
        auto spawnPos = _spriteComponent.GetPos();
        _projectile.emplace_back(std::make_unique<Projectile>(_projectileSize, _projectileColour, spawnPos, target));

        _nextFireTime += fireRate;
    }
}

void Mothership::SetHealth(float health)
{
    _healthComponent.SetHealth(health);
}

void Mothership::SetHealthBarVisibility(bool visible)
{
    _healthBarIsVisible = visible;
}

void Mothership::SetDamage(float damage)
{
    _damage = damage;
}

void Mothership::SetSpeed(float speed)
{
    _speed = speed;
}

void Mothership::SetAcceleration(float acceleration)
{
    _acceleration = acceleration;
}

void Mothership::SetAttackRange(float range)
{
    _attackRange = range;
}

void Mothership::SetColour(sf::Color &colour)
{
    _spriteComponent.GetSprite().setColor(colour);
    _shipColour = colour;
}

void Mothership::SetPosition(sf::Vector2f pos)
{
    _spriteComponent.SetPos(pos);
}

void Mothership::SetRotation(float rot)
{
    _spriteComponent.GetSprite().setRotation(rot);
    _rotation = rot;
}



