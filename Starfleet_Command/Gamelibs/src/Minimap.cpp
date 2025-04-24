#include "Minimap.hpp"

Minimap::Minimap(float viewWidth, float viewHeight, float viewportLeft, float viewportTop, float viewportWidth, float viewportHeight, sf::View& gameplayView)
: _gameplayView(gameplayView)
{
    // Initialize the minimap view to the size of the level
    _minimapView.setSize(viewWidth, viewHeight/3.2F);

    // Focus the view/camera on the centre point of the level
    _minimapView.setCenter(viewWidth / 2.0F, viewHeight / 2.0F);
    _originalViewCenter = _minimapView.getCenter();

    // Position minimap at top middle of the window and set its size
    _minimapView.setViewport(sf::FloatRect(viewportLeft,viewportTop,viewportWidth,viewportHeight));

    _minimapBorder.setSize({Constants::WINDOW_WIDTH * viewportWidth, Constants::WINDOW_HEIGHT * viewportHeight});
    _minimapBorder.setOutlineThickness(1.0F);
    _minimapBorder.setOutlineColor({128, 128, 128});
    _minimapBorder.setFillColor(sf::Color::Transparent);

    _minimapGameplayBoundary.setSize({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT});
    _minimapGameplayBoundary.setOutlineThickness(5.0F);
    _minimapGameplayBoundary.setOutlineColor(Chilli::Colour::GRAY);
    _minimapGameplayBoundary.setFillColor(sf::Color::Transparent);

    _minimapGameplayBoundaryText.setFont(Chilli::CustomFonts::GetBoldFont());
    _minimapGameplayBoundaryText.setString("Gameplay View");
    _minimapGameplayBoundaryText.setCharacterSize(56);
    _minimapGameplayBoundaryText.setFillColor(sf::Color::White);
    _minimapGameplayBoundaryText.setOutlineColor(sf::Color::Black);
}

void Minimap::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    /*auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto worldPositionOfMouse = window.mapPixelToCoords(mouse_pos, window.getView()); // Mouse position translated into world coordinates
    bool isMouseCursorOnMinimap = _minimapBorder.getGlobalBounds().contains(worldPositionOfMouse);

    if(isMouseCursorOnMinimap)
    {
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            HandleMinimapZooming(window, event, mouse_pos);
        }
        if (_currentZoomLevel < 1.0f)
        {
            HandleMinimapPanning(window, event, mouse_pos);
        }
    }
    else
    {
        ResetMinimapView();
    }*/
}

void Minimap::Update(sf::RenderWindow& window, sf::Time deltatime)
{
    _minimapGameplayBoundary.setPosition(_gameplayView.getCenter().x - _minimapGameplayBoundary.getSize().x / 2.0F, _gameplayView.getCenter().y - _minimapGameplayBoundary.getSize().y / 2.0F);
    _minimapGameplayBoundaryText.setPosition(_minimapGameplayBoundary.getPosition().x + 25.0F, _minimapGameplayBoundary.getPosition().y + 10.0F);
    _minimapBorder.setPosition(_gameplayView.getCenter().x - _gameplayView.getSize().x / 4.0F, _gameplayView.getCenter().y - _gameplayView.getSize().y / 2.0F + 12.1F);
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

void Minimap::HandleMinimapZooming(const sf::RenderWindow &window, const sf::Event &event, const sf::Vector2i &mouse_pos)
{
    float zoomFactor = (event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;
    float newZoomLevel = _currentZoomLevel * zoomFactor;
    bool isZoomLevelWithinConstraints = newZoomLevel >= 0.15f and newZoomLevel <= 1.0f; // MAX ZOOM | MIN ZOOM

    if (isZoomLevelWithinConstraints)
    {
        sf::Vector2f beforeZoom = window.mapPixelToCoords(mouse_pos, _minimapView);
        _minimapView.zoom(zoomFactor);
        _currentZoomLevel = newZoomLevel;
        sf::Vector2f afterZoom = window.mapPixelToCoords(mouse_pos, _minimapView);
        sf::Vector2f offset = beforeZoom - afterZoom;
        sf::Vector2f newCenter = _minimapView.getCenter() + offset;
        _minimapView.setCenter(ClampViewCentreBounds(newCenter));
    }
}

void Minimap::HandleMinimapPanning(const sf::RenderWindow &window, const sf::Event &event, const sf::Vector2i &mouse_pos)
{
    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
    {
        _canViewPan = true;
        _initialMousePosition = mouse_pos;
    }

    if (event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Left)
    {
        _canViewPan = false;
    }

    if (event.type == sf::Event::MouseMoved and _canViewPan)
    {
        UpdateMinimapPanPosition(window);
    }
}

void Minimap::UpdateMinimapPanPosition(const sf::RenderWindow &window)
{
    sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f delta = window.mapPixelToCoords(_initialMousePosition, _minimapView) -
                         window.mapPixelToCoords(currentMousePosition, _minimapView);

    sf::Vector2f newCenter = _minimapView.getCenter() + delta;
    _minimapView.setCenter(ClampViewCentreBounds(newCenter));
    _initialMousePosition = currentMousePosition;
}

sf::Vector2f Minimap::ClampViewCentreBounds(const sf::Vector2f& proposedCenter) const
{
    sf::FloatRect levelBounds(0, 0, Constants::LEVEL_WIDTH, Constants::LEVEL_HEIGHT); // Example level bounds
    sf::Vector2f viewSize = _minimapView.getSize();
    sf::Vector2f halfViewSize = viewSize / 2.0f;

    // Calculate the permissible bounds for the view center
    float minX = levelBounds.left + halfViewSize.x;
    float maxX = levelBounds.left + levelBounds.width - halfViewSize.x;
    float minY = levelBounds.top + halfViewSize.y;
    float maxY = levelBounds.top + levelBounds.height - halfViewSize.y;

    // Constrain the center within the permissible bounds
    float constrainedX = std::max(minX, std::min(proposedCenter.x, maxX));
    float constrainedY = std::max(minY, std::min(proposedCenter.y, maxY));

    return {constrainedX, constrainedY};
}

void Minimap::ResetMinimapView()
{
    _minimapView.setCenter(_originalViewCenter);
    float zoomAdjustment = _originalZoomLevel / _currentZoomLevel;
    _minimapView.setSize(_minimapView.getSize() * zoomAdjustment);
    _currentZoomLevel = _originalZoomLevel;
}

