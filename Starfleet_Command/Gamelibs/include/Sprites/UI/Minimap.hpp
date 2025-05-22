#ifndef STARFLEET_COMMAND_MINIMAP_HPP
#define STARFLEET_COMMAND_MINIMAP_HPP
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Utility/Constants.hpp"
#include "Utility/CustomFonts.hpp"
#include "Utility/Colour.hpp"

class Minimap
{
public:
    Minimap(float viewWidth, float viewHeight, float viewportLeft, float viewportTop, float viewportWidth, float viewportHeight, sf::View& gameplayView, sf::Color borderColour);
    ~Minimap() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);
    void RenderGameplayView(sf::RenderWindow& window);
    const sf::View& GetView() const { return _minimapView; }

private:
    sf::View _minimapView{};
    sf::View& _gameplayView;
    sf::RectangleShape _minimapBorder;
    sf::RectangleShape _minimapGameplayBoundary;
    sf::Text _minimapGameplayBoundaryText;
};

#endif //STARFLEET_COMMAND_MINIMAP_HPP
