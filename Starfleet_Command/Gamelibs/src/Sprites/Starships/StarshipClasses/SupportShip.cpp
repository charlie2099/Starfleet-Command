#include "Sprites/Starships/StarshipClasses/SupportShip.hpp"

SupportShip::SupportShip()
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_2.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(300);
    _speed = 70;
    _trainingSpeed = 0.5f;
    _damage = 0;
    _damageScaleFactor = 0.10f;
    _fireRate = 2.0f;
    _attackRange = 400.0F;
    _buildCost = 200;
    _projectileSize = Projectile::SMALL;
    _projectileColour = Projectile::BLUE;
    _shipName = "Support Ship";

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

    _attackRangeCircle.setRadius(_attackRange);
    _attackRangeCircle.setFillColor({253, 103, 100, 50});
    _attackRangeCircle.setOutlineColor(sf::Color(255, 0, 0, 150));
    _attackRangeCircle.setOutlineThickness(2.0F);
    _attackRangeCircle.setOrigin(_attackRangeCircle.getRadius(), _attackRangeCircle.getRadius());
    _attackRangeCircle.setPosition(_spriteComponent.GetPos());
}

void SupportShip::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto worldPositionOfMouse = window.mapPixelToCoords(mouse_pos, window.getView()); // Mouse position translated into world coordinates

    if(Chilli::Vector::BoundsCheck(worldPositionOfMouse, _spriteComponent.GetSprite().getGlobalBounds()))
    {
        _isAttackRangeCircleVisible = true;
    }
    else
    {
        _isAttackRangeCircleVisible = false;
    }
}

void SupportShip::Update(sf::RenderWindow &window, sf::Time deltaTime)
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

    if(_isAttackRangeCircleVisible)
    {
        _attackRangeCircle.setPosition(_spriteComponent.GetPos());
    }
}

void SupportShip::Render(sf::RenderWindow &window)
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

    if(_isAttackRangeCircleVisible)
    {
        window.draw(_attackRangeCircle);
    }
}

void SupportShip::MoveTowards(sf::Vector2f target, sf::Time deltaTime)
{
    auto& ship_sprite = _spriteComponent.GetSprite();

    sf::Vector2f ship_dir = Chilli::Vector::Normalize(target - ship_sprite.getPosition());
    sf::Vector2f ship_move = ship_dir * _speed;
    float ship_rot = atan2(ship_dir.y, ship_dir.x) * 180 / 3.141;

    ship_sprite.move(ship_move * deltaTime.asSeconds());
    ship_sprite.setRotation(ship_rot);
}

void SupportShip::ShootAt(float fireRate, sf::Vector2f target)
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

void SupportShip::SetHealth(float health)
{
    _healthComponent.SetHealth(health);
}

void SupportShip::SetHealthBarVisibility(bool visible)
{
    _healthBarIsVisible = visible;
}

void SupportShip::SetDamage(float damage)
{
    _damage = damage;
}

void SupportShip::SetSpeed(float speed)
{
    _speed = speed;
}

void SupportShip::SetAcceleration(float acceleration)
{
    _acceleration = acceleration;
}

void SupportShip::SetAttackRange(float range)
{
    _attackRange = range;
}

void SupportShip::SetColour(sf::Color &colour)
{
    _spriteComponent.GetSprite().setColor(colour);
    _shipColour = colour;
}

void SupportShip::SetPosition(sf::Vector2f pos)
{
    _spriteComponent.SetPos(pos);
}

void SupportShip::SetRotation(float rot)
{
    _spriteComponent.GetSprite().setRotation(rot);
    _rotation = rot;
}

















