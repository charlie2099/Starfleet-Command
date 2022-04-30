#ifndef STARFLEET_COMMAND_NEWSPRITECOMPONENT_HPP
#define STARFLEET_COMMAND_NEWSPRITECOMPONENT_HPP
#include <SFML/Graphics.hpp>
#include "IComponent.hpp"

class NewSpriteComponent : public IComponent
{
public:
    void LoadSprite(const std::string& texture_filepath);
    sf::Sprite &GetSprite();

private:
    void EventHandler(sf::RenderWindow &window, sf::Event &event) override;
    void Update(sf::RenderWindow &window, sf::Time deltaTime) override;
    void Render(sf::RenderWindow &window) override;

    sf::Texture m_texture;
    sf::Sprite m_sprite;
};

#endif //STARFLEET_COMMAND_NEWSPRITECOMPONENT_HPP
