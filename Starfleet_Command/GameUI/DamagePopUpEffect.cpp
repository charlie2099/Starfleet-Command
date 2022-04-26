#include "DamagePopUpEffect.hpp"

DamagePopUpEffect::DamagePopUpEffect(int damage, sf::Vector2f pos)
{
    InitFont();
    text.setString(std::to_string(damage));
    text.setFont(font);
    text.setCharacterSize(12.5f);

    generator = GetEngine();
    std::uniform_int_distribution<int> dist_x {static_cast<int>(pos.x-30),static_cast<int>(pos.x+30)};
    int rand_xPos = dist_x(generator);
    text.setPosition(rand_xPos, pos.y);
}

void DamagePopUpEffect::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    float moveSpeed = 100.0f;
    text.setPosition(text.getPosition().x, text.getPosition().y - moveSpeed * deltaTime.asSeconds());

    if(text.getFillColor().a > 0)
    {
        float disappearSpeed = 300.0f;
        text.setFillColor(sf::Color(255, 255, 255, text.getFillColor().a - disappearSpeed * deltaTime.asSeconds()));
    }
    else
    {
        _isFaded = true;
    }
}

void DamagePopUpEffect::Render(sf::RenderWindow &window)
{
    window.draw(text);
}

bool DamagePopUpEffect::InitFont()
{
    if(!font.loadFromFile("fonts/Orbitron/Orbitron-Regular.ttf"))
    {
        return false;
    }

    return true;
}

std::mt19937 DamagePopUpEffect::GetEngine()
{
    std::random_device eng;
    std::mt19937 generator(eng());
    unsigned long int time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    generator.seed(time);
    return generator;
}
