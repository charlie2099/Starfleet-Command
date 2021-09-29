#include "GameScene.hpp"

bool GameScene::init()
{
    initBackground();
    initPlayerStarships();
    initView();
    initCrosshair();

    return true;
}

void GameScene::eventHandler(sf::RenderWindow& window, sf::Event& event)
{
    player.eventHandler(window, event);
}

void GameScene::update(sf::RenderWindow& window, sf::Time deltaTime)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    player.update(window, deltaTime);

    flagshipMovement(); // TODO: Refactor

    // Ship selecting with crosshair
    for (int i = 0; i < player.getShip().size(); ++i)
    {
        if(comfortableBoundsCheck(mousePosWorldCoords, player.getShip()[i]->getSpriteComponent().getSprite().getGlobalBounds()))
        {
            selected = i;
            crosshair.snapTo(player.getShip()[selected]);
        }
        // if crosshair is no longer in bounds of the SELECTED ship, unsnap it
        else if(!comfortableBoundsCheck(mousePosWorldCoords, player.getShip()[selected]->getSpriteComponent().getSprite().getGlobalBounds()))
        {
            crosshair.unSnap();
        }
    }
}

void GameScene::render(sf::RenderWindow& window)
{
    window.setView(player_view);
    window.draw(background_sprite);
    for (auto & ships : player.getShip())
    {
        ships->render(window);
    }
    crosshair.render(window);
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
            player.getShip().emplace_back(std::make_unique<Starship>(static_cast<Starship::Type>(i)));
        }
    }

    // Command ship which player controls
    player.getShip().emplace_back(std::make_unique<Starship>(Starship::Type::FLAGSHIP));
    static const unsigned int FLAGSHIP = player.getShip().size()-1;

    auto r = Fleet::getFleetColourRGB().rgb_r;
    auto g = Fleet::getFleetColourRGB().rgb_g;
    auto b = Fleet::getFleetColourRGB().rgb_b;
    for (int i = 0; i < player.getShip().size(); ++i)
    {
        player.getShip()[i]->getSpriteComponent().setPos({50, (i * 40.0F) + Constants::WINDOW_HEIGHT * 0.1F });
        player.getShip()[i]->getSpriteComponent().getSprite().setColor(sf::Color(r, g, b));
    }

    auto flagship = player.getShip()[FLAGSHIP]->getSpriteComponent();
    auto xpos = player.getShip()[0]->getSpriteComponent().getPos().x + flagship.getSprite().getGlobalBounds().width + 20;
    float ypos = Constants::WINDOW_HEIGHT/2 - flagship.getSprite().getGlobalBounds().height/2;
    player.getShip()[FLAGSHIP]->getSpriteComponent().setPos({xpos, ypos});

    //flagship.getSprite().setOrigin(flagship.getPos().x + flagship.getSprite().getLocalBounds().width/2,
                                   //flagship.getPos().y + flagship.getSprite().getLocalBounds().height/2);
}

void GameScene::initView()
{
    /// Reset View to default settings
    //view.setCenter(window.getDefaultView().getCenter());
    //view.setSize(window.getDefaultView().getSize());

    auto flagship = player.getShip()[player.getShip().size() - 1]->getSpriteComponent().getSprite();
    sf::Vector2f VIEW_SIZE = { Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT };
    sf::Vector2f WORLD_PERSPECTIVE = { Constants::WINDOW_WIDTH/2.0F, Constants::WINDOW_HEIGHT/2.0F };
    sf::Vector2f PLAYER_PERSPECTIVE = {flagship.getPosition().x + flagship.getGlobalBounds().width/2,
                                       flagship.getPosition().y + flagship.getGlobalBounds().height/2};
    player_view.setSize(VIEW_SIZE);
    player_view.setCenter(WORLD_PERSPECTIVE);
    //player_view.zoom(0.5F);
}

void GameScene::initCrosshair()
{
    auto r = Fleet::getFleetColourRGB().rgb_r;
    auto g = Fleet::getFleetColourRGB().rgb_g;
    auto b = Fleet::getFleetColourRGB().rgb_b;
    crosshair.setVisibility(true);
    crosshair.setColour(sf::Color(r, g, b));
}

bool GameScene::comfortableBoundsCheck(sf::Vector2<float> mouse_vec, sf::FloatRect sprite_bounds)
{
    auto offset = 10.0F;
    return (mouse_vec.x > sprite_bounds.left - offset &&
    mouse_vec.y > sprite_bounds.top - offset &&
    mouse_vec.x < sprite_bounds.left + sprite_bounds.width + offset &&
    mouse_vec.y < sprite_bounds.top + sprite_bounds.height + offset);
}

void GameScene::flagshipMovement()
{
    static const size_t FLAGSHIP = player.getShip().size() - 1;
    auto& flagship = player.getShip()[FLAGSHIP]->getSpriteComponent().getSprite();
    sf::Vector2f movement(20.0F, 0.f);
    //flagship.move(movement * deltaTime.asSeconds());

    sf::Vector2f PLAYER_PERSPECTIVE = {flagship.getPosition().x + flagship.getGlobalBounds().width/2,
                                       flagship.getPosition().y + flagship.getGlobalBounds().height/2};
    //player_view.setCenter(PLAYER_PERSPECTIVE);

}

