#ifndef STARFLEET_COMMAND_PLAYER_H
#define STARFLEET_COMMAND_PLAYER_H
#include "../Ships/Starship.hpp"

class Player
{
public:
    Player() = default;
    ~Player() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void CreateShip(Starship::Type type);

    std::vector<std::unique_ptr<Starship>> &GetShip();

private:
    std::vector<std::unique_ptr<Starship>> starship{};
};

#endif //STARFLEET_COMMAND_PLAYER_H