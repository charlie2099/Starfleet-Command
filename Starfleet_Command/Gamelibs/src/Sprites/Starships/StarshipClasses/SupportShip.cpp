#include "Sprites/Starships/StarshipClasses/SupportShip.hpp"

SupportShip::SupportShip(int spacelane)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_2.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(500);
    _speed = 70;
    _startSpeed = _speed;
    _deployTimeSpeed = 3.0F;
    _damage = 0;
    _damageScaleFactor = 0.10f;
    _fireRate = 2.0f;
    _attackRange = 400.0F;
    _buildCost = 500;
    _projectileSize = Projectile::SMALL;
    _projectileColour = Projectile::BLUE;
    _starshipName = "Support Ship";
    _assignedLaneIndex = spacelane;
    _starshipIndex = 2;

    _healthBar = std::make_unique<HealthBar>(_healthComponent , false);
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

    _attackableLanes.emplace_back(spacelane);
}

void SupportShip::EventHandler(sf::RenderWindow &window, sf::Event &event)
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

void SupportShip::Update(sf::RenderWindow &window, sf::Time deltaTime)
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

    if(_healthBar->GetHealth() < _maxHealth/* and _healthBar->GetHealth() > 0*/)
    {
        _isHealthBarVisible = true;
    }

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

    if(_isHealthBarVisible)
    {
        _healthBar->Render(window);
    }

    if(_isAttackRangeCircleVisible)
    {
        window.draw(_attackRangeCircle);
    }
}

void SupportShip::Move(float xOffset, float yOffset)
{
    _spriteComponent.Move(xOffset,  yOffset);
}

void SupportShip::ShootAt(sf::Vector2f target)
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

void SupportShip::ShootHealAt(const std::unique_ptr<IStarship> &friendlyStarship)
{
    if(_healingProjectileSpawnTimer < _healingProjectileSpawnTimerClock.getElapsedTime().asSeconds())
    {
        _healingProjectileSpawnTimer = _healingProjectileSpawnTimerClock.getElapsedTime().asSeconds();
    }

    if(_healingProjectileSpawnTimerClock.getElapsedTime().asSeconds() >= _healingProjectileSpawnTimer)
    {
        auto spawnPos = _spriteComponent.GetPos();
        _projectile.emplace_back(std::make_unique<Projectile>(_projectileSize, Projectile::Colour::GREEN, spawnPos, friendlyStarship->GetPos()));
        _healingProjectileSpawnTimer += (_fireRate/2.0F);
    }
}

void SupportShip::DestroyProjectile(int projectileIndex)
{
    _projectile.erase(_projectile.begin() + projectileIndex);
}

void SupportShip::TakeDamage(float damageAmount)
{
    _healthComponent.TakeDamage(damageAmount, GetPos());
}

void SupportShip::ReplenishHealth(float healthAmount)
{
    _healthComponent.ReplenishHealth(_maxHealth, healthAmount, GetPos());
}

void SupportShip::SetHealth(float health)
{
    _healthComponent.SetHealth(health);
}

void SupportShip::SetHealthBarVisibility(bool visible)
{
    _isHealthBarVisible = visible;
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
    _starshipColour = colour;
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

bool SupportShip::IsEnemyInRange(const std::unique_ptr<IStarship> &starship)
{
    return Chilli::Vector::Distance(GetPos(), starship->GetPos()) <= GetAttackRange();
}

bool SupportShip::IsFriendlyStarshipAhead(const std::unique_ptr<IStarship> &starship)
{
    bool isAhead;

    if(starship->GetRotation() == 180) // Starships traveling left (Enemy starships)
    {
        isAhead = starship->GetPos().x < this->GetPos().x;
    }
    else // Starships traveling right (Player starships)
    {
        isAhead = starship->GetPos().x > this->GetPos().x;
    }

    float distance = std::abs(starship->GetPos().x - this->GetPos().x);
    return isAhead and distance < 100.0F;
}

bool SupportShip::IsEnemyStarshipAhead(const std::unique_ptr<IStarship> &enemyStarship)
{
    return Chilli::Vector::Distance(this->GetPos(), enemyStarship->GetPos()) < 100;
}

bool SupportShip::CollidesWith(sf::Rect<float> spriteBounds)
{
    return _spriteComponent.GetSprite().getGlobalBounds().intersects(spriteBounds);
}

bool SupportShip::CanEngageWith(const std::unique_ptr<IStarship> &starship)
{
    return this->GetLaneIndex() == starship->GetLaneIndex();
}


















