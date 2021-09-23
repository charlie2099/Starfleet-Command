#include "ShipyardScene.hpp"

bool ShipyardScene::init()
{
    initBackground();
    initTitleText();
    initCreditsText();
    initNotificationText();
    initPanels();
    initMenuTitleIcon();
    initShipCards();

    return true;
}

void ShipyardScene::eventHandler(sf::RenderWindow& window, sf::Event& event)
{
    for (auto & panel : panels)
    {
        panel.eventHandler(window, event);
    }

    // Play button
    for (int i = 0; i < PLAY_BUTTON; ++i)
    {
        if(panels[i].isHoveredOver())
        {
            playButtonActive(i);
        }
        else if(!panels[i].isHoveredOver())
        {
            playButtonInactive(i);
        }

        if(panels[i].isClicked())
        {
            if(Fleet::getFleetSize() > 0)
            {
                setScene(Scene::ID::GAME);
            }
            else
            {
                notification_text.setString("We need a ship commander!");
            }
        }
    }

    // Fleet Colour Panel
    for (int i = PLAY_BUTTON; i < FLEET_COLOUR; ++i)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if(panels[i].isClicked())
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if(active_colour < 3)
                    {
                        active_colour+= 1;
                    }
                }

                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    if(active_colour > 0)
                    {
                        active_colour-= 1;
                    }
                }
            }
        }
    }

    // Ship Cards
    for (int i = 0; i < ship_cards.size(); ++i)
    {
        ship_cards[i].getPanel().eventHandler(window, event);

        // If ship cards are hovered over
        if(ship_cards[i].getPanel().isHoveredOver())
        {
            shipCardsActive(i);
        }
        else if(!ship_cards[i].getPanel().isHoveredOver())
        {
            shipCardsInactive(i);
        }

        // If ship cards clicked
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if(ship_cards[i].getPanel().isClicked())
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    notification_text.setString("");
                    shipCardsLeftClicked(i);
                }

                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    shipCardsRightClicked(i);
                }
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
    for (auto & ship_card : ship_cards)
    {
        ship_card.getPanel().update(window, deltaTime);
    }

    // Fleet Colour Panel
    for (int i = PLAY_BUTTON; i < FLEET_COLOUR; ++i)
    {
        panels[i].setText("Fleet Colour: " + colours_text[active_colour]);
        panels[i].setPanelColour(colours_sf_light[active_colour]);
        Fleet::setFleetColourRGB(colours_sf[active_colour]);
    }

    // Fleet Size Panel
    for (int i = FLEET_COLOUR; i < FLEET_SIZE; ++i)
    {
        panels[i].setText("Fleet Size: " + std::to_string(Fleet::getFleetSize()));
        panels[i].setPosition(panels[1].getTextPosition().x + panels[1].getPanelSize().width + 10, panels[1].getTextPosition().y);
    }
}

