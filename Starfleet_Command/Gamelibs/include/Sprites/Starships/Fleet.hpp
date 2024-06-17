#ifndef STARFLEET_COMMAND_FLEET_HPP
#define STARFLEET_COMMAND_FLEET_HPP
#include <array>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "StarshipFactory.hpp"

class Fleet
{
 public:
    Fleet() = default;
    ~Fleet() = default;

    struct Colour
    {
        int rgb_r;
        int rgb_g;
        int rgb_b;
    };

    /// Modifiers
    static void setFleetSize(int size);
    static void setFleetColourRGB(sf::Color colour); // Colour colour
    static void setNumOfShips(int count, StarshipFactory::SHIP_TYPE shipType);

    /// Accessors
    static int &getFleetSize();
    static Colour &getFleetColourRGB();
    static std::array<int, 4> &getNumOfShips();

private:
    static const int SHIP_CLASSES = 4;
    static std::array<int, SHIP_CLASSES> ship_class;
    static int fleet_size;
    static Colour fleet_colour;
};

#endif //STARFLEET_COMMAND_FLEET_HPP
