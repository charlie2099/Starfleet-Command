#include "Sprites/UI/Effects/DamagePopUpEffect.hpp"

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
    _color = text.getFillColor();
    m_timePassed += 1.0f * deltaTime.asSeconds();
    //std::cout << "Time passed: " << m_timePassed << std::endl;

    float moveSpeed = 25.0f;
    text.setPosition(text.getPosition().x, text.getPosition().y - moveSpeed * deltaTime.asSeconds());

    if(_color.a > 0 /*&& m_timePassed > 3*/)
    {
        float disappearSpeed = 10;
        text.setFillColor(sf::Color(_color.r, _color.g, _color.b, _color.a - disappearSpeed * deltaTime.asSeconds()));
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
    if(!font.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Regular.ttf"))
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

void DamagePopUpEffect::SetColour(sf::Color color)
{
    text.setFillColor(color);
}

void DamagePopUpEffect::SetCharSize(int size)
{
    text.setCharacterSize(size);
    text.setStyle(sf::Text::Style::Bold);
}
