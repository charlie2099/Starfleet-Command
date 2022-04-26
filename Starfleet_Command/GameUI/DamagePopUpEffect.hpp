#ifndef STARFLEET_COMMAND_DAMAGEPOPUPEFFECT_HPP
#define STARFLEET_COMMAND_DAMAGEPOPUPEFFECT_HPP
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <random>
#include <chrono>
#include <iostream>

class DamagePopUpEffect
{
public:
    DamagePopUpEffect(int damage, sf::Vector2f pos);
    ~DamagePopUpEffect() = default;
    void Update(sf::RenderWindow& window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);
    bool IsFaded() const { return _isFaded; };

private:
    bool InitFont();
    static std::mt19937 GetEngine();
    std::mt19937 generator;
    sf::Text text;
    sf::Font font;
    bool _isFaded = false;
};

#endif //STARFLEET_COMMAND_DAMAGEPOPUPEFFECT_HPP
