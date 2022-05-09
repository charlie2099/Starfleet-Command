#include "Sprites/Player/Player.h"

void Player::Update(sf::RenderWindow &window, sf::Time deltaTime)
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

void Player::Render(sf::RenderWindow &window)
{
    for (auto& ship : starship)
    {
        ship->Render(window);
    }
}

std::vector<std::unique_ptr<OLDStarship>> &Player::GetShip()
{
    return starship;
}

void Player::CreateShip(OLDStarship::Type type)
{
    starship.emplace_back(std::make_unique<OLDStarship>(type));

    /// SHIP_SPAWNED event is invoked (non-agnostic)
    auto range = _observers.equal_range(EventID::SHIP_SPAWNED);
    for(auto iter = range.first; iter != range.second; ++iter)
    {
        /// subscribed method is called
        iter->second();
    }

    /// SHIP_SPAWNED event is invoked (agnostic)
    auto ag_range = _observers_agnostic.equal_range(EventID::SHIP_SPAWNED);
    for(auto iter = ag_range.first; iter != ag_range.second; ++iter)
    {
        /// subscribed method is called
        iter->second(this);
    }
}

void Player::AddObserver(PlayerEvent observer)
{
    _observers.insert(observer);
}

void Player::AddObserver2(Player::PlayerAgnosticEvent observer)
{
    _observers_agnostic.insert(observer);
}
