#ifndef STARFLEET_COMMAND_TESTPLAYER_HPP
#define STARFLEET_COMMAND_TESTPLAYER_HPP
#include "../ECS/Object.hpp"
#include "TestComponent.hpp"

class TestPlayer
{
 public:
    TestPlayer();
    ~TestPlayer() = default;

    void render(sf::RenderWindow& window);

 private:
    std::shared_ptr<Object> object;
};

#endif //STARFLEET_COMMAND_TESTPLAYER_HPP
