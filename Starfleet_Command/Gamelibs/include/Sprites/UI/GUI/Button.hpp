#ifndef STARFLEET_COMMAND_BUTTON_HPP
#define STARFLEET_COMMAND_BUTTON_HPP
#include <SFML/Graphics.hpp>
#include "Components/SpriteComponent.hpp"

class Button
{
 public:
    Button() = default;
    explicit Button(const std::string& filepath);
    ~Button() = default;

    /// General
    void Update(sf::RenderWindow& window);
    void Render(sf::RenderWindow& window);

    void SetPos(sf::Vector2f pos);
    void SetScale(sf::Vector2f  scale);
    void SetColour(sf::Color colour);
    bool IsCursorHoveredOver() const { return _isHoveredOver; }

    sf::Vector2f GetPos() { return _spriteComponent.GetPos(); }
    sf::FloatRect GetBounds() { return _spriteComponent.GetSprite().getGlobalBounds(); }

 private:
    SpriteComponent _spriteComponent;
    sf::Color _colour;
    bool _isHoveredOver = false;
};

#endif //STARFLEET_COMMAND_BUTTON_HPP
