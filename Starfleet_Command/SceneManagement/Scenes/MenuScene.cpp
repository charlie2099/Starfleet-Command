#include "MenuScene.hpp"

bool MenuScene::init()
{
    initBackground();

    button_text.at(0).append("PLAY");
    button_text.at(1).append("OPTIONS");
    button_text.at(2).append("EXIT");

    // Button panels
    for (int i = 0; i < BUTTONS; ++i)
    {
        panels[i].setText(button_text[i]);
        panels[i].setTextSize(35);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 100));
        panels[i].setPosition(utility.WINDOW_WIDTH * 0.185F, (utility.WINDOW_HEIGHT * 0.57F) + static_cast<float>(i * 100));
    }

    // Leaderboard panel
    for (int i = BUTTONS; i < LEADERBOARD; ++i)
    {
        panels[i].setText("LEADERBOARD");
        panels[i].setTextSize(35);
        panels[i].setTextOffset(Panel::TextAlign::OFFSET, 40);
        panels[i].setSize(120, 250);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 100));
        panels[i].setPosition(utility.WINDOW_WIDTH * 0.52F, utility.WINDOW_HEIGHT * 0.6F);
    }

    // Title panel
    for (int i = LEADERBOARD; i < TITLE_PANEL; ++i)
    {
        panels[i].setText("Starfleet Command", sf::Color::Cyan);
        panels[i].setTextSize(85);
        panels[i].setFont(Panel::TextFont::BOLD);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 0));
        panels[i].setPosition(utility.WINDOW_WIDTH * 0.5F - panels[i].getTextSize().width / 2, utility.WINDOW_HEIGHT * 0.22F);
    }

    initMenuTitleIcon();

    if (!ship_texture.loadFromFile("images/starfleet_ship_fighter.png"))
    {
        return false;
    }

    for (int i = 0; i < ship_sprites.size(); ++i)
    {
        ship_sprites[i].setTexture(ship_texture);
        ship_sprites[i].setColor(sf::Color::Cyan);
        ship_sprites[i].setScale(0.05F, 0.05F);
        ship_sprites[i].setRotation(0);
        ship_sprites[i].setPosition(50, static_cast<float >(i * 80) + 300);
    }
    ship_sprites[0].setPosition(20, ship_sprites[0].getPosition().y);
    ship_sprites[1].setPosition(180, ship_sprites[1].getPosition().y);
    ship_sprites[2].setPosition(-100, ship_sprites[2].getPosition().y);
    ship_sprites[3].setPosition(120, ship_sprites[3].getPosition().y);
    ship_sprites[4].setPosition(0, ship_sprites[4].getPosition().y);

    if (!crosshairs_texture.loadFromFile("images/starfleet_selection_crosshairs.png"))
    {
        return false;
    }
    crosshairs_sprite.setTexture(crosshairs_texture);
    crosshairs_sprite.setColor(sf::Color::Transparent);
    crosshairs_sprite.setScale(0.35F, 0.35F);

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
        if(panels[0].isClicked())
        {
            setScene(Scene::ID::SHIPYARD);
        }
        else if(panels[1].isClicked())
        {
            std::cout << "options" << std::endl;
        }
        else if(panels[2].isClicked())
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
                panels[i].setText(button_text[i], sf::Color::Cyan);
            }
        }
        else // EXIT button
        {
            panels[i].setPanelColour(sf::Color(242, 22, 22, 60));
            panels[i].setText(button_text[i], sf::Color::Red);
        }

        if(!panels[i].isHoveredOver())
        {
            panels[i].setPanelColour(sf::Color(178, 178, 178, 100));
            panels[i].setText(button_text[i], sf::Color::White);
        }
    }
}

void MenuScene::update(sf::RenderWindow& window, sf::Time deltaTime)
{
    for (int i = 0; i < BUTTONS; ++i)
    {
        panels[i].update(window, deltaTime);
    }

    sf::Vector2f movement(0.f, 0.f);
    movement.x += 100.0F;
    for (auto & ship_sprite : ship_sprites)
    {
        ship_sprite.move(movement * deltaTime.asSeconds());

        if(ship_sprite.getPosition().x >= utility.WINDOW_WIDTH)
        {
            ship_sprite.setPosition(0, ship_sprite.getPosition().y);
        }
    }

    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    crosshairs_sprite.setColor(sf::Color::Transparent);

    for (int i = 0; i < ship_sprites.size(); ++i)
    {
        if(comfortableBoundsCheck(translated_pos, ship_sprites[i].getGlobalBounds()))
        {
            ship_sprites[i].setColor(sf::Color::White);
            crosshairs_sprite.setColor(sf::Color::Cyan);
            auto crosshairs_xpos = ship_sprites[i].getPosition().x + ship_sprites[i].getGlobalBounds().width/2 - crosshairs_sprite.getGlobalBounds().width/2;
            auto crosshairs_ypos = ship_sprites[i].getPosition().y + ship_sprites[i].getGlobalBounds().height/2 - crosshairs_sprite.getGlobalBounds().height/2;
            crosshairs_sprite.setPosition(crosshairs_xpos, crosshairs_ypos);
        }
        else if(!comfortableBoundsCheck(translated_pos, ship_sprites[i].getGlobalBounds()))
        {
            ship_sprites[i].setColor(sf::Color::Cyan);
        }
    }
}

void MenuScene::render(sf::RenderWindow& window)
{
    window.draw(background_sprite);
    window.draw(menu_title_img_sprite);
    for (const auto & ship_sprite : ship_sprites)
    {
        window.draw(ship_sprite);
    }
    for (auto & panel : panels)
    {
        panel.render(window);
    }
    window.draw(crosshairs_sprite);
}

/// OTHER
bool MenuScene::initBackground()
{
    if (!background_texture.loadFromFile("images/space_background.jpg"))
    {
        return false;
        /*return EXIT_FAILURE;*/
    }
    background_sprite.setTexture(background_texture);

    return true;
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

bool MenuScene::comfortableBoundsCheck(sf::Vector2<float> mouse_vec, sf::FloatRect sprite_bounds)
{
    auto offset = 20.0F;
    return (mouse_vec.x > sprite_bounds.left - offset &&
    mouse_vec.y > sprite_bounds.top - offset &&
    mouse_vec.x < sprite_bounds.left + sprite_bounds.width + offset &&
    mouse_vec.y < sprite_bounds.top + sprite_bounds.height + offset);
}