void ShipyardScene::render(sf::RenderWindow& window)
{
    window.draw(background_sprite);
    window.draw(shipyard_title_text);
    window.draw(credits_text);
    window.draw(notification_text);
    window.draw(ship_img_sprite);
    for (auto & panel : panels)
    {
        panel.render(window);
    }
    for (auto & ship_card : ship_cards)
    {
        ship_card.render(window);
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

void ShipyardScene::initTitleText()
{
    shipyard_title_text.setString("Shipyard");
    shipyard_title_text.setFillColor(sf::Color::Cyan);
    shipyard_title_text.setOutlineColor(sf::Color::Black);
    shipyard_title_text.setOutlineThickness(1);
    shipyard_title_text.setFont(getBoldFont());
    shipyard_title_text.setCharacterSize(60);
    shipyard_title_text.setPosition(Constants::WINDOW_WIDTH * 0.5F - shipyard_title_text.getGlobalBounds().width / 2, Constants::WINDOW_HEIGHT * 0.2F - shipyard_title_text.getGlobalBounds().height / 2);
}

void ShipyardScene::initCreditsText()
{
    credits_text.setString("Credits: " + std::to_string(player.getCredits()));
    credits_text.setFillColor(sf::Color(153, 210, 242));
    credits_text.setOutlineColor(sf::Color::Black);
    credits_text.setOutlineThickness(1);
    credits_text.setFont(getRegularFont());
    credits_text.setCharacterSize(45);
    credits_text.setPosition(Constants::WINDOW_WIDTH * 0.05F, Constants::WINDOW_HEIGHT * 0.85F - credits_text.getGlobalBounds().height / 2);
}

void ShipyardScene::initNotificationText()
{
    notification_text.setString("");
    notification_text.setFillColor(sf::Color::Red);
    notification_text.setOutlineColor(sf::Color::Black);
    notification_text.setOutlineThickness(1);
    notification_text.setFont(getRegularFont());
    notification_text.setCharacterSize(25);
    notification_text.setPosition(Constants::WINDOW_WIDTH * 0.45F, Constants::WINDOW_HEIGHT * 0.85F);
}

void ShipyardScene::initPanels()
{
    // Play Button panel
    for (int i = 0; i < PLAY_BUTTON; ++i)
    {
        panels[i].setText("PLAY");
        panels[i].setTextSize(35);
        panels[i].setFont(Panel::TextFont::BOLD);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 0));
        panels[i].setPadding(20);
        panels[i].setPosition(Constants::WINDOW_WIDTH * 0.9F - panels[i].getTextSize().width / 2, Constants::WINDOW_HEIGHT * 0.85F - panels[i].getTextSize().height / 2);
    }

    // Fleet Colour Panel
    for (int i = PLAY_BUTTON; i < FLEET_COLOUR; ++i)
    {
        colours_text.at(0) = ("BLUE");
        colours_text.at(1) = ("RED");
        colours_text.at(2) = ("GREEN");
        colours_text.at(3) = ("YELLOW");

        colours_sf.at(0) = predefinedColours.LIGHTBLUE;
        colours_sf.at(1) = predefinedColours.LIGHTRED;
        colours_sf.at(2) = predefinedColours.LIGHTGREEN;
        colours_sf.at(3) = sf::Color::Yellow;

        predefinedColours.LIGHTBLUE.a = 120;
        predefinedColours.LIGHTRED.a = 120;
        predefinedColours.LIGHTGREEN.a = 120;
        sf::Color yellow = sf::Color(255, 255, 0, 120);
        colours_sf_light.at(0) = predefinedColours.LIGHTBLUE;
        colours_sf_light.at(1) = predefinedColours.LIGHTRED;
        colours_sf_light.at(2) = predefinedColours.LIGHTGREEN;
        colours_sf_light.at(3) = yellow;

        panels[i].setText("Fleet Colour: " + colours_text[active_colour]);
        panels[i].setFont(Panel::TextFont::BOLD);
        panels[i].setTextSize(18);
        panels[i].setPosition(Constants::WINDOW_WIDTH * 0.5F - panels[i].getPanelSize().width/2, Constants::WINDOW_HEIGHT * 0.745F - panels[i].getPanelSize().height/2);
    }

    // Fleet Size Panel
    for (int i = FLEET_COLOUR; i < FLEET_SIZE; ++i)
    {
        panels[i].setText("Fleet Size: " + std::to_string(0));
        panels[i].setFont(Panel::TextFont::BOLD);
        panels[i].setTextSize(18);
        panels[i].setPanelColour(sf::Color(20, 210, 242, 80));
        panels[i].setPosition(panels[1].getTextPosition().x + panels[1].getPanelSize().width + 10, panels[1].getTextPosition().y);
    }
}

bool ShipyardScene::initMenuTitleIcon()
{
    if (!ship_img_texture.loadFromFile("images/starfleet_ship_fighter.png"))
    {
        return false;
    }
    ship_img_sprite.setTexture(ship_img_texture);
    ship_img_sprite.setColor(sf::Color(178, 178, 178, 200));
    ship_img_sprite.setScale(0.185F, 0.185F);
    ship_img_sprite.setRotation(-8);
    ship_img_sprite.setPosition(panels[0].getTextPosition().x - 30, panels[0].getTextPosition().y - 34);

    return true;
}

