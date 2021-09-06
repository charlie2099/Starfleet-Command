#include "ShipyardScene.hpp"

bool ShipyardScene::init()
{
    initBackground();
    initTitleText();
    initPanels();
    initMenuTitleIcon();

    std::cout << "Fighter TOTAL: [" << ship_count[0] << "]" << std::endl;
    std::cout << "Repair ship TOTAL: [" << ship_count[1] << "]" << std::endl;
    std::cout << "Battleship TOTAL: [" << ship_count[2] << "]" << std::endl;
    std::cout << "Destroyer TOTAL: [" << ship_count[3] << "]" << "\n" << std::endl;

    return true;
}

void ShipyardScene::eventHandler(sf::RenderWindow& window, sf::Event& event)
{
    for (auto & panel : panels)
    {
        panel.eventHandler(window, event);
    }

    for (int i = 0; i < panels.size(); ++i)
    {
        // Ship cards
        if(i < 4)
        {
            // If ship cards hovered over
            if(panels[i].isHoveredOver())
            {
                panels[i].setText(button_text[i], sf::Color::Cyan);
                panels[i].setPanelColour(sf::Color(20, 210, 242, 120));
            }
            else if(!panels[i].isHoveredOver())
            {
                panels[i].setText(button_text[i], sf::Color::White);
                panels[i].setPanelColour(sf::Color(20, 210, 242, 80));
            }

            // If ship cards clicked
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if(panels[i].isClicked())
                {
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        if(ship_count[i] < 5)
                        {
                            ship_count[i] +=1;
                        }
                        std::cout << "Fighter TOTAL: [" << ship_count[0] << "]" << std::endl;
                        std::cout << "Repair ship TOTAL: [" << ship_count[1] << "]" << std::endl;
                        std::cout << "Battleship TOTAL: [" << ship_count[2] << "]" << std::endl;
                        std::cout << "Destroyer TOTAL: [" << ship_count[3] << "]" << "\n" << std::endl;
                        panels[i].setPanelColour(sf::Color(255, 255, 255, 120));
                    }
                    else if(event.mouseButton.button == sf::Mouse::Right)
                    {
                        if(ship_count[i] > 0)
                        {
                            ship_count[i] -=1;
                        }
                        std::cout << "Fighter TOTAL: [" << ship_count[0] << "]" << std::endl;
                        std::cout << "Repair ship TOTAL: [" << ship_count[1] << "]" << std::endl;
                        std::cout << "Battleship TOTAL: [" << ship_count[2] << "]" << std::endl;
                        std::cout << "Destroyer TOTAL: [" << ship_count[3] << "]" << "\n" << std::endl;
                        panels[i].setPanelColour(sf::Color(255, 0, 0, 80));
                    }
                }
            }
        }

        // Play button
        else
        {
            if(panels[i].isHoveredOver())
            {
                panels[i].setText("PLAY", sf::Color::Cyan);
                panels[i].setTextSize(40);
                ship_img_sprite.setColor(sf::Color(0, 178, 178, 100));
            }
            if(!panels[i].isHoveredOver())
            {
                panels[i].setText("PLAY", sf::Color::White);
                panels[i].setTextSize(35);
                ship_img_sprite.setColor(sf::Color(178, 178, 178, 150));
            }

            if(panels[i].isClicked())
            {
                setScene(Scene::ID::GAME);
            }
        }
    }
}

void ShipyardScene::update(sf::RenderWindow& window, sf::Time deltaTime)
{
    for (auto & panel : panels)
    {
        panel.update(window, deltaTime);
    }
}

void ShipyardScene::render(sf::RenderWindow& window)
{
    window.draw(background_sprite);
    window.draw(shipyard_title);
    window.draw(ship_img_sprite);
    for (auto & panel : panels)
    {
        panel.render(window);
    }
}

/// OTHER
bool ShipyardScene::initBackground()
{
    if (!background_texture.loadFromFile("images/space_background.jpg"))
    {
        return false;
    }
    background_sprite.setTexture(background_texture);

    return true;
}

bool ShipyardScene::initMenuTitleIcon()
{
    if (!ship_img_texture.loadFromFile("images/starfleet_ship_fighter.png"))
    {
        return false;
    }
    ship_img_sprite.setTexture(ship_img_texture);
    ship_img_sprite.setColor(sf::Color(178, 178, 178, 200));
    ship_img_sprite.setScale(0.4F, 0.4F);
    ship_img_sprite.setRotation(-8);
    ship_img_sprite.setPosition(panels[4].getTextPosition().x - 35, panels[4].getTextPosition().y - 32);

    return true;
}

void ShipyardScene::initTitleText()
{
    shipyard_title.setString("Shipyard");
    shipyard_title.setFillColor(sf::Color::Cyan);
    shipyard_title.setOutlineColor(sf::Color::Black);
    shipyard_title.setOutlineThickness(1);
    shipyard_title.setFont(getBoldFont());
    shipyard_title.setCharacterSize(60);
    shipyard_title.setPosition(utility.WINDOW_WIDTH * 0.5F - shipyard_title.getGlobalBounds().width / 2, utility.WINDOW_HEIGHT * 0.2F - shipyard_title.getGlobalBounds().height / 2);
}

void ShipyardScene::initPanels()
{
    button_text.at(0).append("Light Fighter");
    button_text.at(1).append("Repair Ship");
    button_text.at(2).append("Battleship");
    button_text.at(3).append("Destroyer");

    // Ship Card panels
    for (int i = 0; i < SHIP_CARDS; ++i)
    {
        panels[i].setText(button_text[i]);
        panels[i].setFont(Panel::TextFont::BOLD);
        panels[i].setTextSize(18);
        panels[i].setTextOffset(Panel::TextAlign::OFFSET, 20);
        panels[i].setSize(50, 175);
        panels[i].setPanelColour(sf::Color(20, 210, 242, 80));

        if(i < 1)
        {
            float position = utility.WINDOW_WIDTH * 0.18F;
            panels[i].setPosition(position, utility.WINDOW_HEIGHT * 0.4F);
        }

        else
        {
            // Position of the panel before it
            float spacing = (70 + panels[i - 1].getPanelPosition().x + panels[i - 1].getPanelSize().width);
            panels[i].setPosition(spacing, utility.WINDOW_HEIGHT * 0.4F);
        }
    }

    // Play Button panel
    for (int i = SHIP_CARDS; i < PLAY_BUTTON; ++i)
    {
        panels[i].setText("PLAY");
        panels[i].setTextSize(35);
        panels[i].setFont(Panel::TextFont::BOLD);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 0));
        panels[i].setPadding(20);
        panels[i].setPosition(utility.WINDOW_WIDTH * 0.9F - panels[i].getTextSize().width / 2, utility.WINDOW_HEIGHT * 0.85F -
        panels[i].getTextSize().height / 2);
    }
}


