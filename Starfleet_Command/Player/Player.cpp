#include "Player.hpp"

void Player::eventHandler(sf::RenderWindow &window, sf::Event &event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    // Flagship Controls
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

    // TODO: Should this be in gamescene?
    // Command Menu
    command_menu.eventHandler(window, event);
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
    {
        for (int i = 0; i < starship.size(); ++i)
        {
            if(comfortableBoundsCheck(mousePosWorldCoords, starship[i]) )
            {
                command_menu.setActive(true);
                selected = i;
                clicked_pos = mousePosWorldCoords;
            }
        }
    }
}

void Player::update(sf::RenderWindow &window, sf::Time deltaTime)
{
    command_menu.update(window, deltaTime);

    flagshipMovementControls(deltaTime);

    // Commands
    /*if(starship[selected]->getCommand() == Starship::Command::MOVETO)
    {
        starship[selected]->moveTo(clicked_pos, deltaTime);
    }*/

    // TODO: Should this be in gamescene?
    if(command_menu.getCommand() == CommandMenu::Command::MOVETO)
    {
        // activate MOVETO crosshair. Next click will reposition player ship.
        starship[selected]->moveTo({500, 500}, deltaTime);
    }
}

void Player::render(sf::RenderWindow &window)
{
    for (auto & ships : starship)
    {
        ships->render(window);
    }

    command_menu.render(window);
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

bool Player::comfortableBoundsCheck(sf::Vector2<float> mouse_vec, std::unique_ptr<Starship> &starship)
{
    auto offset = 10.0F;
    auto sprite_bounds = starship->getSpriteComponent().getSprite().getGlobalBounds();
    return (mouse_vec.x > sprite_bounds.left - offset &&
    mouse_vec.y > sprite_bounds.top - offset &&
    mouse_vec.x < sprite_bounds.left + sprite_bounds.width + offset &&
    mouse_vec.y < sprite_bounds.top + sprite_bounds.height + offset);
}

void Player::flagshipMovementControls(const sf::Time &deltaTime)
{
    auto& flagship = getShip()[getShip().size() - 1];
    auto& flagship_spr = flagship->getSpriteComponent();

    //Convert angle to radians
    double angleRADS = (3.1415926536/180)*(flagship_spr.getSprite().getRotation());

    // move ship in direction it is facing
    sf::Vector2f direction;
    direction.x = cos(angleRADS);
    direction.y = sin(angleRADS);

    float speed = 30.0F;

    if(key_state[sf::Keyboard::W])
    {
        speed *= 3.0F;
    }
    if(key_state[sf::Keyboard::A])
    {
        flagship_spr.getSprite().rotate(-65 * deltaTime.asSeconds());
    }
    if(key_state[sf::Keyboard::S])
    {
        speed /= 2.0F;
    }
    if(key_state[sf::Keyboard::D])
    {
        flagship_spr.getSprite().rotate(65 * deltaTime.asSeconds());
    }

    sf::Vector2f movement = direction * speed;
    flagship_spr.getSprite().move(movement * deltaTime.asSeconds());
}


