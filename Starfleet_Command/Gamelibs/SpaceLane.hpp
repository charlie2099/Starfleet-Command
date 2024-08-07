#ifndef STARFLEET_COMMAND_SPACELANE_HPP
#define STARFLEET_COMMAND_SPACELANE_HPP
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class SpaceLane
{
public:
    SpaceLane() = default;
    ~SpaceLane() = default;

    bool Init();
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    void SetPos(sf::Vector2f  pos);
    void SetColour(sf::Color colour);

    sf::Vector2f GetPos();
    float GetCentreYPos();
    sf::Vector2f GetSize();

private:
    sf::RectangleShape laneRect;
};

#endif //STARFLEET_COMMAND_SPACELANE_HPP
