#ifndef STARFLEET_COMMAND_SPRITECOMPONENT_HPP
#define STARFLEET_COMMAND_SPRITECOMPONENT_HPP
#include <SFML/Graphics.hpp>

class SpriteComponent
{
 public:
    SpriteComponent() = default;
    ~SpriteComponent() = default;

    /// General
    void Render(sf::RenderWindow& renderWindow);

    /// Modifiers
    void LoadSprite(const std::string& texture_filepath);
    void SetPos(sf::Vector2<float> pos);

    /// Accessors
    sf::Sprite &GetSprite();
    sf::Vector2<float> GetPos();

 private:
    sf::Vector2<float> position {0, 0};
    sf::Texture texture_;
    sf::Sprite sprite;
};

#endif //STARFLEET_COMMAND_SPRITECOMPONENT_HPP
