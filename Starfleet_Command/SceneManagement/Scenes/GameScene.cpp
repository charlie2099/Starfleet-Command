#include "GameScene.hpp"

bool GameScene::Init()
{
    initBackground();
    initPlayerStarships();
    initView();
    initCrosshair();

    // initCursor
    cursor_texture.loadFromFile("images/crosshair.png");
    cursor_sprite.setTexture(cursor_texture);
    cursor_sprite.scale(0.1F, 0.1F);

    return true;
}

void GameScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    player.EventHandler(window, event);

    // TODO: Move into player class?
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
    {
        auto flagship_pos = player.GetShip()[player.GetShip().size() - 1]->GetSpriteComponent().getPos();
        projectile.emplace_back(std::make_unique<Projectile>(Projectile::Type::LASER_BLUE, flagship_pos, mousePosWorldCoords));
    }
}

void GameScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    window.setMouseCursorVisible(false);

    player.Update(window, deltaTime);

    // TODO: Move into player class?
    for(auto& projectiles : projectile)
    {
        projectiles->update(window, deltaTime);
    }

    // Destroy projectiles if there are too many on screen
    if(projectile.size() > 10)
    {
        projectile.erase(projectile.begin());
    }

    // Destroy projectiles if off-screen
    for(int i = 0; i < projectile.size(); i++)
    {
        if(projectile[i]->getSprite().getSprite().getPosition().x < 0 ||
           projectile[i]->getSprite().getSprite().getPosition().x > Constants::WINDOW_WIDTH ||
           projectile[i]->getSprite().getSprite().getPosition().y < 0 ||
           projectile[i]->getSprite().getSprite().getPosition().y > Constants::WINDOW_HEIGHT)
        {
            projectile.erase(projectile.begin() + i);
        }
    }

    for (int i = 0; i < player.GetShip().size(); ++i)
    {
        // if mouse within bounds of any ship
        if(comfortableBoundsCheck(mousePosWorldCoords, player.GetShip()[i]))
        {
            selected = i;
            crosshair.sizeAdjust(player.GetShip()[selected]);
            crosshair.snapTo(player.GetShip()[selected]);
        }
        else if(!comfortableBoundsCheck(mousePosWorldCoords, player.GetShip()[selected]))
        {
            crosshair.unSnap();
        }
    }

    cursor_sprite.setPosition(mousePosWorldCoords.x - cursor_sprite.getGlobalBounds().width/2,
                              mousePosWorldCoords.y - cursor_sprite.getGlobalBounds().height/2);
}

void GameScene::Render(sf::RenderWindow& window)
{
    window.setView(player_view);
    window.draw(background_sprite);
    for (auto & ships : player.GetShip())
    {
        ships->Render(window);
    }
    for(auto& projectiles : projectile)
    {
        projectiles->render(window);
    }
    crosshair.render(window);
    window.draw(cursor_sprite);
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
            player.GetShip().emplace_back(std::make_unique<Starship>(static_cast<Starship::Type>(i)));
        }
    }

    // Command ship which player controls
    player.GetShip().emplace_back(std::make_unique<Starship>(Starship::Type::FLAGSHIP));
    static const unsigned int FLAGSHIP = player.GetShip().size() - 1;

    auto r = Fleet::getFleetColourRGB().rgb_r;
    auto g = Fleet::getFleetColourRGB().rgb_g;
    auto b = Fleet::getFleetColourRGB().rgb_b;
    for (int i = 0; i < player.GetShip().size(); ++i)
    {
        player.GetShip()[i]->GetSpriteComponent().setPos({50, (i * 40.0F) + Constants::WINDOW_HEIGHT * 0.1F });
        player.GetShip()[i]->GetSpriteComponent().getSprite().setColor(sf::Color(r, g, b));
    }

    auto flagship = player.GetShip()[FLAGSHIP]->GetSpriteComponent();
    auto xpos = player.GetShip()[0]->GetSpriteComponent().getPos().x + flagship.getSprite().getGlobalBounds().width + 20;
    float ypos = Constants::WINDOW_HEIGHT/2 - flagship.getSprite().getGlobalBounds().height/2;
    player.GetShip()[FLAGSHIP]->GetSpriteComponent().setPos({xpos, ypos});
}

void GameScene::initView()
{
    /// Reset View to default settings
    //view.setCenter(window.getDefaultView().getCenter());
    //view.setSize(window.getDefaultView().getSize());

    auto flagship = player.GetShip()[player.GetShip().size() - 1]->GetSpriteComponent().getSprite();
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

// template?
bool GameScene::comfortableBoundsCheck(sf::Vector2<float> mouse_vec, std::unique_ptr<Starship>& starship)
{
    auto offset = 10.0F;
    auto sprite_bounds = starship->GetSpriteComponent().getSprite().getGlobalBounds();
    return (mouse_vec.x > sprite_bounds.left - offset &&
    mouse_vec.y > sprite_bounds.top - offset &&
    mouse_vec.x < sprite_bounds.left + sprite_bounds.width + offset &&
    mouse_vec.y < sprite_bounds.top + sprite_bounds.height + offset);
}


