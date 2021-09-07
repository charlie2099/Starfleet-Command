#include "ShipyardScene.hpp"

bool ShipyardScene::init()
{
    initBackground();
    initTitleText();
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
    for (int i = 0; i < panels.size(); ++i)
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
            setScene(Scene::ID::GAME);
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
    // Play Button panel
    for (int i = 0; i < panels.size(); ++i)
    {
        panels[i].setText("PLAY");
        panels[i].setTextSize(35);
        panels[i].setFont(Panel::TextFont::BOLD);
        panels[i].setPanelColour(sf::Color(178, 178, 178, 0));
        panels[i].setPadding(20);
        panels[i].setPosition(utility.WINDOW_WIDTH * 0.9F - panels[i].getTextSize().width / 2, utility.WINDOW_HEIGHT * 0.85F - panels[i].getTextSize().height / 2);
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
    ship_img_sprite.setScale(0.4F, 0.4F);
    ship_img_sprite.setRotation(-8);
    ship_img_sprite.setPosition(panels[0].getTextPosition().x - 35, panels[0].getTextPosition().y - 32);

    return true;
}

void ShipyardScene::initShipCards()
{
    button_text.at(0).append("Light Fighter");
    button_text.at(1).append("Repair Ship");
    button_text.at(2).append("Destroyer");
    button_text.at(3).append("Battleship");

    std::array<int, 4> shipTypeInt{};

    for (int i = 0; i < ship_cards.size(); ++i)
    {
        ship_cards[i].getPanel().setText(button_text[i]);
        ship_cards[i].setPosition(500, 500);
        ship_cards[i].setCounterText(ship_count[i]);

        shipTypeInt[i] = i;
        ship_cards[i].setShipType(static_cast<ShipCard::ShipType>(shipTypeInt[i]));

        if(i < 1)
        {
            float position = utility.WINDOW_WIDTH * 0.18F;
            ship_cards[i].setPosition(position, utility.WINDOW_HEIGHT * 0.4F);
        }

        else
        {
            // Position of the panel before it
            float spacing = (70 + ship_cards[i - 1].getPanel().getPanelPosition().x + ship_cards[i - 1].getPanel().getPanelSize().width);
            ship_cards[i].setPosition(spacing, utility.WINDOW_HEIGHT * 0.4F);
        }
    }
}

void ShipyardScene::playButtonActive(int i)
{
    panels[i].setText("PLAY", sf::Color::Cyan);
    panels[i].setTextSize(40);
    ship_img_sprite.setColor(sf::Color(0, 178, 178, 100));
}

void ShipyardScene::playButtonInactive(int i)
{
    panels[i].setText("PLAY", sf::Color::White);
    panels[i].setTextSize(35);
    ship_img_sprite.setColor(sf::Color(178, 178, 178, 150));
}

void ShipyardScene::shipCardsActive(int i)
{
    ship_cards[i].getPanel().setText(button_text[i], sf::Color::Cyan);
    ship_cards[i].getPanel().setPanelColour(sf::Color(20, 210, 242, 120));
    ship_cards[i].getCounterText().setFillColor(sf::Color::Cyan);
    ship_cards[i].getImage().setColor(sf::Color::Cyan);
}

void ShipyardScene::shipCardsInactive(int i)
{
    ship_cards[i].getPanel().setText(button_text[i], sf::Color::White);
    ship_cards[i].getPanel().setPanelColour(sf::Color(20, 210, 242, 80));
    ship_cards[i].getCounterText().setFillColor(sf::Color::White);
    ship_cards[i].getImage().setColor(sf::Color::White);
}

void ShipyardScene::shipCardsLeftClicked(int i)
{
    if(ship_count[i] < 5)
    {
        ship_count[i] +=1;
    }
    ship_cards[i].setCounterText(ship_count[i]);
    ship_cards[i].getPanel().setPanelColour(sf::Color(255, 255, 255, 120));
}

void ShipyardScene::shipCardsRightClicked(int i)
{
    if(ship_count[i] > 0)
    {
        ship_count[i] -=1;
    }
    ship_cards[i].setCounterText(ship_count[i]);
    ship_cards[i].getPanel().setPanelColour(sf::Color(255, 0, 0, 80));
}

