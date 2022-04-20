#include <chrono>
#include "MenuScene.hpp"

bool MenuScene::Init()
{
    std::mt19937 generator = GetEngine();
    InitBackground();
    InitButtonPanels();
    InitLeaderboardPanel();
    InitTitlePanel();
    InitMenuTitleIcon();
    InitBackgroundShips(generator);

    return true;
}

void MenuScene::EventHandler(sf::RenderWindow& window, sf::Event& event)
{
    for (int i = 0; i < BUTTONS; ++i)
    {
        panels[i].eventHandler(window, event);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(panels[PLAY_BUTTON].isClicked())
        {
            SetScene(Scene::ID::GAME);
        }
        else if(panels[OPTIONS_BUTTON].isClicked())
        {
            SetScene(Scene::ID::OPTIONS);
        }
        else if(panels[EXIT_BUTTON].isClicked())
        {
            window.close();
        }
    }

    for (int i = 0; i < BUTTONS; ++i)
    {
        if(i < 2) // PLAY and OPTIONS button
            {
            if(panels[i].isHoveredOver())
            {
                //panels[i].setPanelColour(sf::Color(20, 210, 242, 60));
                panels[i].setPanelColour(sf::Color(153, 210, 242, 80));
                panels[i].setText(panels[i].getText().getString(), sf::Color(153, 210, 242, 255));
            }
            }
        else // EXIT button
        {
            panels[i].setPanelColour(sf::Color(242, 22, 22, 60));
            panels[i].setText(panels[i].getText().getString(), sf::Color::Red);
        }

        // All Buttons
        if(!panels[i].isHoveredOver())
        {
            panels[i].setPanelColour(sf::Color(178, 178, 178, 100));
            panels[i].setText(panels[i].getText().getString(), sf::Color::White);
        }
    }
}

void MenuScene::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    cursor.Update(window, deltaTime);

    for (int i = 0; i < BUTTONS; ++i)
    {
        panels[i].update(window);
    }

    for (int i = 0; i < starship.size(); ++i)
    {
        // Ally ships
        if(i < BACKGROUND_SHIPS/2)
        {
            sf::Vector2f movement(static_cast<float>(starship_speed_vec[i]), 0.f);
            starship[i]->GetSpriteComponent().getSprite().move(movement * deltaTime.asSeconds());
        }
        // Enemy ships
        if(i >= BACKGROUND_SHIPS/2)
        {
            sf::Vector2f movement(static_cast<float>(starship_speed_vec[i] *-1), 0.f);
            starship[i]->GetSpriteComponent().getSprite().move(movement * deltaTime.asSeconds());
        }

        if(starship[i]->GetSpriteComponent().getPos().x >= Constants::WINDOW_WIDTH)
        {
            starship[i]->GetSpriteComponent().setPos({0, starship[i]->GetSpriteComponent().getPos().y});
        }
        else if(starship[i]->GetSpriteComponent().getPos().x <= 0)
        {
            starship[i]->GetSpriteComponent().setPos({Constants::WINDOW_WIDTH, starship[i]->GetSpriteComponent().getPos().y});
        }
    }

    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
    {
        if(ComfortableBoundsCheck(mousePosWorldCoords, starship[i]->GetSpriteComponent().getSprite().getGlobalBounds()))
        {
            SELECTED_SHIP = i;
            crosshair.snapTo(starship[SELECTED_SHIP]);
            cursor.SetCursorType(Chilli::Cursor::Type::SELECTED, sf::Color::Cyan);
        }
        else if(!ComfortableBoundsCheck(mousePosWorldCoords,
                                        starship[SELECTED_SHIP]->GetSpriteComponent().getSprite().getGlobalBounds()))
        {
            crosshair.unSnap();
            cursor.SetCursorType(Chilli::Cursor::DEFAULT, sf::Color::White);
        }
    }
}

void MenuScene::Render(sf::RenderWindow& window)
{
    window.draw(background_sprite);
    for (auto & ship : starship)
    {
        ship->Render(window);
    }
    window.draw(menu_title_img_sprite);
    for (auto & panel : panels)
    {
        panel.render(window);
    }
    crosshair.render(window);
    //test_player.Render(window);
    cursor.Render(window);
}

/// OTHER
std::mt19937 MenuScene::GetEngine()
{
    std::random_device eng;
    std::mt19937 generator(eng());
    unsigned long int time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed(time);
    return generator;
}

