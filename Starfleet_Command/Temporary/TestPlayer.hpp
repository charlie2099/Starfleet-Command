#ifndef STARFLEET_COMMAND_TESTPLAYER_HPP
#define STARFLEET_COMMAND_TESTPLAYER_HPP
#include "../ECS/GameObject.hpp"
#include "TestComponent.hpp"

class TestPlayer
{
 public:
    TestPlayer();
    ~TestPlayer() = default;

    void render(sf::RenderWindow& window);

 private:
    std::shared_ptr<GameObject> object;
};

#endif //STARFLEET_COMMAND_TESTPLAYER_HPP
