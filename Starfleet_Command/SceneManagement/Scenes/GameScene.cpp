#include "GameScene.hpp"

bool GameScene::init()
{
    initBackground();

    std::cout << "Fleet size: " << Fleet::getFleetSize() << std::endl;

    spriteComponent.loadSprite("images/starfleet_ship.png");
    spriteComponent2.loadSprite("images/starfleet_ship_repair.png");

    spriteComponent.setPos(sf::Vector2<float>{500,0});
    spriteComponent2.setPos(sf::Vector2<float>{200,0});

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
    spriteComponent.render(window);
    spriteComponent2.render(window);
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

