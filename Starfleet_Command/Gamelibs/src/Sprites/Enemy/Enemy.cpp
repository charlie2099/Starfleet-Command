#include "Sprites/Enemy/Enemy.hpp"

Enemy::Enemy(int startingScrapAmount, sf::Color teamColour)
{
    _scrapMetalManager = std::make_unique<ScrapMetalManager>(Chilli::Colour::GRAY, teamColour, startingScrapAmount);
    _teamColour = teamColour;
}

void Enemy::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    _scrapMetalManager->Update(window, deltaTime);
    _scrapMetalManager->SetTextPosition(_scrapTextPos.x, _scrapTextPos.y);

    for (auto& ship : starships)
    {
        ship->Update(window, deltaTime);
    }

    for (int i = 0; i < starships.size(); i++)
    {
        if(starships[i]->GetHealth() <= 0)
        {
            StarshipDestroyedData destroyedStarshipData;
            destroyedStarshipData.DeathLocation = starships[i]->GetPos();
            destroyedStarshipData.BuildCost = starships[i]->GetBuildCost();
            InvokeAgnosticEvent(STARSHIP_DESTROYED, destroyedStarshipData);
            starships.erase(starships.begin() + i);
        }
    }
}

void Enemy::RenderGameplaySprites(sf::RenderWindow &window)
{
    for (auto& ship : starships)
    {
        ship->Render(window);
    }
    _scrapMetalManager->Render(window);
}

void Enemy::RenderMinimapSprites(sf::RenderWindow &window)
{
    for (auto& ship : starships)
    {
        ship->Render(window);
    }
}

void Enemy::MoveStarship(int starshipIndex, sf::Vector2<float> positionOffset)
{
    starships[starshipIndex]->Move(positionOffset.x, positionOffset.y);
}

void Enemy::CreateStarship(StarshipFactory::STARSHIP_TYPE starshipType, int spacelane)
{
    std::unique_ptr<Starship> newStarship = StarshipFactory::CreateShip(starshipType, spacelane);
    newStarship->SetColour(_teamColour);
    newStarship->SetProjectileColour(_teamColour);
    starships.emplace_back(std::move(newStarship));
    InvokeBasicEvent(STARSHIP_SPAWNED);
}

void Enemy::CreateScrapPopup(int scrapAmount, sf::Vector2<float> pos)
{
    _scrapMetalManager->CreatePopup(scrapAmount, pos);
}

void Enemy::SetMothershipPosition(sf::Vector2f pos)
{
    starships[0]->SetPosition(pos);
}

void Enemy::SetMothershipRotation(float rot)
{
    starships[0]->SetRotation(rot);
}

void Enemy::SetStarshipPosition(std::unique_ptr<Starship> &ship, sf::Vector2f pos)
{
    ship->SetPosition(pos);
}

void Enemy::SetStarshipRotation(std::unique_ptr<Starship> &ship, float rot)
{
    ship->SetRotation(rot);
}

void Enemy::SetTeamColour(sf::Color colour)
{
    for (const auto & starship : starships)
    {
        starship->SetColour(colour);
    }
    _teamColour = colour;
}

void Enemy::SpendScrap(int buildCost)
{
    _scrapMetalManager->SpendScrap(buildCost);
}

void Enemy::CollectScrap(int scrapAmount)
{
    _scrapMetalManager->CollectScrap(scrapAmount);
}

void Enemy::SetScrapText(const std::string& scrapText)
{
    _scrapMetalManager->SetScrapText(scrapText);
}

void Enemy::SetScrapTextPosition(sf::Vector2<float> pos)
{
    _scrapTextPos = pos;
}

void Enemy::AddBasicObserver(BasicEnemyEvent observer)
{
    _basicObservers.insert(observer);
}

void Enemy::AddAgnosticObserver(AgnosticEnemyEvent observer)
{
    _agnosticObservers.insert(observer);
}

void Enemy::InvokeBasicEvent(EventID eventId)
{
    /// Invokes the callback function assigned to the specified event id?
    auto range = _basicObservers.equal_range(eventId);
    for(auto iter = range.first; iter != range.second; ++iter)
    {
        // subscribed method is called
        iter->second();
    }
}

void Enemy::InvokeAgnosticEvent(EventID eventId, const std::any& anyData)
{
    /// Invokes the callback function assigned to the specified event id?
    auto ag_range = _agnosticObservers.equal_range(eventId);
    for(auto iter = ag_range.first; iter != ag_range.second; ++iter)
    {
        /// subscribed method is called
        iter->second(anyData);
    }
}





