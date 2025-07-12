#include "EffectManager.hpp"

void EffectManager::Update(sf::RenderWindow &window, sf::Time &deltaTime)
{
    for (int i = 0; i < _activeEffects.size(); ++i)
    {
        _activeEffects[i]->Update(window, deltaTime);

        if(_activeEffects[i]->IsFinished())
        {
            _activeEffects.erase(_activeEffects.begin() + i);
        }
    }
}

void EffectManager::Render(sf::RenderWindow &window)
{
    for (int i = 0; i < _activeEffects.size(); ++i)
    {
        _activeEffects[i]->Render(window);
    }
}

void EffectManager::AddExplosion(sf::Vector2f position)
{
    auto explosion = std::make_unique<ExplosionEffect>(position);
    _activeEffects.push_back(std::move(explosion));
}
