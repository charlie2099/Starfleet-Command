#include "Player.hpp"

void Player::eventHandler(sf::RenderWindow &window, sf::Event &event)
{
    for(key_idx = key_state.begin(); key_idx != key_state.end(); ++key_idx)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            // first element of map is a keyboard keycode
            if(event.key.code == key_idx->first)
            {
                key_state[event.key.code] = true;
            }
        }

        else if (event.type == sf::Event::KeyReleased)
        {
            if(event.key.code == key_idx->first)
            {
                key_state[event.key.code] = false;
            }
        }
    }
}

void Player::update(sf::RenderWindow &window, sf::Time deltaTime)
{
    auto& flagship = this->getShip()[this->getShip().size()-1];
    auto& flagship_spr = flagship->getSpriteComponent();

    //Convert angle to radians
    double angleRADS = (3.1415926536/180)*(flagship_spr.getSprite().getRotation());

    // move ship in direction it is facing
    sf::Vector2f direction;
    direction.x = cos(angleRADS);
    direction.y = sin(angleRADS);

    float speed = 50.0F;

    if(key_state[sf::Keyboard::W])
    {
        speed *= 3.0F;
    }
    else if(key_state[sf::Keyboard::A])
    {
        flagship_spr.getSprite().rotate(-65 * deltaTime.asSeconds());
    }
    else if(key_state[sf::Keyboard::S])
    {
        speed /= 2.0F;
    }
    else if(key_state[sf::Keyboard::D])
    {
        flagship_spr.getSprite().rotate(65 * deltaTime.asSeconds());
    }

    sf::Vector2f movement = direction * speed;
    flagship_spr.getSprite().move(movement * deltaTime.asSeconds());
}

void Player::setCredits(int credits)
{
    player_credits = credits;
}

int Player::getCredits() const
{
    return player_credits;
}

std::vector<std::unique_ptr<Starship>> &Player::getShip()
{
    return starship;
}
