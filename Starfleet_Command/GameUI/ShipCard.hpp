#ifndef STARFLEET_COMMAND_SHIPCARD_HPP
#define STARFLEET_COMMAND_SHIPCARD_HPP
#include "Panel.hpp"

class ShipCard
{
 public:
    ShipCard();
    ~ShipCard() = default;

    void render(sf::RenderWindow& window);

    enum class ShipType
    {
        FIGHTER,
        REPAIR,
        DESTROYER,
        BATTLESHIP
    };
    void setShipType(ShipType shipType);
    void setCounterText(int count);
    void setPosition(float x, float y);
    Panel &getPanel();
    sf::Sprite &getImage();
    sf::Text &getCounterText();

 private:
    bool loadFont();

    Panel panel;
    sf::Texture ship_texture;
    sf::Sprite ship_sprite;
    sf::Font font_regular;
    sf::Text counter_text;
    int ship_count = 0;
};

#endif //STARFLEET_COMMAND_SHIPCARD_HPP
