#include "Sprites/Projectiles/Projectile.hpp"
#include "Utility/Colour.hpp"

Projectile::Projectile(Projectile::Size size, Projectile::Colour colour, sf::Vector2f spawnPos, sf::Vector2f targetPos)
{
    _spriteComponent.LoadSprite("Resources/Textures/laser.png");

    switch (size)
    {
        case SMALL:
            _spriteComponent.GetSprite().setScale(0.35F, 0.35F);
            break;
        case REGULAR:
            _spriteComponent.GetSprite().setScale(0.5F, 0.5F);
            break;
        case LARGE:
            _spriteComponent.GetSprite().setScale(0.75F, 0.75F);
            break;
    }

    switch (colour)
    {
        case BLUE:
            _spriteComponent.GetSprite().setColor(Chilli::Colour::LIGHTBLUE);
            break;
        case RED:
            _spriteComponent.GetSprite().setColor(Chilli::Colour::LIGHTRED);
            break;
        case GREEN:
            _spriteComponent.GetSprite().setColor(Chilli::Colour::LIGHTGREEN);
            break;
        case ORANGE:
            _spriteComponent.GetSprite().setColor(Chilli::Colour::LIGHTORANGE);
            break;
        case YELLOW:
            _spriteComponent.GetSprite().setColor(Chilli::Colour::YELLOW);
            break;
        case PURPLE:
            _spriteComponent.GetSprite().setColor(Chilli::Colour::LIGHTPURPLE);
            break;
        case PINK:
            _spriteComponent.GetSprite().setColor(Chilli::Colour::LIGHTPINK);
            break;
        case WHITE:
            _spriteComponent.GetSprite().setColor(sf::Color::White);
            break;
        default:
            _spriteComponent.GetSprite().setColor(sf::Color::White);
    }

    _spriteComponent.SetPos(spawnPos);

    // Set rotation
    const float PI = 3.14159265;
    float dx = spawnPos.x - targetPos.x;
    float dy = spawnPos.y - targetPos.y;
    float rotation = (atan2(dy, dx)) * 180 / PI;
    _spriteComponent.GetSprite().setRotation(rotation + 180);

    // Set direction
    auto angleX = targetPos.x - _spriteComponent.GetPos().x;
    auto angleY = targetPos.y - _spriteComponent.GetPos().y;
    float vectorLength = sqrt(angleX*angleX + angleY*angleY);
    _direction.x = angleX / vectorLength;
    _direction.y = angleY / vectorLength;

    _size = size;
    _colour = colour;
    _spawnPos = spawnPos;
}

void Projectile::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    float speed = 500.0F;
    sf::Vector2f movement = _direction * speed;
    _spriteComponent.GetSprite().move(movement * deltaTime.asSeconds());
}

void Projectile::Render(sf::RenderWindow& window)
{
    _spriteComponent.Render(window);
}

