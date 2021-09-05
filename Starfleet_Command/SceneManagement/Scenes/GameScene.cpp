#include "GameScene.hpp"

bool GameScene::init()
{
    initBackground();

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

