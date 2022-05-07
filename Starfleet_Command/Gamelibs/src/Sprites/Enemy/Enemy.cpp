#include "Sprites/Enemy/Enemy.hpp"

void Enemy::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    for (auto& ship : starship)
    {
        ship->Update(window, deltaTime);
    }

    for (int i = 0; i < starship.size(); i++)
    {
        if(starship[i]->GetHealthBar()->GetHealth() <= 0)
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

void Enemy::CreateShip(Starship::Type type)
{
    starship.emplace_back(std::make_unique<Starship>(type));

    auto range = _observers.equal_range(EventID::SHIP_SPAWNED);
    for(auto iter = range.first; iter != range.second; ++iter)
    {
        iter->second();
    }
}

void Enemy::AddObserver(std::pair<EventID, std::function<void()>> observer)
{
    _observers.insert(observer);
}

std::vector<std::unique_ptr<Starship>> &Enemy::GetShip()
{
    return starship;
}




