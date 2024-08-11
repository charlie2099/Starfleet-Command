#include "Sprites/Player/Player.h"

void Player::Update(sf::RenderWindow &window, sf::Time deltaTime)
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

void Player::Render(sf::RenderWindow &window)
{
    for (auto& ship : starship)
    {
        ship->Render(window);
    }
}

std::vector<std::unique_ptr<IStarship>> &Player::GetShips()
{
    return starship;
}

std::unique_ptr<IStarship> &Player::GetFlagship()
{
    return starship[0];
}

void Player::CreateShip(StarshipFactory::SHIP_TYPE type)
{
    std::unique_ptr<IStarship> starship1 = StarshipFactory::CreateShip(type);
    starship.emplace_back(std::move(starship1));

    if(!starship.empty())
    {
        auto& flagship = starship[0];
        auto& newestShip = starship[starship.size()-1];
        newestShip->SetColour(flagship->GetColour());
        newestShip->SetProjectileColour(flagship->GetColour());
    }

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

void Player::PaintFlagship(sf::Color colour)
{
    starship[0]->SetColour(colour);
    starship[0]->SetProjectileColour(colour);
}

void Player::SetFlagshipPosition(sf::Vector2f pos)
{
    starship[0]->SetPosition(pos);
}

void Player::SetFleetPosition(std::unique_ptr<IStarship> &ship, sf::Vector2f pos)
{
    ship->SetPosition(pos);
}

void Player::AddBasicObserver(BasicPlayerEvent observer)
{
    _basicObservers.insert(observer);
}

void Player::AddAgnosticObserver(AgnosticPlayerEvent observer)
{
    _agnosticObservers.insert(observer);
}




