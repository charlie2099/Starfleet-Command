#include <iostream>
#include "Crosshair.hpp"


Crosshair::Crosshair()
{
    initTexture();
    sprite = std::make_unique<SpriteComponent>();
    sprite->getSprite().setTexture(texture);
    sprite->getSprite().setColor(colour_);
    sprite->getSprite().setScale(0.36F, 0.36F);
}

void Crosshair::render(sf::RenderWindow &window)
{
    if(is_visible_)
    {
        window.draw(sprite->getSprite());
    }
}

std::unique_ptr<SpriteComponent>& Crosshair::getSprite()
{
    return sprite;
}

void Crosshair::snapTo(std::unique_ptr<Starship>& starship)
{
    is_visible_ = true;
    sprite->getSprite().setColor(colour_);
    auto& ship = starship->GetSpriteComponent();
    auto crosshair_bounds = sprite->getSprite().getGlobalBounds();

    if(ship.getSprite().getOrigin().x == 0)
    {
        /// Default origin
        sf::Vector2<float> topleftPos;
        topleftPos.x = ship.getPos().x + ship.getSprite().getGlobalBounds().width/2 - crosshair_bounds.width/2;
        topleftPos.y = ship.getPos().y + ship.getSprite().getGlobalBounds().height/2 - crosshair_bounds.height/2;
        sprite->getSprite().setPosition(topleftPos);
    }
    else
    {
        /// Centered origin
        sf::Vector2<float> centerPos;
        centerPos.x = ship.getPos().x - crosshair_bounds.width / 2;
        centerPos.y = ship.getPos().y - crosshair_bounds.height/2;
        sprite->getSprite().setPosition(centerPos);
    }
}

void Crosshair::unSnap()
{
    is_visible_ = false;
    sprite->getSprite().setPosition(0, 0);
}

void Crosshair::setColour(sf::Color colour)
{
    colour_ = colour;
}

void Crosshair::setVisibility(bool visible)
{
    is_visible_ = visible;
}

bool Crosshair::getVisibility() const
{
    return is_visible_;
}

sf::Color &Crosshair::getColour()
{
    return colour_;
}

bool Crosshair::initTexture()
{
    if (!texture.loadFromFile("images/starfleet_selection_crosshairs.png"))
    {
        return false;
    }
    return true;
}

void Crosshair::sizeAdjust(std::unique_ptr<Starship>& starship)
{
    auto starship_spr = starship->GetSpriteComponent().getSprite();
    float scale_x = starship_spr.getGlobalBounds().width * starship_spr.getScale().x/8.0F;
    float scale_y = starship_spr.getGlobalBounds().height * starship_spr.getScale().y/8.0F;
    sprite->getSprite().setScale({scale_x, scale_y});
}



