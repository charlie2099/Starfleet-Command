#ifndef STARFLEET_COMMAND_FLEET_HPP
#define STARFLEET_COMMAND_FLEET_HPP
#include <array>
#include <iostream>
#include <SFML/Graphics/Color.hpp>

class Fleet
{
 public:
    Fleet();
    ~Fleet() = default;

    enum class ShipType {FIGHTER, REPAIR, DESTROYER, BATTLESHIP};
    //enum class Colour {CYAN, RED, GREEN, YELLOW};

    /// Mutator Functions
    static void setFleetSize(int size);
    //static void setFleetColour(sf::Color& colour);
    static void setNumOfShips(int count, ShipType shipType);

    /// Accessor Functions
    static int &getFleetSize();
    //static sf::Color &getFleetColour();
    static std::array<int, 4> &getNumOfShips();

private:
    static const int SHIP_CLASSES = 4;
    static std::array<int, SHIP_CLASSES> ship_class;
    static int fleet_size;
    //static Colour ship_colour;
    //static sf::Color fleet_colour;
};

#endif //STARFLEET_COMMAND_FLEET_HPP
