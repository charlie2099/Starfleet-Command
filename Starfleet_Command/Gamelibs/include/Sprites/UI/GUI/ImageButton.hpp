#ifndef STARFLEET_COMMAND_IMAGEBUTTON_HPP
#define STARFLEET_COMMAND_IMAGEBUTTON_HPP
#include <SFML/Graphics.hpp>
#include "Components/SpriteComponent.hpp"

class ImageButton
{
 public:
    explicit ImageButton(const std::string& filepath);
    ~ImageButton() = default;

    void EventHandler(sf::RenderWindow &window, sf::Event &event);
    void Update(sf::RenderWindow& window);
    void Render(sf::RenderWindow& window);

    void SetPos(sf::Vector2f pos);
    void SetScale(sf::Vector2f  scale);
    void SetColour(sf::Color colour);

    bool IsClicked() const { return _isClicked; }
    bool IsMouseOver() const { return _isMouseHoveredOver; }

    sf::Vector2f GetPos() { return _spriteComponent.GetPos(); }
    sf::Rect<float> GetBounds() { return _spriteComponent.GetSprite().getGlobalBounds(); }

 private:
    SpriteComponent _spriteComponent;
    sf::Color _colour;
    bool _isClicked = false;
    bool _isMouseHoveredOver = false;
};

#endif //STARFLEET_COMMAND_IMAGEBUTTON_HPP
