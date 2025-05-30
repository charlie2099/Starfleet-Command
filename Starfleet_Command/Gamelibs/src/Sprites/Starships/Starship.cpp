#include "Sprites/Starships/Starship.hpp"

Starship::Starship(int spawnSpacelane, const std::string& starshipTypeName)
{
    auto starshipData = Chilli::JsonSaveSystem::LoadFile(STARSHIP_DATA_FILE_PATH);
    if(starshipData.contains("StarshipData"))
    {
        for(const auto& shipData : starshipData["StarshipData"])
        {
            if(shipData.contains("Name") && shipData["Name"] == starshipTypeName)
            {
                _starshipName = shipData["Name"];
                _starshipAbbreviation = shipData["Abbreviation"];
                _healthComponent.SetHealth(shipData["Health"]);
                _maximumDamage = shipData["MaxDamage"];
                _damageScaleFactor = shipData["DamageScaleFactor"];
                _speed = shipData["Speed"];
                _startSpeed = _speed;
                _deployTimeSpeed = shipData["DeployTime"];
                _fireRate = shipData["FireRate"];
                _attackRange = shipData["AttackRange"];
                _buildCost = shipData["BuildCost"];

                std::vector<int> attackLanes = shipData["AttackLanes"];
                for (const auto& laneOffset : attackLanes)
                {
                    int attackableLane = spawnSpacelane + laneOffset;

                    const int SPACELANE_COUNT = 4;
                    if(attackableLane >= 0 && attackableLane <= SPACELANE_COUNT)
                    {
                        _attackableLanes.emplace_back(attackableLane);
                    }
                }

                break;
            }
        }
    }

    _healthBar = std::make_unique<HealthBar>(_healthComponent, false);
    _healthBar->SetMaxHealth(_healthComponent.GetHealth());
    _maximumHealth = _healthComponent.GetHealth();
}

void Starship::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto worldPositionOfMouse = window.mapPixelToCoords(mouse_pos, window.getView()); // Mouse position translated into world coordinates

    if(Chilli::Vector::BoundsCheck(worldPositionOfMouse, _spriteComponent.GetSprite().getGlobalBounds()))
    {
        _isMouseOver = true;
    }
    else
    {
        _isMouseOver = false;
    }
}

void Starship::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    for(auto& projectiles : _projectiles)
    {
        projectiles->Update(window, deltaTime);
    }

    for (int i = 0; i < _projectiles.size(); ++i)
    {
        if(Chilli::Vector::Distance(GetPos(), _projectiles[i]->GetPos()) > Constants::WINDOW_WIDTH)
        {
            _projectiles.erase(_projectiles.begin() + i);
        }
    }

    _healthComponent.Update(window, deltaTime);

    auto ship_bounds = _spriteComponent.GetSprite().getGlobalBounds();
    auto bar_bounds = _healthBar->GetSpriteComponent().GetSprite().getGlobalBounds();
    auto xPos = (_spriteComponent.GetPos().x) - (ship_bounds.width/2.0f + bar_bounds.width/2.0f);
    auto yPos = (_spriteComponent.GetPos().y + ship_bounds.height/2.0f) - (ship_bounds.height + bar_bounds.height*4);
    _healthBar->Update(window, deltaTime);
    _healthBar->SetPos({xPos, yPos});

    if(_healthBar->GetHealth() < _maximumHealth/* && _healthBar->GetHealth() > 0*/)
    {
        _isHealthBarVisible = true;
    }
}

