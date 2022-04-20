#include "Player1.h"

void Player1::Update(sf::RenderWindow &window, sf::Time deltaTime)
{

}

void Player1::Render(sf::RenderWindow &window)
{
    for (auto& ship : starship)
    {
        ship->Render(window);
    }
}

std::vector<std::unique_ptr<Starship>> &Player1::GetShip()
{
    return starship;
}

void Player1::CreateShip(Starship::Type type)
{
    starship.emplace_back(std::make_unique<Starship>(type));
}
