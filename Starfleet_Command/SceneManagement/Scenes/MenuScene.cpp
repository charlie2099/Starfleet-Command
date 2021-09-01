#include <iostream>
#include "MenuScene.hpp"

bool MenuScene::init()
{
    initBackground();
    initMenuTitle();

    panel1.setText("PLAY");
    panel1.setPosition(500, 500);
    panel1.setPadding(50);

    return true;
}

void MenuScene::eventHandler(sf::RenderWindow& window, sf::Event& event)
{
    panel1.eventHandler(window, event);

    if(panel1.isClicked())
    {
        std::cout << "hello" << std::endl;
    }
    /*if(panel1.is_hovered_over())
    {
        panel1.setPanelColour(sf::Color::Cyan);
    }

    if(panel1.isPressed())
    {
        // CHANGE SCENE
    }*/

    /*auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
    const int PLAY = 0;
    const int OPTIONS = 1;
    const int EXIT = 2;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if(panel1.pressed)
        {
            setScene(Scene::ID::MODE_SELECT);
        }
    }*/
}

void MenuScene::update(sf::RenderWindow& window, sf::Time deltaTime)
{
    panel1.update(window, deltaTime);

    if(panel1.isHoveredOver())
    {
        panel1.setPanelColour(sf::Color::Blue);
    }

    if(!panel1.isHoveredOver())
    {
        panel1.setPanelColour(sf::Color::White);
    }
    //auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    //auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

    /*if(panel1.isHoveredOver())
    {
        panel1.setPanelColour(sf::Color::Blue);
    }

    if(!panel1.isHoveredOver())
    {
        panel1.setPanelColour(sf::Color::White);
    }*/
}

void MenuScene::render(sf::RenderWindow& window)
{
    window.draw(background_sprite);
    window.draw(panel);
    window.draw(menu_title_img_sprite);
    window.draw(menu_title);
    panel1.render(window);
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
    if (!panel_texture.loadFromFile("images/panel_image.png"))
    {
        return false;
    }
    panel.setTexture(&panel_texture);

    menu_title.setString("Starfleet Command");
    menu_title.setFont(getBoldFont());
    menu_title.setCharacterSize(70);
    menu_title.setFillColor(sf::Color::White);

    auto menu_title_xpos = utility.WINDOW_WIDTH*0.5F - menu_title.getGlobalBounds().width/2.0F;
    auto menu_title_ypos = utility.WINDOW_HEIGHT*0.2F;
    menu_title.setPosition(menu_title_xpos, menu_title_ypos);

    auto panel_offset = 75.0F;
    panel.setSize({menu_title.getGlobalBounds().width + panel_offset*2, menu_title.getGlobalBounds().height*5});
    panel.setPosition(menu_title.getPosition().x - panel_offset, (menu_title.getGlobalBounds().top + menu_title.getGlobalBounds().height/2) - panel.getGlobalBounds().height/2);

    if (!menu_title_img_texture.loadFromFile("images/starfleet_ship_fighter.png"))
    {
        return false;
    }
    menu_title_img_sprite.setTexture(menu_title_img_texture);
    menu_title_img_sprite.setColor(sf::Color(0, 255, 255, 100));
    menu_title_img_sprite.setScale(0.75F, 0.75F);
    menu_title_img_sprite.setRotation(-8);
    menu_title_img_sprite.setPosition(menu_title.getPosition().x - 60, menu_title.getPosition().y - 62);

    /// Create panel class and convert this over with a instance of the panel class

    return true;
}


