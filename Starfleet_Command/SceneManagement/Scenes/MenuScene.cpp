#include "MenuScene.hpp"

bool MenuScene::init()
{
    initBackground();

    button_text.at(0).append("PLAY");
    button_text.at(1).append("OPTIONS");
    button_text.at(2).append("EXIT");

    for (int i = 0; i < BUTTONS; ++i)
    {
        panels[i].setText(button_text[i]);
        panels[i].setTextSize(35);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 100));
        panels[i].setPosition(utility.WINDOW_WIDTH * 0.185F, (utility.WINDOW_HEIGHT * 0.57F) + static_cast<float>(i * 100));
    }

    for (int i = BUTTONS; i < LEADERBOARD; ++i)
    {
        panels[i].setText("LEADERBOARD");
        panels[i].setTextSize(35);
        panels[i].setTextOffset(Panel::TextAlign::OFFSET, 40);
        panels[i].setSize(120, 250);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 100));
        panels[i].setPosition(utility.WINDOW_WIDTH * 0.52F, utility.WINDOW_HEIGHT * 0.6F);
    }

    for (int i = LEADERBOARD; i < TITLE_PANEL; ++i)
    {
        panels[i].setText("Starfleet Command", sf::Color::Cyan);
        panels[i].setTextSize(85);
        panels[i].setFont(Panel::TextFont::BOLD);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 0));
        panels[i].setPosition(utility.WINDOW_WIDTH * 0.5F - panels[i].getSize().width/2, utility.WINDOW_HEIGHT * 0.22F);
    }

    initMenuTitleIcon();

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
            std::cout << "play" << std::endl;
            //setScene(Scene::ID::GAME);
        }
        else if(panels[1].isClicked())
        {
            std::cout << "options" << std::endl;
            //setScene(Scene::ID::GAME);
        }
        else if(panels[2].isClicked())
        {
            window.close();
        }
    }

    for (int i = 0; i < BUTTONS; ++i)
    {
        if(i < 2)
        {
            if(panels[i].isHoveredOver())
            {
                panels[i].setPanelColour(sf::Color(20, 210, 242, 60));
                panels[i].setText(button_text[i], sf::Color::Cyan);
            }
        }
        else
        {
            panels[i].setPanelColour(sf::Color(242, 22, 22, 60));
            panels[i].setText(button_text[i], sf::Color::Red);
        }

        if(!panels[i].isHoveredOver())
        {
            panels[i].setPanelColour(sf::Color(178, 178, 178, 120));
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
    window.draw(menu_title_img_sprite);
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
    menu_title_img_sprite.setPosition(panels[4].getPosition().x - 60, panels[4].getPosition().y - 69);

    return true;
}
