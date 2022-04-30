#ifndef STARFLEET_COMMAND_TESTCOMPONENT_HPP
#define STARFLEET_COMMAND_TESTCOMPONENT_HPP
#include <SFML/Graphics.hpp>
#include "../ECS/Component.hpp"

class TestComponent : public Component
{
 public:
    explicit TestComponent(Entity* object);

    /// General
    void Render(sf::RenderWindow& renderWindow) override;

    /// Mutators
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

#endif //STARFLEET_COMMAND_TESTCOMPONENT_HPP
