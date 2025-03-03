#include "Sprites/Projectiles/Projectile.hpp"

Projectile::Projectile(Projectile::Size size, Projectile::Colour colour, sf::Vector2f spawnPos, sf::Vector2f targetPos)
{
    switch (size)
    {
        case SMALL:
            switch (colour)
            {
                case BLUE:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_blue.png");
                    break;
                case GREEN:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_green.png");
                    break;
                case RED:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_red.png");
                    break;
                case ORANGE:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_orange.png");
                    break;
                case WHITE:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_white.png");
                    break;
            }
            _spriteComponent.GetSprite().setScale(0.35F, 0.35F);
            break;
        case REGULAR:
            switch (colour)
            {
                case BLUE:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_blue.png");
                    break;
                case GREEN:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_green.png");
                    break;
                case RED:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_red.png");
                    break;
                case ORANGE:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_orange.png");
                    break;
                case WHITE:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_white.png");
                    break;
            }
            _spriteComponent.GetSprite().setScale(0.5F, 0.5F);
            break;
        case LARGE:
            switch (colour)
            {
                case BLUE:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_blue.png");
                    break;
                case GREEN:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_green.png");
                    break;
                case RED:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_red.png");
                    break;
                case ORANGE:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_orange.png");
                    break;
                case WHITE:
                    _spriteComponent.LoadSprite("Resources/Textures/laser_white.png");
                    break;
            }
            _spriteComponent.GetSprite().setScale(0.75F, 0.75F);
            break;
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

SpriteComponent &Projectile::GetSpriteComponent()
{
    return _spriteComponent;
}
