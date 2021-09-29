#include "TestPlayer.hpp"

TestPlayer::TestPlayer()
{
    object = std::make_shared<Object>();
    // Adds a component by calling our previously written template function.
    auto sprite = object->addComponent<TestComponent>();
    sprite->loadSprite("images/starfleet_ship.png");
}

void TestPlayer::render(sf::RenderWindow &window)
{
    object->render(window);
}
