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

    bool IsCursorHoveredOver() const { return _isHoveredOver; }

    void SetPos(sf::Vector2f  pos);
    void SetColour(sf::Color colour);
    void SetSize(sf::Vector2f  size);

    sf::Vector2f GetPos();
    float GetCentreYPos();
    sf::Vector2f GetSize();

private:
    sf::RectangleShape laneRect;
    bool _isHoveredOver = false;
};

#endif //STARFLEET_COMMAND_SPACELANE_HPP
