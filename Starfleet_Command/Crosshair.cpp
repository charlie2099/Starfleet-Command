#include "Crosshair.hpp"


Crosshair::Crosshair()
{
    initTexture();
    sprite = std::make_unique<SpriteComponent>();
    sprite->getSprite().setTexture(texture);
    sprite->getSprite().setColor(sf::Color::Cyan);
    sprite->getSprite().setScale(0.35F, 0.35F);
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
    sprite->getSprite().setColor(sf::Color::Cyan);
    auto ship = starship->getSpriteCompo();
    auto crosshair_bounds = sprite->getSprite().getGlobalBounds();
    auto xpos = ship.getPos().x + ship.getSprite().getGlobalBounds().width / 2 - crosshair_bounds.width / 2;
    auto ypos = ship.getPos().y + ship.getSprite().getGlobalBounds().height / 2 - crosshair_bounds.height / 2;
    sprite->getSprite().setPosition(xpos, ypos);
}

void Crosshair::unSnap()
{
    is_visible_ = false;
    sprite->getSprite().setPosition(0, 0);
}

void Crosshair::setColour(sf::Color colour)
{
    sprite->getSprite().setColor(colour);
}

void Crosshair::setVisibility(bool visible)
{
    is_visible_ = visible;
}

bool Crosshair::getVisibility() const
{
    return is_visible_;
}

bool Crosshair::initTexture()
{
    if (!texture.loadFromFile("images/starfleet_selection_crosshairs.png"))
    {
        return false;
    }
    return true;
}


