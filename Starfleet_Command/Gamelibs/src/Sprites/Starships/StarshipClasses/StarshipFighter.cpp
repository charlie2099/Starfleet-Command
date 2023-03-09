#include "Sprites/Starships/StarshipClasses/StarshipFighter.hpp"

StarshipFighter::StarshipFighter()
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_fighter.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(100);
    _speed = 80;
    //_trainingSpeed = 0.5f;
    _damage = 20;
   // _damageScaleFactor = 0.25f;
   // _fireRate = 0.25f;
   // _shipCost = 250;
   // _projectileType = Projectile::Type::LASER_RED_REGULAR;


    /*_healthComponent.SetHealth(100);
    _damage = 20;
    _speed = 10;

    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_fighter.png");
    _spriteComponent.GetSprite().setColor(sf::Color::Yellow);
    _spriteComponent.GetSprite().setScale(0.1F, 0.1F);
    _spriteComponent.GetSprite().setPosition(300, 300);*/


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

void StarshipFighter::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    _healthComponent.Update(window, deltaTime);

    auto ship_bounds = _spriteComponent.GetSprite().getGlobalBounds();
    auto bar_bounds = _healthBar->GetSpriteComponent().GetSprite().getGlobalBounds();
    auto xPos = (_spriteComponent.GetPos().x) - (ship_bounds.width/2.0f + bar_bounds.width/2.0f);
    auto yPos = (_spriteComponent.GetPos().y + ship_bounds.height/2.0f) - (ship_bounds.height + bar_bounds.height*4);
    _healthBar->Update(window, deltaTime);
    _healthBar->SetPos({xPos, yPos});

    if(_healthBar->GetHealth() < _maxHealth)
    {
        _healthBarIsVisible = true;
    }
}

void StarshipFighter::Render(sf::RenderWindow &window)
{
    _spriteComponent.Render(window);
    _healthComponent.Render(window);

    if(_healthBarIsVisible)
    {
        _healthBar->Render(window);
    }
}

void StarshipFighter::SetDamage(float damage)
{
    _damage = damage;
}

void StarshipFighter::SetSpeed(float speed)
{
    _speed = speed;
}

void StarshipFighter::SetHealthBarVisibility(bool visible)
{
    _healthBarIsVisible = visible;
}

SpriteComponent &StarshipFighter::GetSpriteComponent()
{
    return _spriteComponent;
}

HealthComponent &StarshipFighter::GetHealthComponent()
{
    return _healthComponent;
}

std::unique_ptr<HealthBar> &StarshipFighter::GetHealthBar()
{
    return _healthBar;
}

const float StarshipFighter::GetSpeed()
{
    return _speed;
}

const float StarshipFighter::GetMaxHealth()
{
    return _maxHealth;
}

bool StarshipFighter::IsHealthBarVisible()
{
    return _healthBarIsVisible;
}









