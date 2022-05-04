#ifndef STARFLEET_COMMAND_TESTPLAYER_HPP
#define STARFLEET_COMMAND_TESTPLAYER_HPP
#include "Sprites/Entity.hpp"
#include "Temporary/TestComponent.hpp"

class TestPlayer
{
 public:
    TestPlayer();
    ~TestPlayer() = default;

    void render(sf::RenderWindow& window);

 private:
    std::shared_ptr<Entity> object;
};

#endif //STARFLEET_COMMAND_TESTPLAYER_HPP
