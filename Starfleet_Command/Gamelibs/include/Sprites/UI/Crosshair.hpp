#ifndef STARFLEET_COMMAND_CROSSHAIR_HPP
#define STARFLEET_COMMAND_CROSSHAIR_HPP
#include "Components/SpriteComponent.hpp"
#include "Interfaces/IStarship.hpp"

class Crosshair
{
 public:
    Crosshair();
    ~Crosshair() = default;

    void render(sf::RenderWindow& window);

    void snapTo(std::unique_ptr<IStarship>& starship);
    void unSnap();

    /// Mutators
    void setColour(sf::Color colour);
    void sizeAdjust(std::unique_ptr<IStarship>& starship);
    void setVisibility(bool visible);

    /// Accessors
    std::unique_ptr<SpriteComponent>& getSprite();
    sf::Color& getColour();
    bool getVisibility() const;

 private:
    bool initTexture();

    std::unique_ptr<SpriteComponent> sprite;
    sf::Texture texture;
    sf::Color colour_ = sf::Color::Cyan;
    bool is_visible_ = false;
    bool in_bounds = false;
};

#endif //STARFLEET_COMMAND_CROSSHAIR_HPP
