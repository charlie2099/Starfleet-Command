#include "GameScene.hpp"

bool GameScene::init()
{
    initBackground();
    initPlayerStarships();

    /// Reset View to default settings
    //view.setCenter(window.getDefaultView().getCenter());
    //view.setSize(window.getDefaultView().getSize());

    auto flagship = starship[starship.size() - 1]->getSpriteComponent().getSprite();
    sf::Vector2f VIEW_SIZE = { Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT };
    sf::Vector2f WORLD_PERSPECTIVE = { Constants::WINDOW_WIDTH/2.0F, Constants::WINDOW_HEIGHT/2.0F };
    sf::Vector2f PLAYER_PERSPECTIVE = {flagship.getPosition().x + flagship.getGlobalBounds().width/2,
                                       flagship.getPosition().y + flagship.getGlobalBounds().height/2};
    player_view.setSize(VIEW_SIZE);
    player_view.setCenter(PLAYER_PERSPECTIVE);
    player_view.zoom(0.5F);

    return true;
}

void GameScene::eventHandler(sf::RenderWindow& /*window*/, sf::Event& /*event*/)
{

}

void GameScene::update(sf::RenderWindow& window, sf::Time deltaTime)
{
    static const size_t FLAGSHIP = starship.size()-1;
    auto& flagship = starship[FLAGSHIP]->getSpriteComponent().getSprite();
    sf::Vector2f movement(20.0F, 0.f);
    sf::Vector2f PLAYER_PERSPECTIVE = {flagship.getPosition().x + flagship.getGlobalBounds().width/2,
                                       flagship.getPosition().y + flagship.getGlobalBounds().height/2};
    player_view.setCenter(PLAYER_PERSPECTIVE);
    flagship.move(movement * deltaTime.asSeconds());

}

void GameScene::render(sf::RenderWindow& window)
{
    window.setView(player_view);
    window.draw(background_sprite);
    for (auto & ships : starship)
    {
        ships->render(window);
    }
}

/// OTHER
bool GameScene::initBackground()
{
    /*if (!background_texture.loadFromFile("images/background2.png"))
    {
        return false;
    }
    background_texture.setRepeated(true);
    background_sprite.setTexture(background_texture);
    background_sprite.scale(0.40F, 0.40F);
    auto bTexSizeX = static_cast<int>(background_texture.getSize().x);
    auto bTexSizeY = static_cast<int>(background_texture.getSize().y);
    background_sprite.setTextureRect(sf::IntRect(0, 0, bTexSizeX*3, bTexSizeY*3));*/

    if (!background_texture.loadFromFile("images/space_nebula.png")) // background2
    {
        return false;
    }
    background_texture.setRepeated(true);
    background_sprite.setTexture(background_texture);
    background_sprite.scale(0.2F, 0.2F);
    auto bTexSizeX = static_cast<int>(background_texture.getSize().x);
    auto bTexSizeY = static_cast<int>(background_texture.getSize().y);
    background_sprite.setTextureRect(sf::IntRect(0, 0, bTexSizeX*2, bTexSizeY*2));
    //background_sprite.setOrigin(background_sprite.getLocalBounds().width/2, background_sprite.getLocalBounds().height/2);

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

    // Command ship which players controls
    starship.emplace_back(std::make_unique<Starship>(Starship::Type::FLAGSHIP));
    static const unsigned int FLAGSHIP = starship.size()-1;

    auto r = Fleet::getFleetColourRGB().rgb_r;
    auto g = Fleet::getFleetColourRGB().rgb_g;
    auto b = Fleet::getFleetColourRGB().rgb_b;
    for (int i = 0; i < starship.size(); ++i)
    {
        starship[i]->getSpriteComponent().setPos({50, (i * 40.0F) + Constants::WINDOW_HEIGHT * 0.1F });
        starship[i]->getSpriteComponent().getSprite().setColor(sf::Color(r, g, b));
    }

    auto flagship = starship[FLAGSHIP]->getSpriteComponent();
    auto xpos = starship[0]->getSpriteComponent().getPos().x + flagship.getSprite().getGlobalBounds().width + 20;
    float ypos = Constants::WINDOW_HEIGHT/2 - flagship.getSprite().getGlobalBounds().height/2;
    starship[FLAGSHIP]->getSpriteComponent().setPos({xpos, ypos});

}

bool GameScene::comfortableBoundsCheck(sf::Vector2<float> mouse_vec, sf::FloatRect sprite_bounds)
{
    auto offset = 10.0F;
    return (mouse_vec.x > sprite_bounds.left - offset &&
    mouse_vec.y > sprite_bounds.top - offset &&
    mouse_vec.x < sprite_bounds.left + sprite_bounds.width + offset &&
    mouse_vec.y < sprite_bounds.top + sprite_bounds.height + offset);
}