void ShipyardScene::initShipCards()
{
    ship_names.at(0).append("Light Fighter");
    ship_names.at(1).append("Repair Ship");
    ship_names.at(2).append("Destroyer");
    ship_names.at(3).append("Battleship");

    for (int i = 0; i < ship_cards.size(); ++i)
    {
        ship_cards[i].getPanel().setText(ship_names[i]);
        ship_cards[i].setPosition(500, 500);
        ship_cards[i].setCounterText(Fleet::getNumOfShips()[i]);
        //ship_cards[i].setCounterText(ship_count[i]);
        ship_cards[i].setShipCost(50 + (i * 50));
        ship_cards[i].setShipType(static_cast<Starship::Type>(i));

        // Ship card position alignment
        if(i < 1)
        {
            float position = Constants::WINDOW_WIDTH * 0.18F;
            ship_cards[i].setPosition(position, Constants::WINDOW_HEIGHT * 0.4F);
        }
        else
        {
            // Position of the panel before it
            float spacing = (70 + ship_cards[i - 1].getPanel().getPanelPosition().x + ship_cards[i - 1].getPanel().getPanelSize().width);
            ship_cards[i].setPosition(spacing, Constants::WINDOW_HEIGHT * 0.4F);
        }
    }
}

void ShipyardScene::playButtonActive(int i)
{
    panels[i].setText("PLAY", sf::Color::Cyan); // getString()?
    panels[i].setTextSize(40);
    ship_img_sprite.setColor(sf::Color(0, 178, 178, 100));
}

void ShipyardScene::playButtonInactive(int i)
{
    panels[i].setText("PLAY", sf::Color::White); // getString()?
    panels[i].setTextSize(35);
    ship_img_sprite.setColor(sf::Color(178, 178, 178, 150));
}

void ShipyardScene::shipCardsActive(int i)
{
    ship_cards[i].getPanel().setText(ship_names[i], sf::Color::Cyan);
    ship_cards[i].getPanel().setPanelColour(sf::Color(20, 210, 242, 120));
    ship_cards[i].getCounterText().setFillColor(sf::Color::Cyan);
    ship_cards[i].getImage().setColor(colours_sf[active_colour]);
}

void ShipyardScene::shipCardsInactive(int i)
{
    ship_cards[i].getPanel().setText(ship_names[i], sf::Color::White);
    ship_cards[i].getPanel().setPanelColour(sf::Color(20, 210, 242, 80));
    ship_cards[i].getCounterText().setFillColor(sf::Color::White);
    ship_cards[i].getImage().setColor(sf::Color::White);
}

void ShipyardScene::shipCardsLeftClicked(int i)
{
    if(Fleet::getNumOfShips()[i] < 5 && player.getCredits() >= ship_cards[i].getShipCost())
    {
        Fleet::setNumOfShips(Fleet::getNumOfShips()[i] + 1, static_cast<Starship::Type>(i));

        int sum = 0;
        for (int elements : Fleet::getNumOfShips())
        {
            sum += elements;
        }
        Fleet::setFleetSize(sum);

        player.setCredits(player.getCredits() - ship_cards[i].getShipCost());
        credits_text.setString("Credits: " + std::to_string(player.getCredits()));

        ship_cards[i].setCounterText(Fleet::getNumOfShips()[i]);
    }
    ship_cards[i].getPanel().setPanelColour(sf::Color(255, 255, 255, 120));
}

void ShipyardScene::shipCardsRightClicked(int i)
{
    if(Fleet::getNumOfShips()[i] > 0)
    {
        Fleet::setNumOfShips(Fleet::getNumOfShips()[i] - 1, static_cast<Starship::Type>(i));

        int sum = 0;
        for (int elements : Fleet::getNumOfShips())
        {
            sum += elements;
        }
        Fleet::setFleetSize(sum);

        player.setCredits(player.getCredits() + ship_cards[i].getShipCost());
        credits_text.setString("Credits: " + std::to_string(player.getCredits()));
        ship_cards[i].setCounterText(Fleet::getNumOfShips()[i]);
    }
    ship_cards[i].getPanel().setPanelColour(sf::Color(255, 0, 0, 80));

}


