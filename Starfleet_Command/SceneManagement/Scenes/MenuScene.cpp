#include <chrono>
#include "MenuScene.hpp"

bool MenuScene::init()
{
    std::mt19937 generator = getEngine();
    initBackground();
    initButtonPanels();
    initLeaderboardPanel();
    initTitlePanel();
    initMenuTitleIcon();
    initBackgroundShips(generator);

    return true;
}

void MenuScene::eventHandler(sf::RenderWindow& window, sf::Event& event)
{
    for (int i = 0; i < BUTTONS; ++i)
    {
        panels[i].eventHandler(window, event);
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if(panels[PLAY_BUTTON].isClicked())
        {
            setScene(Scene::ID::SHIPYARD);
        }
        else if(panels[OPTIONS_BUTTON].isClicked())
        {
            setScene(Scene::ID::OPTIONS);
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
                panels[i].setPanelColour(sf::Color(20, 210, 242, 60));
                panels[i].setText(panels[i].getText().getString(), sf::Color::Cyan);
            }
            }
        else // EXIT button
        {
            panels[i].setPanelColour(sf::Color(242, 22, 22, 60));
            panels[i].setText(panels[i].getText().getString(), sf::Color::Red);
        }

        if(!panels[i].isHoveredOver())
        {
            panels[i].setPanelColour(sf::Color(178, 178, 178, 100));
            panels[i].setText(panels[i].getText().getString(), sf::Color::White);
        }
    }
}

void MenuScene::update(sf::RenderWindow& window, sf::Time deltaTime)
{
    for (int i = 0; i < BUTTONS; ++i)
    {
        panels[i].update(window, deltaTime);
    }

    for (int i = 0; i < starship.size(); ++i)
    {
        // Ally ships
        if(i < BACKGROUND_SHIPS/2)
        {
            sf::Vector2f movement(static_cast<float>(starship_speed_vec[i]), 0.f);
            starship[i]->getSpriteCompo().getSprite().move(movement * deltaTime.asSeconds());
        }
        // Enemy ships
        if(i >= BACKGROUND_SHIPS/2)
        {
            sf::Vector2f movement(static_cast<float>(starship_speed_vec[i] *-1), 0.f);
            starship[i]->getSpriteCompo().getSprite().move(movement * deltaTime.asSeconds());
        }

        if(starship[i]->getSpriteCompo().getPos().x >= Constants::WINDOW_WIDTH)
        {
            starship[i]->getSpriteCompo().setPos({0, starship[i]->getSpriteCompo().getPos().y});
        }
        else if(starship[i]->getSpriteCompo().getPos().x <= 0)
        {
            starship[i]->getSpriteCompo().setPos({Constants::WINDOW_WIDTH, starship[i]->getSpriteCompo().getPos().y});
        }
    }

    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto mousePosWorldCoords = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    for (int i = 0; i < BACKGROUND_SHIPS/2; ++i)
    {
        if(comfortableBoundsCheck(mousePosWorldCoords, starship[i]->getSpriteCompo().getSprite().getGlobalBounds()))
        {
            SELECTED_SHIP = i;
            crosshair.snapTo(starship[SELECTED_SHIP]);
        }
        else if(!comfortableBoundsCheck(mousePosWorldCoords, starship[SELECTED_SHIP]->getSpriteCompo().getSprite().getGlobalBounds()))
        {
            crosshair.unSnap();
        }
    }
}

void MenuScene::render(sf::RenderWindow& window)
{
    window.draw(background_sprite);
    for (auto & ship : starship)
    {
        ship->render(window);
    }
    window.draw(menu_title_img_sprite);
    for (auto & panel : panels)
    {
        panel.render(window);
    }
    crosshair.render(window);
}

/// OTHER

std::mt19937 MenuScene::getEngine()
{
    std::random_device eng;
    std::mt19937 generator(eng());
    unsigned long int time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed(time);
    return generator;
}

bool MenuScene::initBackground()
{
    if (!background_texture.loadFromFile("images/space_background.jpg"))
    {
        return false;
    }
    background_sprite.setTexture(background_texture);

    return true;
}

void MenuScene::initButtonPanels()
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

void MenuScene::initLeaderboardPanel()
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

void MenuScene::initTitlePanel()
{
    for (int i = LEADERBOARD; i < TITLE_PANEL; ++i)
    {
        panels[i].setText("Starfleet Command", sf::Color::Cyan);
        panels[i].setTextSize(85);
        panels[i].setFont(Panel::TextFont::BOLD);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 0));
        panels[i].setPosition(Constants::WINDOW_WIDTH * 0.5F - panels[i].getTextSize().width / 2, Constants::WINDOW_HEIGHT * 0.22F);
    }
}

bool MenuScene::initMenuTitleIcon()
{
    if (!menu_title_img_texture.loadFromFile("images/starfleet_ship_fighter.png"))
    {
        return false;
    }
    menu_title_img_sprite.setTexture(menu_title_img_texture);
    menu_title_img_sprite.setColor(sf::Color(0, 255, 255, 100));
    menu_title_img_sprite.setScale(0.75F, 0.75F);
    menu_title_img_sprite.setRotation(-8);
    menu_title_img_sprite.setPosition(panels[4].getTextPosition().x - 60, panels[4].getTextPosition().y - 50);

    return true;
}

void MenuScene::initBackgroundShips(std::mt19937 &generator)
{
    createDistribution("Ship xpos", 0, 1280);
    createDistribution("Ship ypos", 20, 720);
    createDistribution("Ship class", 0, 3);
    createDistribution("Ship speed", 50, 250);

    for (int i = 0; i < BACKGROUND_SHIPS; ++i)
    {
        int rand_x = uint_distrib[0](generator);
        int rand_y = uint_distrib[1](generator);
        int rand_ship = uint_distrib[2](generator);
        int rand_speed = uint_distrib[3](generator);

        starship_speed_vec.emplace_back(int());
        starship_speed_vec[i] = rand_speed;
        starship.emplace_back(std::make_unique<Starship>(static_cast<Starship::Type>(rand_ship)));
        starship[i]->getSpriteCompo().getSprite().setColor(sf::Color::Cyan);
        starship[i]->getSpriteCompo().setPos({static_cast<float>(rand_x), static_cast<float>(rand_y)});

        if(i >= BACKGROUND_SHIPS/2)
        {
            starship[i]->getSpriteCompo().getSprite().setRotation(180);
            starship[i]->getSpriteCompo().getSprite().setColor(sf::Color::Red);
        }
    }
}

bool MenuScene::comfortableBoundsCheck(sf::Vector2<float> mouse_vec, sf::FloatRect sprite_bounds)
{
    auto offset = 20.0F;
    return (mouse_vec.x > sprite_bounds.left - offset &&
    mouse_vec.y > sprite_bounds.top - offset &&
    mouse_vec.x < sprite_bounds.left + sprite_bounds.width + offset &&
    mouse_vec.y < sprite_bounds.top + sprite_bounds.height + offset);
}

void MenuScene::createDistribution(const std::string& name, int min, int max)
{
    std::uniform_int_distribution<int> instance{min, max};
    uint_distrib.emplace_back(instance);
}
