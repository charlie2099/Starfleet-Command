#include <iostream>
#include "MenuScene.hpp"

bool MenuScene::init()
{
    initBackground();
    initMenuTitle();

    button_text.at(0).append("PLAY");
    button_text.at(1).append("OPTIONS");
    button_text.at(2).append("EXIT");

    for (int i = 0; i < BUTTONS; ++i)
    {
        panels[i].setText(button_text[i]);
        //panels.setTextOffset(Panel::TextAlign::OFFSET, 40);
        panels[i].setPosition(utility.WINDOW_WIDTH * 0.2F, (utility.WINDOW_HEIGHT * 0.55F) + static_cast<float>(i * 100));
        panels[i].setPadding(50);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 100));
    }

    for (int i = BUTTONS; i < LEADERBOARD; ++i)
    {
        panels[i].setText("LEADERBOARD");
        panels[i].setTextOffset(Panel::TextAlign::OFFSET, 40);
        panels[i].setSize(80, 250);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 100));
        panels[i].setPosition(utility.WINDOW_WIDTH * 0.51F, utility.WINDOW_HEIGHT * 0.59F);
    }

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
            //setScene(Scene::ID::GAME);
        }
        else if(panels[2].isClicked())
        {
            window.close();
        }
    }

    for (int i = 0; i < BUTTONS; ++i)
    {
        if(panels[i].isHoveredOver())
        {
            panels[i].setPanelColour(sf::Color(153, 210, 242, 60));
            panels[i].setText(button_text[i], sf::Color::Cyan);
        }
        else if(!panels[i].isHoveredOver())
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
}

void MenuScene::render(sf::RenderWindow& window)
{
    window.draw(background_sprite);
    window.draw(title_box);
    window.draw(menu_title_img_sprite);
    window.draw(menu_title);
    for (auto & panel : panels)
    {
        panel.render(window);
    }
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

bool MenuScene::initMenuTitle()
{
    if (!title_box_texture.loadFromFile("images/panel_image.png"))
    {
        return false;
    }
    title_box.setTexture(&title_box_texture);

    menu_title.setString("Starfleet Command");
    menu_title.setFont(getBoldFont());
    menu_title.setCharacterSize(70);
    menu_title.setFillColor(sf::Color::White);

    auto menu_title_xpos = utility.WINDOW_WIDTH*0.5F - menu_title.getGlobalBounds().width/2.0F;
    auto menu_title_ypos = utility.WINDOW_HEIGHT*0.2F;
    menu_title.setPosition(menu_title_xpos, menu_title_ypos);

    auto panel_offset = 75.0F;
    title_box.setSize({menu_title.getGlobalBounds().width + panel_offset*2, menu_title.getGlobalBounds().height*5});
    title_box.setPosition(menu_title.getPosition().x - panel_offset, (menu_title.getGlobalBounds().top + menu_title.getGlobalBounds().height/2) - title_box.getGlobalBounds().height/2);

    if (!menu_title_img_texture.loadFromFile("images/starfleet_ship_fighter.png"))
    {
        return false;
    }
    menu_title_img_sprite.setTexture(menu_title_img_texture);
    menu_title_img_sprite.setColor(sf::Color(0, 255, 255, 100));
    menu_title_img_sprite.setScale(0.75F, 0.75F);
    menu_title_img_sprite.setRotation(-8);
    menu_title_img_sprite.setPosition(menu_title.getPosition().x - 60, menu_title.getPosition().y - 62);

    return true;
}