bool MenuScene::InitBackground()
{
    /*if (!background_texture.loadFromFile("images/space_background.jpg"))
    {
        return false;
    }
    background_sprite.setTexture(background_texture);*/

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

    return true;
}

void MenuScene::InitButtonPanels()
{
    std::array<std::string, 3> button_text
    {
        "PLAY",
        "OPTIONS",
        "EXIT"
    };

    for (int i = 0; i < BUTTONS; ++i)
    {
        panels[i].setText(button_text[i]);
        panels[i].setTextSize(35);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 100));
        panels[i].setPosition(Constants::WINDOW_WIDTH * 0.185F, (Constants::WINDOW_HEIGHT * 0.57F) + static_cast<float>(i * 100));
    }
}

void MenuScene::InitLeaderboardPanel()
{
    for (int i = BUTTONS; i < LEADERBOARD; ++i)
    {
        panels[i].setText("HIGHSCORES");
        panels[i].setTextSize(35);
        panels[i].setTextOffset(Panel::TextAlign::OFFSET, 40);
        panels[i].setSize(120, 250);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 100));
        panels[i].setPosition(Constants::WINDOW_WIDTH * 0.56F, Constants::WINDOW_HEIGHT * 0.6F);
    }
}

void MenuScene::InitTitlePanel()
{
    for (int i = LEADERBOARD; i < TITLE_PANEL; ++i)
    {
        panels[i].setText("Starfleet Command", sf::Color(153, 210, 242));
        panels[i].setTextSize(85);
        panels[i].setFont(Panel::TextFont::BOLD);
        panels[i].setPanelColour(sf::Color(0, 0, 0, 0));
        panels[i].setPosition(Constants::WINDOW_WIDTH * 0.5F - panels[i].getTextSize().width / 2, Constants::WINDOW_HEIGHT * 0.22F);
    }
}

bool MenuScene::InitMenuTitleIcon()
{
    if (!menu_title_img_texture.loadFromFile("images/starfleet_ship_fighter.png"))
    {
        return false;
    }
    menu_title_img_sprite.setTexture(menu_title_img_texture);
    menu_title_img_sprite.setColor(sf::Color(153, 210, 242, 175));
    menu_title_img_sprite.setScale(0.35F, 0.35F);
    menu_title_img_sprite.setRotation(-8);
    menu_title_img_sprite.setPosition(panels[4].getTextPosition().x - 44, panels[4].getTextPosition().y - 54);

    return true;
}

void MenuScene::InitBackgroundShips(std::mt19937 &generator)
{
    CreateDistribution("Ship xpos", 0, Constants::WINDOW_WIDTH);
    CreateDistribution("Ship ypos", 45, 675);
    CreateDistribution("Ship class", 0, 3);
    CreateDistribution("Ship speed", 50, 250);

    for (int i = 0; i < BACKGROUND_SHIPS; ++i)
    {
        int rand_x = uint_distrib[0](generator);
        int rand_y = uint_distrib[1](generator);
        int rand_ship = uint_distrib[2](generator);
        int rand_speed = uint_distrib[3](generator);

        starship_speed_vec.emplace_back(int());
        starship_speed_vec[i] = rand_speed;
        starship.emplace_back(std::make_unique<Starship>(static_cast<Starship::Type>(rand_ship)));
        starship[i]->GetSpriteComponent().getSprite().setColor(sf::Color(153, 210, 242));
        starship[i]->GetSpriteComponent().setPos({static_cast<float>(rand_x), static_cast<float>(rand_y)});

        if(i >= BACKGROUND_SHIPS/2)
        {
            starship[i]->GetSpriteComponent().getSprite().setRotation(180);
            //starship[i]->GetSpriteComponent().getSprite().setColor(sf::Color(247, 85, 85));
            starship[i]->GetSpriteComponent().getSprite().setColor(sf::Color(91, 239, 170));
        }
    }
}

bool MenuScene::ComfortableBoundsCheck(sf::Vector2<float> mouse_vec, sf::FloatRect sprite_bounds)
{
    auto offset = 20.0F;
    return (mouse_vec.x > sprite_bounds.left - offset &&
    mouse_vec.y > sprite_bounds.top - offset &&
    mouse_vec.x < sprite_bounds.left + sprite_bounds.width + offset &&
    mouse_vec.y < sprite_bounds.top + sprite_bounds.height + offset);
}

void MenuScene::CreateDistribution(const std::string& name, int min, int max)
{
    std::uniform_int_distribution<int> instance{min, max};
    uint_distrib.emplace_back(instance);
}
