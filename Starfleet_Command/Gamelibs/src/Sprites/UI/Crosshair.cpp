#include <iostream>
#include "Sprites/UI/Crosshair.hpp"


Crosshair::Crosshair()
{
    initTexture();
    sprite = std::make_unique<SpriteComponent>();
    sprite->GetSprite().setTexture(texture);
    sprite->GetSprite().setColor(colour_);
    sprite->GetSprite().setScale(0.25F, 0.25F);
}

void Crosshair::render(sf::RenderWindow &window)
{
    if(is_visible_)
    {
        window.draw(sprite->GetSprite());
    }
}

std::unique_ptr<SpriteComponent>& Crosshair::getSprite()
{
    return sprite;
}

void Crosshair::snapTo(std::unique_ptr<OLDStarship>& starship)
{
    is_visible_ = true;
    sprite->GetSprite().setColor(colour_);
    auto& ship = starship->GetSpriteComponent();
    auto crosshair_bounds = sprite->GetSprite().getGlobalBounds();

    if(ship.GetSprite().getOrigin().x == 0)
    {
        /// Default origin
        sf::Vector2<float> topleftPos;
        topleftPos.x = ship.GetPos().x + ship.GetSprite().getGlobalBounds().width / 2 - crosshair_bounds.width / 2;
        topleftPos.y = ship.GetPos().y + ship.GetSprite().getGlobalBounds().height / 2 - crosshair_bounds.height / 2;
        sprite->GetSprite().setPosition(topleftPos);
    }
    else
    {
        /// Centered origin
        sf::Vector2<float> centerPos;
        centerPos.x = ship.GetPos().x - crosshair_bounds.width / 2;
        centerPos.y = ship.GetPos().y - crosshair_bounds.height / 2;
        sprite->GetSprite().setPosition(centerPos);
    }
}

void Crosshair::unSnap()
{
    is_visible_ = false;
    sprite->GetSprite().setPosition(0, 0);
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
    if (!texture.loadFromFile("Resources/Textures/starfleet_selection_crosshairs.png"))
    {
        return false;
    }
    return true;
}

void Crosshair::sizeAdjust(std::unique_ptr<OLDStarship>& starship)
{
    auto starship_spr = starship->GetSpriteComponent().GetSprite();
    float scale_x = starship_spr.getGlobalBounds().width * starship_spr.getScale().x/8.0F;
    float scale_y = starship_spr.getGlobalBounds().height * starship_spr.getScale().y/8.0F;
    sprite->GetSprite().setScale({scale_x, scale_y});
}



