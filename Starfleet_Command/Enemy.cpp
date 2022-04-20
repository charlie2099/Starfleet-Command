#include "Enemy.hpp"

void Enemy::Update(sf::RenderWindow &window, sf::Time deltaTime)
{

}

void Enemy::Render(sf::RenderWindow &window)
{
    for (auto& ship : starship)
    {
        ship->Render(window);
    }
}

std::vector<std::unique_ptr<Starship>> &Enemy::GetShip()
{
    return starship;
}

void Enemy::CreateShip(Starship::Type type)
{
    starship.emplace_back(std::make_unique<Starship>(type));
}



