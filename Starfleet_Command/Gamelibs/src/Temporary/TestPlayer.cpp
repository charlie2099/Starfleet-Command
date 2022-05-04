#include "Temporary/TestPlayer.hpp"

TestPlayer::TestPlayer()
{
    object = std::make_shared<Entity>();
    // Adds a component by calling our previously written template function.
    auto sprite = object->AddComponent<TestComponent>();
    sprite->loadSprite("Resources/Textures/starfleet_ship.png");
}

void TestPlayer::render(sf::RenderWindow &window)
{
    object->Render(window);
}
