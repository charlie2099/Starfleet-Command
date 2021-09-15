#include "GameScene.hpp"

bool GameScene::init()
{
    initBackground();

    initPlayerStarships();

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
    for (auto & ships : starship)
    {
        ships->render(window);
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

void GameScene::initPlayerStarships()
{
    for (int i = 0; i < Fleet::getNumOfShips().size(); ++i)
    {
        for (int j = 0; j < Fleet::getNumOfShips()[i]; ++j)
        {
            starship.emplace_back(std::make_unique<Starship>(static_cast<Starship::Type>(i)));
        }
    }

    auto r = Fleet::getFleetColourRGB().rgb_r;
    auto g = Fleet::getFleetColourRGB().rgb_g;
    auto b = Fleet::getFleetColourRGB().rgb_b;
    for (int i = 0; i < Fleet::getFleetSize(); ++i)
    {
        starship[i]->getSpriteCompo().setPos({50, (i * 30.0F) + Constants::WINDOW_HEIGHT*0.1F });
        starship[i]->getSpriteCompo().getSprite().setColor(sf::Color(r, g, b));
    }
}

bool GameScene::comfortableBoundsCheck(sf::Vector2<float> mouse_vec, sf::FloatRect sprite_bounds)
{
    auto offset = 10.0F;
    return (mouse_vec.x > sprite_bounds.left - offset &&
    mouse_vec.y > sprite_bounds.top - offset &&
    mouse_vec.x < sprite_bounds.left + sprite_bounds.width + offset &&
    mouse_vec.y < sprite_bounds.top + sprite_bounds.height + offset);
}

