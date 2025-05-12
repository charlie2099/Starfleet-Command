#include "Sprites/UI/ParallaxBackground.hpp"

ParallaxBackground::ParallaxBackground(const std::string &backgroundImagePath, sf::Color backgroundColour, float parallaxWidth, float parallaxHeight, int numParallaxStars, sf::Color parallaxStarColour)
: _parallaxWidth(parallaxWidth), _parallaxHeight(parallaxHeight)
{
    _backgroundTexture.loadFromFile(backgroundImagePath);
    _backgroundTexture.setRepeated(true);
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setTextureRect(sf::IntRect(0, 0, _parallaxWidth * 2.0F, Constants::WINDOW_HEIGHT));
    _backgroundSprite.setPosition(0, _parallaxHeight/2.0F - Constants::WINDOW_HEIGHT/2.0F);
    _backgroundSprite.setColor(backgroundColour);

    for (int i = 0; i < numParallaxStars; ++i)
    {
        _parallaxStars.emplace_back();
        _parallaxStars[i].position = sf::Vector2f(std::rand() % (int)_parallaxWidth, std::rand() % (int)_parallaxHeight);
        _parallaxStars[i].speed = 0.1f + static_cast<float>(std::rand() % 100) / 100.0f; // Speed between 0.1 and 1.0
        _parallaxStars[i].size = 0.5f + static_cast<float>(std::rand() % 2); // Size between 1 and 3
        _parallaxStars[i].circleShape.setRadius(_parallaxStars[i].size);
        _parallaxStars[i].circleShape.setFillColor(parallaxStarColour);
    }
}

void ParallaxBackground::Update(sf::RenderWindow &window, sf::Time deltaTime)
{
    UpdateBackgroundLayerMovementAndPosition(deltaTime);
    UpdateBackgroundStarPositions(deltaTime);
}

void ParallaxBackground::Render(sf::RenderWindow& window)
{
    RenderBackground(window);
    RenderStars(window);
}

void ParallaxBackground::RenderBackground(sf::RenderWindow& window)
{
    window.draw(_backgroundSprite);
}

void ParallaxBackground::RenderStars(sf::RenderWindow& window)
{
    for (auto& star : _parallaxStars)
    {
        window.draw(star.circleShape);
    }
}

void ParallaxBackground::UpdateBackgroundLayerMovementAndPosition(const sf::Time &deltaTime)
{
    _backgroundSprite.move(-25.0F * deltaTime.asSeconds(), 0);

    if(_backgroundSprite.getPosition().x + _backgroundSprite.getGlobalBounds().width / 2.0F < 0)
    {
        _backgroundSprite.setPosition(0, _parallaxHeight / 2.0F - Constants::WINDOW_HEIGHT / 2.0F);
    }
}

void ParallaxBackground::UpdateBackgroundStarPositions(const sf::Time &deltaTime)
{
    for (auto& star : _parallaxStars)
    {
        star.position.x -= star.speed * 100.0F * deltaTime.asSeconds();
        star.circleShape.setPosition(star.position);
        if (star.position.x < 0)
        {
            star.position.x = _parallaxWidth;
            star.position.y = std::rand() % (int)_parallaxHeight;
        }
    }
}