void Starship::Render(sf::RenderWindow &window)
{
    for(auto& projectiles : _projectiles)
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

void Starship::Move(float xOffset, float yOffset)
{
    _spriteComponent.Move(xOffset,  yOffset);
}

void Starship::ShootAt(sf::Vector2f target)
{
    if(_damagingProjectileSpawnTimer < _damagingProjectileSpawnTimerClock.getElapsedTime().asSeconds())
    {
        _damagingProjectileSpawnTimer = _damagingProjectileSpawnTimerClock.getElapsedTime().asSeconds();
    }

    if(_damagingProjectileSpawnTimerClock.getElapsedTime().asSeconds() >= _damagingProjectileSpawnTimer)
    {
        _projectiles.emplace_back(std::make_unique<Projectile>(_projectileSize, _projectileColour,  _spriteComponent.GetPos(), target));
        _projectiles.back()->SetPos({_spriteComponent.GetPos().x, _spriteComponent.GetPos().y - _projectiles.back()->GetSpriteComponent().GetSprite().getGlobalBounds().height/2.0F});

        _damagingProjectileSpawnTimer += _fireRate;
    }
}

void Starship::DestroyProjectile(int projectileIndex)
{
    _projectiles.erase(_projectiles.begin() + projectileIndex);
}

void Starship::TakeDamage(float damageAmount)
{
    _healthComponent.TakeDamage(damageAmount, GetPos());
}

void Starship::ReplenishHealth(float healthAmount)
{
    _healthComponent.ReplenishHealth(_maximumHealth, healthAmount, GetPos());
}

bool Starship::IsEnemyInRange(const std::unique_ptr<Starship> &starship)
{
    return Chilli::Vector::Distance(GetPos(), starship->GetPos()) <= GetAttackRange();
}

bool Starship::IsFriendlyStarshipAhead(const std::unique_ptr<Starship> &starship)
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

bool Starship::IsEnemyStarshipAhead(const std::unique_ptr<Starship> &enemyStarship)
{
    return Chilli::Vector::Distance(this->GetPos(), enemyStarship->GetPos()) < 100;
}

bool Starship::CanEngageWith(const std::unique_ptr<Starship> &enemyStarship)
{
    int enemyLane = enemyStarship->GetLaneIndex();

    for(const auto& lane : _attackableLanes)
    {
        if (lane == enemyLane)
        {
            return true;
        }
    }

    return false;
}

bool Starship::CollidesWith(sf::Rect<float> spriteBounds)
{
    return _spriteComponent.GetSprite().getGlobalBounds().intersects(spriteBounds);
}

void Starship::SetHealth(float health)
{
    _healthComponent.SetHealth(health);
}

void Starship::SetHealthBarVisibility(bool visible)
{
    _isHealthBarVisible = visible;
}

void Starship::SetDamage(float damage)
{
    _maximumDamage = damage;
}

void Starship::SetSpeed(float speed)
{
    _speed = speed;
}

void Starship::SetAcceleration(float acceleration)
{
    _acceleration = acceleration;
}

void Starship::SetAttackRange(float range)
{
    _attackRange = range;
}

void Starship::SetColour(sf::Color &colour)
{
    _spriteComponent.GetSprite().setColor(colour);
    _starshipColour = colour;
}

void Starship::SetPosition(sf::Vector2f pos)
{
    _spriteComponent.SetPos(pos);
}

void Starship::SetRotation(float rot)
{
    _spriteComponent.GetSprite().setRotation(rot);
    _rotation = rot;
}

void Starship::SetProjectileColour(sf::Color colour)
{
    if(colour == sf::Color::Cyan or colour == sf::Color::Blue or colour == Chilli::Colour::LIGHTBLUE)
    {
        _projectileColour = Projectile::BLUE;
    }
    else if(colour == sf::Color::Red or colour == Chilli::Colour::LIGHTRED)
    {
        _projectileColour = Projectile::RED;
    }
    else if(colour == sf::Color::Green or colour == Chilli::Colour::LIGHTGREEN)
    {
        _projectileColour = Projectile::GREEN;
    }
    else if(colour == Chilli::Colour::ORANGE or colour == Chilli::Colour::LIGHTORANGE)
    {
        _projectileColour = Projectile::ORANGE;
    }
    else if(colour == Chilli::Colour::YELLOW)
    {
        _projectileColour = Projectile::YELLOW;
    }
    else if(colour == Chilli::Colour::LIGHTPURPLE)
    {
        _projectileColour = Projectile::PURPLE;
    }
    else if(colour == Chilli::Colour::LIGHTPINK)
    {
        _projectileColour = Projectile::PINK;
    }
    else
    {
        std::cout << "WARNING: Could not locate projectile of the desired colour. Defaulting to WHITE. (" + _starshipName + ")" << std::endl;
        _projectileColour = Projectile::WHITE;
    }
}


