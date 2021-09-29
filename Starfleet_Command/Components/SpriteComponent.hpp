#ifndef STARFLEET_COMMAND_SPRITECOMPONENT_HPP
#define STARFLEET_COMMAND_SPRITECOMPONENT_HPP
#include <SFML/Graphics.hpp>

class SpriteComponent
{
 public:
    SpriteComponent() = default;
    ~SpriteComponent() = default;

    /// General
    void render(sf::RenderWindow& renderWindow);

    /// Modifiers
    void loadSprite(const std::string& texture_filepath);
    void setPos(sf::Vector2<float> pos);

    /// Accessors
    sf::Sprite &getSprite();
    sf::Vector2<float> getPos();

 private:
    sf::Vector2<float> position {0, 0};
    sf::Texture texture_;
    sf::Sprite sprite;
};

#endif //STARFLEET_COMMAND_SPRITECOMPONENT_HPP
