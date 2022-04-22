#include "Projectile.hpp"

Projectile::Projectile(Projectile::Type type, sf::Vector2<float> start_pos, sf::Vector2<float> mouse_pos) : type_(type), click_position_(mouse_pos)
{
    switch (type)
    {
        case Type::LASER_BLUE:
            sprite_.LoadSprite("images/laser_blue.png");
            break;
        case Type::LASER_RED:
            sprite_.LoadSprite("images/laser_red.png");
            break;
        case Type::MISSILE_BLUE:
            sprite_.LoadSprite("images/missile_blue.png");
            break;
        case Type::MISSILE_RED:
            sprite_.LoadSprite("images/missile_red.png");
            break;
    }

    sprite_.GetSprite().setScale(0.5F, 0.5F);
    sprite_.SetPos(start_pos);

    // Set rotation
    const float PI = 3.14159265;
    float dx = start_pos.x - mouse_pos.x;
    float dy = start_pos.y - mouse_pos.y;
    float rotation = (atan2(dy, dx)) * 180 / PI;
    sprite_.GetSprite().setRotation(rotation + 180);

    // Set direction
    auto angleX = mouse_pos.x - sprite_.GetPos().x;
    auto angleY = mouse_pos.y - sprite_.GetPos().y;
    float vectorLength = sqrt(angleX*angleX + angleY*angleY);
    direction_.x = angleX / vectorLength;
    direction_.y = angleY / vectorLength;
}

void Projectile::update(sf::RenderWindow &window, sf::Time deltaTime)
{
    // Shoot projectile towards position of mouse click
    float speed = 200.0F;
    sf::Vector2f movement = direction_ * speed;
    sprite_.GetSprite().move(movement * deltaTime.asSeconds());


    // TODO: Change this so the projectiles follow the position
    //  and rotation of the mouse and NOT the ship
    /*//Convert angle to radians
    const float PI = 3.14159265;
    double angleRADS = (PI/180)*(sprite_.getSprite().getRotation());

    // move ship in direction it is facing
    sf::Vector2f direction;
    direction.x = cos(angleRADS);
    direction.y = sin(angleRADS);

    float speed = 200.0F;
    sf::Vector2f movement = direction * speed;
    sprite_.GetSprite().move(movement * deltaTime.asSeconds());*/
}

void Projectile::render(sf::RenderWindow &window)
{
    sprite_.Render(window);
}

SpriteComponent &Projectile::getSprite()
{
    return sprite_;
}
