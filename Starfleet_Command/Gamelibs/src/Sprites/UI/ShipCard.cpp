#include "Sprites/UI/ShipCard.hpp"

ShipCard::ShipCard()
{
    panel.SetText("Ship");
    panel.SetFont(Panel::TextFont::BOLD);
    panel.SetTextSize(18);
    panel.SetTextOffset(Panel::TextAlign::OFFSET, 20);
    panel.SetSize(50, 175);
    panel.SetPanelColour(sf::Color(20, 210, 242, 80));

    loadFont();

    cost_text.setString(std::to_string(ship_cost));
    cost_text.setFont(font_regular);
    cost_text.setFillColor(sf::Color(153, 210, 242));
    cost_text.setCharacterSize(20);
    /*auto cost_text_x = panel.getPanelPosition().x * 0.75F;
    auto cost_text_y = panel.GetPanelPosition().y + panel.GetPanelSize().height * 0.8F;
    cost_text.SetPosition(cost_text_x, cost_text_y);*/

    counter_text.setString("x" + std::to_string(ship_count));
    counter_text.setFont(font_regular);
    counter_text.setCharacterSize(20);
    /*auto counter_text_x = panel.getPanelPosition().x + panel.getPanelSize().width * 0.75F;
    auto counter_text_y = panel.GetPanelPosition().y + panel.GetPanelSize().height * 0.8F;
    counter_text.SetPosition(counter_text_x, counter_text_y);*/

    //setShipType(ShipType::FIGHTER);
    //ship_sprite.setTexture(ship_texture);
    ship_sprite.scale(0.2F,0.2F);
    ship_sprite.setPosition(panel.GetPanelPosition().x, panel.GetPanelPosition().y);
}

void ShipCard::render(sf::RenderWindow& window)
{
    panel.Render(window);
    window.draw(cost_text);
    window.draw(counter_text);
    window.draw(ship_sprite);
}

void ShipCard::setShipCost(int cost)
{
    ship_cost = cost;
    cost_text.setString(std::to_string(ship_cost));
}

void ShipCard::setCounterText(int count)
{
    ship_count = count;
    counter_text.setString("x" + std::to_string(ship_count));
}

void ShipCard::setPosition(float x, float y)
{
    panel.SetPosition(x, y);

    auto cost_text_x = panel.GetPanelPosition().x + 30.0F;
    auto cost_text_y = panel.GetPanelPosition().y + panel.GetPanelSize().height * 0.8F;
    cost_text.setPosition(cost_text_x, cost_text_y);

    auto counter_text_x = panel.GetPanelPosition().x + panel.GetPanelSize().width * 0.75F;
    auto counter_text_y = panel.GetPanelPosition().y + panel.GetPanelSize().height * 0.8F;
    counter_text.setPosition(counter_text_x, counter_text_y);

    auto ship_sprite_x =
            panel.GetPanelPosition().x + panel.GetPanelSize().width / 2 - ship_sprite.getGlobalBounds().width / 2;
    auto ship_sprite_y =
            panel.GetPanelPosition().y + panel.GetPanelSize().height / 2 - ship_sprite.getGlobalBounds().height / 2;
    ship_sprite.setPosition(ship_sprite_x, ship_sprite_y);
}

Panel &ShipCard::getPanel()
{
    return panel;
}

bool ShipCard::loadFont()
{
    if(!font_regular.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Regular.ttf"))
    {
        return false;
    }
    return true;
}

void ShipCard::setShipType(Starship::Type shipType)
{
    switch (shipType)
    {
        case Starship::Type::FIGHTER:
            ship_texture.loadFromFile("Resources/Textures/starfleet_ship_fighter.png");
            break;
            case Starship::Type::REPAIR:
            ship_texture.loadFromFile("Resources/Textures/starfleet_ship_repair.png");
            break;
            case Starship::Type::DESTROYER:
            ship_texture.loadFromFile("Resources/Textures/starfleet_ship_destroyer.png");
            break;
            case Starship::Type::BATTLESHIP:
            ship_texture.loadFromFile("Resources/Textures/starfleet_ship_battleship.png");
            break;
        default:
            ship_texture.loadFromFile("Resources/Textures/starfleet_ship_fighter.png");
    }
    ship_sprite.scale(0.6F, 0.6F);
    ship_sprite.setTexture(ship_texture);
}

sf::Sprite &ShipCard::getImage()
{
    return ship_sprite;
}

int &ShipCard::getShipCost()
{
    return ship_cost;
}

sf::Text &ShipCard::getCounterText()
{
    return counter_text;
}

