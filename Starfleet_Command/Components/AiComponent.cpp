#include "AiComponent.hpp"

void AiComponent::EventHandler(sf::RenderWindow &window, sf::Event &event) {}

void AiComponent::Update(sf::RenderWindow &window, sf::Time deltaTime) {}

void AiComponent::Render(sf::RenderWindow &window) {}

void AiComponent::MoveTowards(sf::Sprite& sprite, sf::Vector2f target, float speed, sf::Time deltaTime)
{
    auto& ship_sprite = sprite;

    sf::Vector2f ship_dir = Chilli::Vector::Normalize(target - ship_sprite.getPosition());
    sf::Vector2f ship_move = ship_dir * speed;
    float ship_rot = atan2(ship_dir.y, ship_dir.x) * 180 / 3.141;

    ship_sprite.move(ship_move * deltaTime.asSeconds());
    ship_sprite.setRotation(ship_rot);
}
