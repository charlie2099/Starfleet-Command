#include "Sprites/Projectiles/Projectile.hpp"

Projectile::Projectile(Projectile::Type type, sf::Vector2f spawn_pos, sf::Vector2f target_pos) : _type(type)
{
    switch (type)
    {
        case Type::LASER_RED_SMALL:
            _spriteComponent.LoadSprite("Resources/Textures/laser_red.png");
            _spriteComponent.GetSprite().setScale(0.35F, 0.35F);
            break;
        case Type::LASER_BLUE_SMALL:
            _spriteComponent.LoadSprite("Resources/Textures/laser_blue.png");
            _spriteComponent.GetSprite().setScale(0.35F, 0.35F);
            break;
        case Type::LASER_GREEN_SMALL:
            _spriteComponent.LoadSprite("Resources/Textures/laser_green.png");
            _spriteComponent.GetSprite().setScale(0.35F, 0.35F);
            break;
        case Type::LASER_RED_REGULAR:
            _spriteComponent.LoadSprite("Resources/Textures/laser_red.png");
            _spriteComponent.GetSprite().setScale(0.5F, 0.5F);
            break;
        case Type::LASER_BLUE_REGULAR:
            _spriteComponent.LoadSprite("Resources/Textures/laser_blue.png");
            _spriteComponent.GetSprite().setScale(0.5F, 0.5F);
            break;
        case Type::LASER_GREEN_REGULAR:
            _spriteComponent.LoadSprite("Resources/Textures/laser_green.png");
            _spriteComponent.GetSprite().setScale(0.5F, 0.5F);
            break;
        case Type::LASER_RED_LARGE:
            _spriteComponent.LoadSprite("Resources/Textures/laser_red.png");
            _spriteComponent.GetSprite().setScale(0.75F, 0.75F);
            break;
        case Type::LASER_BLUE_LARGE:
            _spriteComponent.LoadSprite("Resources/Textures/laser_blue.png");
            _spriteComponent.GetSprite().setScale(0.75F, 0.75F);
            break;
        case Type::LASER_GREEN_LARGE:
            _spriteComponent.LoadSprite("Resources/Textures/laser_green.png");
            _spriteComponent.GetSprite().setScale(0.75F, 0.75F);
            break;
    }
    _spriteComponent.SetPos(spawn_pos);

    // Set rotation
    const float PI = 3.14159265;
    float dx = spawn_pos.x - target_pos.x;
    float dy = spawn_pos.y - target_pos.y;
    float rotation = (atan2(dy, dx)) * 180 / PI;
    _spriteComponent.GetSprite().setRotation(rotation + 180);

    // Set direction
    auto angleX = target_pos.x - _spriteComponent.GetPos().x;
    auto angleY = target_pos.y - _spriteComponent.GetPos().y;
    float vectorLength = sqrt(angleX*angleX + angleY*angleY);
    _direction.x = angleX / vectorLength;
    _direction.y = angleY / vectorLength;

    _type = type;
}

void Projectile::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    // Shoot projectile towards position of mouse click
    float speed = 500.0F;
    sf::Vector2f movement = _direction * speed;
    _spriteComponent.GetSprite().move(movement * deltaTime.asSeconds());

    // TODO: Change this so the projectiles follow the position
    //  and rotation of the mouse and NOT the ship
    /*//Convert angle to radians
    const float PI = 3.14159265;
    double angleRADS = (PI/180)*(_spriteComponent.GetSprite().getRotation());

    // move ship in direction it is facing
    sf::Vector2f direction;
    direction.x = cos(angleRADS);
    direction.y = sin(angleRADS);

    float speed = 200.0F;
    sf::Vector2f movement = direction * speed;
    _spriteComponent.GetSpriteComponent().move(movement * deltaTime.asSeconds());*/
}

void Projectile::Render(sf::RenderWindow& window)
{
    _spriteComponent.Render(window);
}

SpriteComponent &Projectile::GetSpriteComponent()
{
    return _spriteComponent;
}
