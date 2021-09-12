#include "GameScene.hpp"

bool GameScene::init()
{
    initBackground();

    static const int LIGHTFIGHTERS = 0;
    static const int REPAIR_SHIPS = 1;
    static const int DESTROYERS = 2;
    static const int BATTLESHIPS = 3;

    for (int i = 0; i < Fleet::getNumOfShips()[LIGHTFIGHTERS]; ++i)
    {
        light_fighter.emplace_back(std::make_unique<LightFighter>());
        light_fighter[i]->getSpriteComp().setPos({100, static_cast<float>(i * 100) + 100});
        //light_fighter[i]->getSpriteComp().getSprite().setColor(Fleet::getFleetColour());
        light_fighter[i]->getSpriteComp().getSprite().setColor(sf::Color::Yellow);
    }

    for (int i = 0; i < Fleet::getNumOfShips()[REPAIR_SHIPS]; ++i)
    {
        repair_ship.emplace_back(std::make_unique<RepairShip>());
        repair_ship[i]->getSpriteComp().setPos({200, static_cast<float>(i * 100) + 100});
    }

    for (int i = 0; i < Fleet::getNumOfShips()[DESTROYERS]; ++i)
    {
        destroyer_ship.emplace_back(std::make_unique<Destroyer>());
        destroyer_ship[i]->getSpriteComp().setPos({300, static_cast<float>(i * 100) + 100});
    }

    for (int i = 0; i < Fleet::getNumOfShips()[BATTLESHIPS]; ++i)
    {
        battleship_ship.emplace_back(std::make_unique<Battleship>());
        battleship_ship[i]->getSpriteComp().setPos({400, static_cast<float>(i * 100) + 100});
    }

    return true;
}

void GameScene::eventHandler(sf::RenderWindow& /*window*/, sf::Event& /*event*/)
{

}

void GameScene::update(sf::RenderWindow& /*window*/, sf::Time /*deltaTime*/)
{

}

void GameScene::render(sf::RenderWindow& window)
{
    window.draw(background_sprite);
    for (auto & fighter : light_fighter)
    {
        fighter->render(window);
    }
    for (auto & repair : repair_ship)
    {
        repair->render(window);
    }
    for (auto & destroyer : destroyer_ship)
    {
        destroyer->render(window);
    }
    for (auto & battleship : battleship_ship)
    {
        battleship->render(window);
    }
}

/// OTHER
bool GameScene::initBackground()
{
    if (!background_texture.loadFromFile("images/space_background.jpg"))
    {
        return false;
    }
    background_sprite.setTexture(background_texture);

    return true;
}

bool GameScene::comfortableBoundsCheck(sf::Vector2<float> mouse_vec, sf::FloatRect sprite_bounds)
{
    auto offset = 10.0F;
    return (mouse_vec.x > sprite_bounds.left - offset &&
    mouse_vec.y > sprite_bounds.top - offset &&
    mouse_vec.x < sprite_bounds.left + sprite_bounds.width + offset &&
    mouse_vec.y < sprite_bounds.top + sprite_bounds.height + offset);
}

