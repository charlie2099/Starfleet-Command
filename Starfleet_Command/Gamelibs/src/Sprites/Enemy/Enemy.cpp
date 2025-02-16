#include "Sprites/Enemy/Enemy.hpp"

void Enemy::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    for (auto& ship : starship)
    {
        ship->Update(window, deltaTime);
    }

    for (int i = 0; i < starship.size(); i++)
    {
        if(starship[i]->GetHealthComponent().GetHealth() <= 0)
        {
            ShipDataToSend dataToSend;
            dataToSend.DeathLocation = starship[i]->GetPos();
            dataToSend.BuildCost = starship[i]->GetBuildCost();
            InvokeAgnosticEvent(SHIP_DESTROYED, dataToSend);

            starship.erase(starship.begin() + i);
        }
    }
}

void Enemy::Render(sf::RenderWindow &window)
{
    for (auto& ship : starship)
    {
        ship->Render(window);
    }
}

void Enemy::CreateShip(StarshipFactory::SHIP_TYPE type)
{
    std::unique_ptr<IStarship> newStarship = StarshipFactory::CreateShip(type);
    bool atLeastOneShipExists = !starship.empty();
    if(atLeastOneShipExists)
    {
        auto& flagship = starship[0];
        newStarship->SetColour(flagship->GetColour());
        newStarship->SetProjectileColour(flagship->GetColour());
    }
    starship.emplace_back(std::move(newStarship));
    InvokeBasicEvent(SHIP_SPAWNED); // QUESTION: Are these both needed? Can just agnostic be used?
    InvokeAgnosticEvent(SHIP_SPAWNED, this);
}

void Enemy::PaintFlagship(sf::Color colour)
{
    starship[0]->SetColour(colour);
    starship[0]->SetProjectileColour(colour);
}

void Enemy::SetFlagshipPosition(sf::Vector2f pos)
{
    starship[0]->SetPosition(pos);
}

void Enemy::SetFlagshipRotation(float rot)
{
    starship[0]->SetRotation(rot);
}

void Enemy::SetShipPosition(std::unique_ptr<IStarship> &ship, sf::Vector2f pos)
{
    ship->SetPosition(pos);
}

void Enemy::SetShipRotation(std::unique_ptr<IStarship> &ship, float rot)
{
    ship->SetRotation(rot);
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

std::vector<std::unique_ptr<IStarship>> &Enemy::GetShips()
{
    return starship;
}

std::unique_ptr<IStarship> &Enemy::GetFlagship()
{
    return starship[0];
}


