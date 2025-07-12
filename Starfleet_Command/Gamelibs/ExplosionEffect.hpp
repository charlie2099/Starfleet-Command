#ifndef STARFLEET_COMMAND_EXPLOSIONEFFECT_HPP
#define STARFLEET_COMMAND_EXPLOSIONEFFECT_HPP
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "IEffect.hpp"

class ExplosionEffect : public IEffect
{
public:
    explicit ExplosionEffect(sf::Vector2f position);
    void Update(sf::RenderWindow &window, sf::Time &deltaTime) override;
    void Render(sf::RenderWindow &window) override;

    bool IsFinished() override;

private:
    sf::Texture _explosionTexture;
    sf::Sprite _explosionEffect;
    float _timePassed = 0;
};

#endif //STARFLEET_COMMAND_EXPLOSIONEFFECT_HPP
