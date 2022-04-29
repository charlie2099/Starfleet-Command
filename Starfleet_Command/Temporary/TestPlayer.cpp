#include "TestPlayer.hpp"

TestPlayer::TestPlayer()
{
    object = std::make_shared<GameObject>();
    // Adds a component by calling our previously written template function.
    auto sprite = object->AddComponent<TestComponent>();
    sprite->loadSprite("images/starfleet_ship.png");
}

void TestPlayer::render(sf::RenderWindow &window)
{
    object->Render(window);
}
