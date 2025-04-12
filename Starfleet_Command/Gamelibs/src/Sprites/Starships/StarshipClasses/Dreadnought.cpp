#include "Sprites/Starships/StarshipClasses/Dreadnought.hpp"

Dreadnought::Dreadnought(int spacelane)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_3.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(1500);
    _speed = 40;
    _startSpeed = _speed;
    _deployTimeSpeed = 10.0F;
    _maximumDamage = 500;
    _damageScaleFactor = 1.0F;
    _fireRate = 3.0f;
    _attackRange = 800.0F;
    _buildCost = 1000;
    _projectileSize = Projectile::LARGE;
    _projectileColour = Projectile::BLUE;
    _starshipName = "Dreadnought";
    _starshipAbbreviation = "DRN";
    _assignedLaneIndex = spacelane;
    _starshipIndex = 3;

    _healthBar = std::make_unique<HealthBar>(_healthComponent, false);
    _healthBar->SetMaxHealth(_healthComponent.GetHealth());
    _maximumHealth = _healthComponent.GetHealth();

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = _spriteComponent.GetSprite().getLocalBounds().width / 2;
    centered_origin.y = _spriteComponent.GetSprite().getLocalBounds().height / 2;
    _spriteComponent.GetSprite().setOrigin(centered_origin);

    //auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    //_healthComponent.AddBasicObserver({HealthComponent::HEALTH_DEPLETED, callbackFnc1}); // NOTE: Or handle in Destructor instead of as an event?

    const int SPACELANE_COUNT = 4;
    int minLane = std::max(0, spacelane-2);
    int maxLane = std::min(SPACELANE_COUNT, spacelane+2);
    for (int i = minLane; i <= maxLane; ++i)
    {
        _attackableLanes.emplace_back(i);
    }
}

void Dreadnought::EventHandler(sf::RenderWindow &window, sf::Event &event)
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

void Dreadnought::Update(sf::RenderWindow &window, sf::Time deltaTime)
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

    if(_healthBar->GetHealth() < _maximumHealth)
    {
        _isHealthBarVisible = true;
    }
}

void Dreadnought::Render(sf::RenderWindow &window)
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

void Dreadnought::Move(float xOffset, float yOffset)
{
    _spriteComponent.Move(xOffset,  yOffset);
}

void Dreadnought::ShootAt(sf::Vector2f target)
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

void Dreadnought::DestroyProjectile(int projectileIndex)
{
    _projectile.erase(_projectile.begin() + projectileIndex);
}

void Dreadnought::TakeDamage(float damageAmount)
{
    _healthComponent.TakeDamage(damageAmount, GetPos());
}

void Dreadnought::ReplenishHealth(float healthAmount)
{
    _healthComponent.ReplenishHealth(_maximumHealth, healthAmount, GetPos());
}

void Dreadnought::SetHealth(float health)
{
    _healthComponent.SetHealth(health);
}

void Dreadnought::SetHealthBarVisibility(bool visible)
{
    _isHealthBarVisible = visible;
}

void Dreadnought::SetDamage(float damage)
{
    _maximumDamage = damage;
}

void Dreadnought::SetSpeed(float speed)
{
    _speed = speed;
}

void Dreadnought::SetAcceleration(float acceleration)
{
    _acceleration = acceleration;
}

void Dreadnought::SetAttackRange(float range)
{
    _attackRange = range;
}

void Dreadnought::SetColour(sf::Color &colour)
{
    _spriteComponent.GetSprite().setColor(colour);
    _starshipColour = colour;
}

void Dreadnought::SetPosition(sf::Vector2f pos)
{
    _spriteComponent.SetPos(pos);
}

void Dreadnought::SetRotation(float rot)
{
    _spriteComponent.GetSprite().setRotation(rot);
    _rotation = rot;
}

bool Dreadnought::IsEnemyInRange(const std::unique_ptr<IStarship> &starship)
{
    return Chilli::Vector::Distance(GetPos(), starship->GetPos()) <= GetAttackRange();
}

bool Dreadnought::IsFriendlyStarshipAhead(const std::unique_ptr<IStarship> &starship)
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

bool Dreadnought::IsEnemyStarshipAhead(const std::unique_ptr<IStarship> &enemyStarship)
{
    return Chilli::Vector::Distance(this->GetPos(), enemyStarship->GetPos()) < 100;
}

bool Dreadnought::CollidesWith(sf::Rect<float> spriteBounds)
{
    return _spriteComponent.GetSprite().getGlobalBounds().intersects(spriteBounds);
}

bool Dreadnought::CanEngageWith(const std::unique_ptr<IStarship> &starship)
{
    if(this->GetLaneIndex() == starship->GetLaneIndex() - 2 or
            this->GetLaneIndex() == starship->GetLaneIndex() - 1 or
            this->GetLaneIndex() == starship->GetLaneIndex() or
            this->GetLaneIndex() == starship->GetLaneIndex() + 1 or
            this->GetLaneIndex() == starship->GetLaneIndex() + 2)
    {
        return true;
    }
    return false;
}

/*void Dreadnought::SetAttackRangeVisibility(bool visibility)
{
    _isAttackRangeCircleVisible = visibility;
}*/



















