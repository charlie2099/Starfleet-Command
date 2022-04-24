#include "Player.h"

void Player::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    for (auto& ship : starship)
    {
        ship->Update(window, deltaTime);
    }

    for (int i = 0; i < starship.size(); i++)
    {
        if(starship[i]->GetHealthBar().GetHealth() <= 0)
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

std::vector<std::unique_ptr<Starship>> &Player::GetShip()
{
    return starship;
}

void Player::CreateShip(Starship::Type type)
{
    starship.emplace_back(std::make_unique<Starship>(type));
}
