#ifndef STARFLEET_COMMAND_PARALLAXBACKGROUND_HPP
#define STARFLEET_COMMAND_PARALLAXBACKGROUND_HPP
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Utility/Constants.hpp"
#include <vector>

struct ParallaxStar
{
    sf::CircleShape circleShape;
    sf::Vector2f position;
    float speed{};
    float size{};
};

class ParallaxBackground
{
public:
    explicit ParallaxBackground(const std::string& backgroundImagePath, sf::Color backgroundColour, int numParallaxStars, sf::Color parallaxStarColour);
    ~ParallaxBackground() = default;

    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);
    void RenderBackground(sf::RenderWindow& window);
    void RenderStars(sf::RenderWindow& window);

private:
    void UpdateBackgroundLayerMovementAndPosition(const sf::Time &deltaTime);
    void UpdateBackgroundStarPositions(const sf::Time &deltaTime);
    sf::Texture _backgroundTexture;
    sf::Sprite _backgroundSprite;
    std::vector<ParallaxStar> _parallaxStars;
};

#endif //STARFLEET_COMMAND_PARALLAXBACKGROUND_HPP
