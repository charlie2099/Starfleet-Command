#ifndef STARFLEET_COMMAND_FLEET_HPP
#define STARFLEET_COMMAND_FLEET_HPP
#include <array>
#include <iostream>

class Fleet
{
 public:
    Fleet();
    ~Fleet() = default;

    static void setFleetSize(int size); // static?
    static int getFleetSize() ;

    enum class ShipType {FIGHTER, REPAIR, DESTROYER, BATTLESHIP};

    /// Mutator Functions
    void setNumOfShips(int count, ShipType shipType);

    /// Accessor Functions
    const std::array<int, 4> &getNumOfShips() const;

private:
    static const int SHIP_CLASSES = 4;
    std::array<int, SHIP_CLASSES> ship_class{};

    static int fleet_size;
};

#endif //STARFLEET_COMMAND_FLEET_HPP
