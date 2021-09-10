#ifndef STARFLEET_COMMAND_FLEET_HPP
#define STARFLEET_COMMAND_FLEET_HPP
#include <array>

class Fleet
{
 public:
    Fleet() = default;
    ~Fleet() = default;

    void setFleetSize(int size); // static?
    int getFleetSize() const;

    enum class ShipType {FIGHTER, REPAIR, DESTROYER, BATTLESHIP};
    void setNumOfShips(int count, ShipType shipType);
    const std::array<int, 4> &getNumOfShips() const;

private:
    // Ship ship
    static const int SHIP_CLASSES = 4;
    std::array<int, SHIP_CLASSES> ship_class{};
    int fleet_size = 0;
};

#endif //STARFLEET_COMMAND_FLEET_HPP
