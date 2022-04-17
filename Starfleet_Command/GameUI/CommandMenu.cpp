#include "CommandMenu.hpp"

CommandMenu::CommandMenu()
{
    panel.setText("Command Control");
    panel.setTextSize(22);
    panel.setTextOffset(Panel::TextAlign::OFFSET, 20);
    panel.setSize(100, 150);
    panel.setPanelColour(sf::Color(94,94,94, 200));
    auto offsetX = panel.getTextPosition().x - panel.getPanelPosition().x;
    auto offsetY = panel.getTextPosition().y - panel.getPanelPosition().y;
    auto xpos = Constants::WINDOW_WIDTH * 0.0F + offsetX;
    auto ypos = Constants::WINDOW_HEIGHT - panel.getPanelSize().height + offsetY;
    panel.setPosition(xpos, ypos);

    button[0] = std::make_unique<Button>("images/attack_button.png");
    button[0]->getSpriteComponent().getSprite().setScale(0.5F, 0.5F);
    button[0]->setActiveColour(predef_colours.LIGHTBLUE);
    float button_width = button[0]->getSpriteComponent().getSprite().getGlobalBounds().width/2;
    float button_height = button[0]->getSpriteComponent().getSprite().getGlobalBounds().height/2;
    float button_xpos = panel.getPanelPosition().x + button_width;
    float button_ypos = panel.getPanelPosition().y + panel.getPanelSize().height/2 - button_height;
    button[0]->getSpriteComponent().getSprite().setPosition(button_xpos, button_ypos);
}

void CommandMenu::eventHandler(sf::RenderWindow &window, sf::Event &event)
{
    panel.eventHandler(window, event);

    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        static const int MOVETO = 0;
        if(button[MOVETO]->hoveredOver())
        {
            command = Command::MOVETO;
        }
        else
        {
            command = Command::NONE;
            is_active_ = false;
        }
    }

    /*if(shoot button pressed)
    {
        command = Starship::Command::SHOOT;
    }
    else if(attack button pressed)
    {
        command = Starship::Command::ATTACK;
    }
    else if(defend button pressed)
    {
        command = Starship::Command::DEFEND;
    }
    else if(follow button pressed)
    {
        command = Starship::Command::FOLLOW;
    }
    else if(moveto button pressed)
    {
        command = Starship::Command::MOVETO;
    }
    else if(selfdestruct button pressed)
    {
        command = Starship::Command::SELF_DESTRUCT;
    }*/
}

void CommandMenu::update(sf::RenderWindow& window, sf::Time /*deltaTime*/)
{
    panel.update(window);
    button[0]->update(window);

    if(command == Command::SHOOT)
    {
        button[0]->getSpriteComponent().getSprite().setColor(sf::Color::Cyan);
    }
}

void CommandMenu::render(sf::RenderWindow &window)
{
    if(is_active_)
    {
        panel.render(window);
        button[0]->render(window);
    }
}

void CommandMenu::setActive(bool active)
{
    is_active_ = active;
}

bool CommandMenu::isActive() const
{
    is_active_;
}

