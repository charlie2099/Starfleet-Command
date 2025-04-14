#include "Sprites/Starships/StarshipClasses/LightFighter.hpp"

LightFighter::LightFighter(int spacelane)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_0.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(150);
    _speed = 160;
    _startSpeed = _speed;
    _deployTimeSpeed = 2.0F;
    _maximumDamage = 25;
    _damageScaleFactor = 1.0F;
    _fireRate = 0.5f;
    _attackRange = 400.0F;
    _buildCost = 50;
    _projectileSize = Projectile::SMALL;
    _projectileColour = Projectile::BLUE;
    _starshipName = "Light Fighter";
    _starshipAbbreviation = "LF";
    _assignedLaneIndex = spacelane;
    _starshipIndex = 0;

    _healthBar = std::make_unique<HealthBar>(_healthComponent, false);
    _healthBar->SetMaxHealth(_healthComponent.GetHealth());
    _maximumHealth = _healthComponent.GetHealth();

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = _spriteComponent.GetSprite().getLocalBounds().width / 2;
    centered_origin.y = _spriteComponent.GetSprite().getLocalBounds().height / 2;
    _spriteComponent.GetSprite().setOrigin(centered_origin);

    //auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    //_healthComponent.AddBasicObserver({HealthComponent::HEALTH_DEPLETED, callbackFnc1});

    _attackableLanes.emplace_back(spacelane);
}

void LightFighter::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto worldPositionOfMouse = window.mapPixelToCoords(mouse_pos, window.getView()); // Mouse position translated into world coordinates

    if(Chilli::Vector::BoundsCheck(worldPositionOfMouse, _spriteComponent.GetSprite().getGlobalBounds()))
    {
        //_isAttackRangeCircleVisible = true;
        _isMouseOver = true;
    }
    else
    {
        //_isAttackRangeCircleVisible = false;
        _isMouseOver = false;
    }
}

void LightFighter::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    for(auto& projectiles : _projectile)
    {
        projectiles->Update(window, deltaTime);
    }

    for (int i = 0; i < _projectile.size(); ++i)
    {
        if(Chilli::Vector::Distance(GetPos(), _projectile[i]->GetPos()) > Constants::WINDOW_WIDTH)
        {
            _projectile.erase(_projectile.begin() + i);
        }
    }

    _healthComponent.Update(window, deltaTime);

    auto ship_bounds = _spriteComponent.GetSprite().getGlobalBounds();
    auto bar_bounds = _healthBar->GetSpriteComponent().GetSprite().getGlobalBounds();
    auto xPos = (_spriteComponent.GetPos().x) - (ship_bounds.width/2.0f + bar_bounds.width/2.0f);
    auto yPos = (_spriteComponent.GetPos().y + ship_bounds.height/2.0f) - (ship_bounds.height + bar_bounds.height*4);
    _healthBar->Update(window, deltaTime);
    _healthBar->SetPos({xPos, yPos});

    if(_healthBar->GetHealth() < _maximumHealth/* and _healthBar->GetHealth() > 0*/)
    {
        _isHealthBarVisible = true;
    }
}

void LightFighter::Render(sf::RenderWindow &window)
{
    for(auto& projectiles : _projectile)
    {
        projectiles->Render(window);
    }

    _spriteComponent.Render(window);
    _healthComponent.Render(window);

    if(_isHealthBarVisible)
    {
        _healthBar->Render(window);
    }
}

void LightFighter::Move(float xOffset, float yOffset)
{
    _spriteComponent.Move(xOffset,  yOffset);
}

void LightFighter::ShootAt(sf::Vector2f target)
{
    if(_damagingProjectileSpawnTimer < _damagingProjectileSpawnTimerClock.getElapsedTime().asSeconds())
    {
        _damagingProjectileSpawnTimer = _damagingProjectileSpawnTimerClock.getElapsedTime().asSeconds();
    }

    if(_damagingProjectileSpawnTimerClock.getElapsedTime().asSeconds() >= _damagingProjectileSpawnTimer)
    {
        auto spawnPos = _spriteComponent.GetPos();
        _projectile.emplace_back(std::make_unique<Projectile>(_projectileSize, _projectileColour, spawnPos, target));

        _damagingProjectileSpawnTimer += _fireRate;
    }
}

void LightFighter::DestroyProjectile(int projectileIndex)
{
    _projectile.erase(_projectile.begin() + projectileIndex);
}

void LightFighter::TakeDamage(float damageAmount)
{
    _healthComponent.TakeDamage(damageAmount, GetPos());
}

void LightFighter::ReplenishHealth(float healthAmount)
{
    _healthComponent.ReplenishHealth(_maximumHealth, healthAmount, GetPos());
}

void LightFighter::SetHealth(float health)
{
    _healthComponent.SetHealth(health);
}

void LightFighter::SetHealthBarVisibility(bool visible)
{
    _isHealthBarVisible = visible;
}

void LightFighter::SetDamage(float damage)
{
    _maximumDamage = damage;
}

void LightFighter::SetSpeed(float speed)
{
    _speed = speed;
}

void LightFighter::SetAcceleration(float acceleration)
{
    _acceleration = acceleration;
}

void LightFighter::SetAttackRange(float range)
{
    _attackRange = range;
}

void LightFighter::SetColour(sf::Color &colour)
{
    _spriteComponent.GetSprite().setColor(colour);
    _starshipColour = colour;
}

void LightFighter::SetPosition(sf::Vector2f pos)
{
    _spriteComponent.SetPos(pos);
}

void LightFighter::SetRotation(float rot)
{
    _spriteComponent.GetSprite().setRotation(rot);
    _rotation = rot;
}

bool LightFighter::IsEnemyInRange(const std::unique_ptr<IStarship> &starship)
{
    return Chilli::Vector::Distance(GetPos(), starship->GetPos()) <= GetAttackRange();
}

bool LightFighter::IsFriendlyStarshipAhead(const std::unique_ptr<IStarship> &starship)
{
    bool isAhead;

    if(starship->GetRotation() == 180) // Starships traveling left
    {
        isAhead = starship->GetPos().x < this->GetPos().x;
    }
    else // Starships traveling right
    {
        isAhead = starship->GetPos().x > this->GetPos().x;
    }

    float distance = std::abs(starship->GetPos().x - this->GetPos().x);
    return isAhead and distance < 100.0F;
}

bool LightFighter::IsEnemyStarshipAhead(const std::unique_ptr<IStarship> &enemyStarship)
{
    return Chilli::Vector::Distance(this->GetPos(), enemyStarship->GetPos()) < 100;
}

bool LightFighter::CollidesWith(sf::Rect<float> spriteBounds)
{
    return _spriteComponent.GetSprite().getGlobalBounds().intersects(spriteBounds);
}

bool LightFighter::CanEngageWith(const std::unique_ptr<IStarship> &starship)
{
    return this->GetLaneIndex() == starship->GetLaneIndex();
}

