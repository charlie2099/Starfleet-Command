#include "Sprites/Starships/StarshipClasses/Destroyer.hpp"

Destroyer::Destroyer(int spacelane)
{
    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_3.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _healthComponent.SetHealth(1500);
    _speed = 40;
    _trainingSpeed = 0.2f;
    _damage = 150;
    _damageScaleFactor = 1.0f;
    _fireRate = 3.0f;
    _attackRange = 800.0F;
    _buildCost = 1000;
    _projectileSize = Projectile::LARGE;
    _projectileColour = Projectile::BLUE;
    _starshipName = "Destroyer";
    _assignedLaneIndex = spacelane;

    _healthBar = std::make_unique<HealthBar>(_healthComponent);
    _healthBar->SetMaxHealth(_healthComponent.GetHealth());
    _maxHealth = _healthComponent.GetHealth();

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = _spriteComponent.GetSprite().getLocalBounds().width / 2;
    centered_origin.y = _spriteComponent.GetSprite().getLocalBounds().height / 2;
    _spriteComponent.GetSprite().setOrigin(centered_origin);

    //auto callbackFnc1 = std::bind(&TestClass::TestFncForObserverToCall, testClass);
    //_healthComponent.AddBasicObserver({HealthComponent::HEALTH_DEPLETED, callbackFnc1}); // NOTE: Or handle in Destructor instead of as an event?

    _attackRangeCircle.setRadius(_attackRange);
    _attackRangeCircle.setFillColor({253, 103, 100, 50});
    _attackRangeCircle.setOutlineColor(sf::Color(255, 0, 0, 150));
    _attackRangeCircle.setOutlineThickness(2.0F);
    _attackRangeCircle.setOrigin(_attackRangeCircle.getRadius(), _attackRangeCircle.getRadius());
    _attackRangeCircle.setPosition(_spriteComponent.GetPos());

    if(spacelane == 0)
    {
        _attackableLanes.emplace_back(spacelane);
        _attackableLanes.emplace_back(spacelane+1);
        _attackableLanes.emplace_back(spacelane+2);
    }
    if(spacelane == 1)
    {
        _attackableLanes.emplace_back(spacelane-1);
        _attackableLanes.emplace_back(spacelane);
        _attackableLanes.emplace_back(spacelane+1);
        _attackableLanes.emplace_back(spacelane+2);
    }
    else if(spacelane == 3)
    {
        _attackableLanes.emplace_back(spacelane-2);
        _attackableLanes.emplace_back(spacelane-1);
        _attackableLanes.emplace_back(spacelane);
        _attackableLanes.emplace_back(spacelane+1);
    }
    else if(spacelane == 4)
    {
        _attackableLanes.emplace_back(spacelane-2);
        _attackableLanes.emplace_back(spacelane-1);
        _attackableLanes.emplace_back(spacelane);
    }
    else
    {
        _attackableLanes.emplace_back(spacelane-2);
        _attackableLanes.emplace_back(spacelane-1);
        _attackableLanes.emplace_back(spacelane);
        _attackableLanes.emplace_back(spacelane+1);
        _attackableLanes.emplace_back(spacelane+2);
    }
}

void Destroyer::EventHandler(sf::RenderWindow &window, sf::Event &event)
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

void Destroyer::Update(sf::RenderWindow &window, sf::Time deltaTime)
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

    if(_healthBar->GetHealth() < _maxHealth)
    {
        _isHealthBarVisible = true;
    }

    if(_isAttackRangeCircleVisible)
    {
        _attackRangeCircle.setPosition(_spriteComponent.GetPos());
    }
}

void Destroyer::Render(sf::RenderWindow &window)
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

void Destroyer::Move(float xOffset, float yOffset)
{
    _spriteComponent.Move(xOffset,  yOffset);
}

void Destroyer::ShootAt(float fireRate, sf::Vector2f target)
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

void Destroyer::DestroyProjectile(int projectileIndex)
{
    _projectile.erase(_projectile.begin() + projectileIndex);
}

void Destroyer::TakeDamage(float damageAmount)
{
    _healthComponent.TakeDamage(damageAmount, GetPos());
}

void Destroyer::SetHealth(float health)
{
    _healthComponent.SetHealth(health);
}

void Destroyer::SetHealthBarVisibility(bool visible)
{
    _isHealthBarVisible = visible;
}

void Destroyer::SetDamage(float damage)
{
    _damage = damage;
}

void Destroyer::SetSpeed(float speed)
{
    _speed = speed;
}

void Destroyer::SetAcceleration(float acceleration)
{
    _acceleration = acceleration;
}

void Destroyer::SetAttackRange(float range)
{
    _attackRange = range;
}

void Destroyer::SetColour(sf::Color &colour)
{
    _spriteComponent.GetSprite().setColor(colour);
    _starshipColour = colour;
}

void Destroyer::SetPosition(sf::Vector2f pos)
{
    _spriteComponent.SetPos(pos);
}

void Destroyer::SetRotation(float rot)
{
    _spriteComponent.GetSprite().setRotation(rot);
    _rotation = rot;
}

bool Destroyer::IsProjectileOutOfRange(int projectileIndex)
{
    return Chilli::Vector::Distance(GetPos(), _projectile[projectileIndex]->GetPos()) > Constants::WINDOW_WIDTH;
}

bool Destroyer::IsEnemyInRange(const std::unique_ptr<IStarship> &enemyStarship)
{
    return Chilli::Vector::Distance(GetPos(), enemyStarship->GetPos()) <= GetAttackRange();
}

bool Destroyer::CollidesWith(sf::Rect<float> spriteBounds)
{
    return _spriteComponent.GetSprite().getGlobalBounds().intersects(spriteBounds);
}

bool Destroyer::CanAttackEnemy(const std::unique_ptr<IStarship> &enemyStarship)
{
    if(this->GetLaneIndex() == enemyStarship->GetLaneIndex() - 2 ||
            this->GetLaneIndex() == enemyStarship->GetLaneIndex() - 1 ||
            this->GetLaneIndex() == enemyStarship->GetLaneIndex() ||
            this->GetLaneIndex() == enemyStarship->GetLaneIndex() + 1 ||
            this->GetLaneIndex() == enemyStarship->GetLaneIndex() + 2)
    {
        return true;
    }
    return false;
}

/*void Destroyer::SetAttackRangeVisibility(bool visibility)
{
    _isAttackRangeCircleVisible = visibility;
}*/



















