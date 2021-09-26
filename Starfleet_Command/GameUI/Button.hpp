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
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    /// Modifiers
    void setActiveColour(sf::Color colour);

    /// Accessors
    SpriteComponent &getSpriteComponent();
    bool hoveredOver() const { return is_within_bounds; };

 private:
    SpriteComponent spriteComponent;
    sf::Color idle_colour;
    sf::Color active_colour;
    bool is_within_bounds = false;
};

#endif //STARFLEET_COMMAND_BUTTON_HPP
