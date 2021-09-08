#ifndef STARFLEET_COMMAND_FLEET_HPP
#define STARFLEET_COMMAND_FLEET_HPP
#include <array>

class Fleet
{
 public:
    Fleet() = default;
    ~Fleet() = default;

    void setFleetSize(int size){}; // static?
    int getFleetSize() const { return fleet_size; };

    enum class ShipType {FIGHTER, REPAIR, DESTROYER, BATTLESHIP};
    void setNumOfShips(int count, ShipType shipType){};

    /*void setFighterCount(int count){};
    void setRepairShipCount(int count){};
    void setDestroyerCount(int count){};
    void setBattleshipCount(int count){};*/

 private:
    int fleet_size = 0;

    static const int SHIP_CLASSES = 4;
    std::array<int, SHIP_CLASSES> ship_count{};

    /*int fighter_count = 0;
    int repair_count = 0;
    int destroyer_count = 0;
    int battleship_count = 0;*/
};

#endif //STARFLEET_COMMAND_FLEET_HPP
