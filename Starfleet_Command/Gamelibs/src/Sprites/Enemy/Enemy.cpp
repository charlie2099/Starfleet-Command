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
    std::unique_ptr<IStarship> starship1 = StarshipFactory::CreateShip(type);
    starship.emplace_back(std::move(starship1));

    /// SHIP_SPAWNED event is invoked (non-agnostic)
    auto range = _basicObservers.equal_range(EventID::SHIP_SPAWNED);
    for(auto iter = range.first; iter != range.second; ++iter)
    {
        /// subscribed method is called
        iter->second();
    }

    /// SHIP_SPAWNED event is invoked (agnostic)
    auto ag_range = _agnosticObservers.equal_range(EventID::SHIP_SPAWNED);
    for(auto iter = ag_range.first; iter != ag_range.second; ++iter)
    {
        /// subscribed method is called
        iter->second(this);
    }
}

void Enemy::AddBasicObserver(BasicEnemyEvent observer)
{
    _basicObservers.insert(observer);
}

void Enemy::AddAgnosticObserver(AgnosticEnemyEvent observer)
{
    _agnosticObservers.insert(observer);
}

std::vector<std::unique_ptr<IStarship>> &Enemy::GetShips()
{
    return starship;
}






