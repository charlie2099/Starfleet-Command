#ifndef STARFLEET_COMMAND_EFFECTMANAGER_HPP
#define STARFLEET_COMMAND_EFFECTMANAGER_HPP
#include <SFML/Graphics/RenderWindow.hpp>
#include "ExplosionEffect.hpp"
#include "IEffect.hpp"

class EffectManager
{
public:
    void Update(sf::RenderWindow &window, sf::Time &deltaTime);
    void Render(sf::RenderWindow& window);

    void AddExplosion(sf::Vector2f position);

private:
    std::vector<std::unique_ptr<IEffect>> _activeEffects;
};

#endif //STARFLEET_COMMAND_EFFECTMANAGER_HPP
