#ifndef STARFLEET_COMMAND_MINIMAP_HPP
#define STARFLEET_COMMAND_MINIMAP_HPP
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Utility/Constants.hpp"

class Minimap
{
public:
    Minimap(float viewWidth, float viewHeight, float viewportLeft, float viewportTop, float viewportWidth, float viewportHeight, sf::View& displayView);
    ~Minimap() = default;
    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);
    const sf::View& GetView() const { return _minimapView; }

private:
    void HandleMinimapZooming(const sf::RenderWindow &window, const sf::Event &event, const sf::Vector2i &mouse_pos);
    void HandleMinimapPanning(const sf::RenderWindow &window, const sf::Event &event, const sf::Vector2i &mouse_pos);
    void UpdateMinimapPanPosition(const sf::RenderWindow &window);
    void ResetMinimapView();
    sf::Vector2f ClampViewCentreBounds(const sf::Vector2f& proposedCenter) const;
    sf::View _minimapView{};
    sf::View& _displayView;
    sf::RectangleShape _minimapBorder;
    sf::Vector2i _initialMousePosition;
    sf::Vector2f _originalViewCenter;
    float _originalZoomLevel = 1.0f;
    float _currentZoomLevel = 1.0f;
    bool _canViewPan = false;
};

#endif //STARFLEET_COMMAND_MINIMAP_HPP
