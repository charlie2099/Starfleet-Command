#ifndef STARFLEET_COMMAND_BUTTON_HPP
#define STARFLEET_COMMAND_BUTTON_HPP
#include <SFML/Graphics.hpp>
#include "../Components/SpriteComponent.hpp"

class Button
{
 public:
    Button() = default;
    explicit Button(const std::string& filepath);
    ~Button() = default;

    /// General
    void Update(sf::RenderWindow& window);
    void Render(sf::RenderWindow& window);

    /// Accessors
    SpriteComponent &GetSpriteComponent();
    bool IsHoveredOver() const { return is_within_bounds; };

 private:
    SpriteComponent spriteComponent;
    bool is_within_bounds = false;
};

#endif //STARFLEET_COMMAND_BUTTON_HPP
