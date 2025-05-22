#include "Sprites/UI/Minimap.hpp"

Minimap::Minimap(float viewWidth, float viewHeight, float viewportLeft, float viewportTop, float viewportWidth, float viewportHeight, sf::View& gameplayView, sf::Color borderColour)
: _gameplayView(gameplayView)
{
    // Initialize the minimap view to the size of the level
    _minimapView.setSize(viewWidth, viewHeight);

    // Focus the view/camera on the centre point of the level
    _minimapView.setCenter(viewWidth / 2.0F, Constants::LEVEL_HEIGHT / 2.0F);

    // Position minimap at top middle of the window and set its size
    _minimapView.setViewport(sf::FloatRect(viewportLeft,viewportTop,viewportWidth,viewportHeight));

    _minimapBorder.setSize({Constants::WINDOW_WIDTH * viewportWidth, Constants::WINDOW_HEIGHT * viewportHeight});
    _minimapBorder.setOutlineThickness(1.0F);
    //_minimapBorder.setOutlineColor({128, 128, 128});
    _minimapBorder.setOutlineColor(borderColour);
    _minimapBorder.setFillColor(sf::Color::Transparent);

    _minimapGameplayBoundary.setSize({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT});
    _minimapGameplayBoundary.setOutlineThickness(5.0F);
    //_minimapGameplayBoundary.setOutlineColor(Chilli::Colour::GRAY);
    _minimapGameplayBoundary.setOutlineColor(borderColour);
    _minimapGameplayBoundary.setFillColor(sf::Color::Transparent);

    _minimapGameplayBoundaryText.setFont(Chilli::CustomFonts::GetBoldFont());
    _minimapGameplayBoundaryText.setString("Gameplay View");
    _minimapGameplayBoundaryText.setCharacterSize(56);
    _minimapGameplayBoundaryText.setFillColor(sf::Color::White);
    _minimapGameplayBoundaryText.setOutlineColor(sf::Color::Black);
}

void Minimap::Update(sf::RenderWindow& window, sf::Time deltatime)
{
    // NOTE: The following code NEEDS to be positioned relative to the gameplay view as they are elements viewed on the main gameplay view, NOT the minimap.
    // TODO: Perhaps a UI-specific view layer should be created to abstract the UI elements from the gameplay elements.
    _minimapGameplayBoundary.setPosition(_gameplayView.getCenter().x - _minimapGameplayBoundary.getSize().x / 2.0F, _gameplayView.getCenter().y - _minimapGameplayBoundary.getSize().y / 2.0F);
    _minimapGameplayBoundaryText.setPosition(_minimapGameplayBoundary.getPosition().x + 25.0F, _minimapGameplayBoundary.getPosition().y + 10.0F);
    //_minimapBorder.setPosition(_gameplayView.getCenter().x - _gameplayView.getSize().x / 4.0F, _gameplayView.getCenter().y - _gameplayView.getSize().y / 2.0F + 12.1F);
    _minimapBorder.setPosition(_gameplayView.getCenter().x - _gameplayView.getSize().x / 4.0F / Constants::Minimap::VIEWPORT_SCALE_FACTOR,
                               _gameplayView.getCenter().y - _gameplayView.getSize().y / 2.0F + 6.0F);
}

void Minimap::Render(sf::RenderWindow &window)
{
    window.draw(_minimapBorder);
}

void Minimap::RenderGameplayView(sf::RenderWindow &window)
{
    window.draw(_minimapGameplayBoundary);
    window.draw(_minimapGameplayBoundaryText);
}
