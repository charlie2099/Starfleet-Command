#include "Sprites/Starships/StarshipClasses/HeavyFighter.hpp"

HeavyFighter::HeavyFighter(int spacelane)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_1.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(300);
    _speed = 80;
    _startSpeed = _speed;
    _trainingSpeed = 0.4f;
    _damage = 20;
    _damageScaleFactor = 0.25f;
    _fireRate = 0.25f;
    _attackRange = 300.0F;
    _buildCost = 250;
    _projectileSize = Projectile::REGULAR;
    _projectileColour = Projectile::BLUE;
    _starshipName = "Heavy Fighter";
    _assignedLaneIndex = spacelane;
    _starshipIndex = 1;

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

    _attackableLanes.emplace_back(spacelane);
}

void HeavyFighter::EventHandler(sf::RenderWindow &window, sf::Event &event)
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

void HeavyFighter::Update(sf::RenderWindow &window, sf::Time deltaTime)
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

    if(_healthBar->GetHealth() < _maxHealth/* && _healthBar->GetHealth() > 0*/)
    {
        _isHealthBarVisible = true;
    }

    if(_isAttackRangeCircleVisible)
    {
        _attackRangeCircle.setPosition(_spriteComponent.GetPos());
    }
}

void HeavyFighter::Render(sf::RenderWindow &window)
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

void HeavyFighter::Move(float xOffset, float yOffset)
{
    _spriteComponent.Move(xOffset,  yOffset);
}

void HeavyFighter::ShootAt(sf::Vector2f target)
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

void HeavyFighter::DestroyProjectile(int projectileIndex)
{
    _projectile.erase(_projectile.begin() + projectileIndex);
}

void HeavyFighter::TakeDamage(float damageAmount)
{
    _healthComponent.TakeDamage(damageAmount, GetPos());
}

void HeavyFighter::ReplenishHealth(float healthAmount)
{
    _healthComponent.ReplenishHealth(_maxHealth, healthAmount, GetPos());
}

void HeavyFighter::SetHealth(float health)
{
    _healthComponent.SetHealth(health);
}

void HeavyFighter::SetHealthBarVisibility(bool visible)
{
    _isHealthBarVisible = visible;
}

void HeavyFighter::SetDamage(float damage)
{
    _damage = damage;
}

void HeavyFighter::SetSpeed(float speed)
{
    _speed = speed;
}

void HeavyFighter::SetAcceleration(float acceleration)
{
    _acceleration = acceleration;
}

void HeavyFighter::SetAttackRange(float range)
{
    _attackRange = range;
}

void HeavyFighter::SetColour(sf::Color &colour)
{
    _spriteComponent.GetSprite().setColor(colour);
    _starshipColour = colour;
}

void HeavyFighter::SetPosition(sf::Vector2f pos)
{
    _spriteComponent.SetPos(pos);
}

void HeavyFighter::SetRotation(float rot)
{
    _spriteComponent.GetSprite().setRotation(rot);
    _rotation = rot;
}

bool HeavyFighter::IsEnemyInRange(const std::unique_ptr<IStarship> &starship)
{
    return Chilli::Vector::Distance(GetPos(), starship->GetPos()) <= GetAttackRange();
}

bool HeavyFighter::IsFriendlyStarshipAhead(const std::unique_ptr<IStarship> &starship)
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
    return isAhead && distance < 100.0F;
}

bool HeavyFighter::IsEnemyStarshipAhead(const std::unique_ptr<IStarship> &enemyStarship)
{
    return Chilli::Vector::Distance(this->GetPos(), enemyStarship->GetPos()) < 100;
}

bool HeavyFighter::CollidesWith(sf::Rect<float> spriteBounds)
{
    return _spriteComponent.GetSprite().getGlobalBounds().intersects(spriteBounds);
}

bool HeavyFighter::CanEngageWith(const std::unique_ptr<IStarship> &starship)
{
    return this->GetLaneIndex() == starship->GetLaneIndex();
}










