#include "Sprites/Starships/StarshipClasses/LightFighter.hpp"

LightFighter::LightFighter(int spacelane)
{
    auto starshipData = Chilli::JsonSaveSystem::LoadFile(STARSHIP_DATA_FILE_PATH);
    if(starshipData.contains("StarshipData"))
    {
        for(const auto& shipData : starshipData["StarshipData"])
        {
            if(shipData.contains("Name") && shipData["Name"] == "Light Fighter")
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
                break;
            }
        }
    }

    _spriteComponent.LoadSprite("Resources/Textures/starfleet_ship_0.png");
    _spriteComponent.GetSprite().scale({0.05F, 0.05F});
    _projectileSize = Projectile::SMALL;
    _projectileColour = Projectile::BLUE;
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

bool LightFighter::CanEngageWith(const std::unique_ptr<Starship> &starship)
{
    return this->GetLaneIndex() == starship->GetLaneIndex();
}

