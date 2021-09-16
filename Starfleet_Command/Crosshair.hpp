#ifndef STARFLEET_COMMAND_CROSSHAIR_HPP
#define STARFLEET_COMMAND_CROSSHAIR_HPP
#include "SpriteComponent.hpp"
#include "Ships/Starship.hpp"

class Crosshair
{
 public:
    Crosshair();
    ~Crosshair() = default;

    void render(sf::RenderWindow& window);

    void snapTo(std::unique_ptr<Starship>& starship);
    void unSnap();

    /// Mutators
    void setColour(sf::Color colour);
    void setVisibility(bool visible);

    /// Accessors
    std::unique_ptr<SpriteComponent>& getSprite();
    bool getVisibility() const;


 private:
    bool initTexture();
    std::unique_ptr<SpriteComponent> sprite;
    sf::Texture texture;
    bool is_visible_ = false;
};

#endif //STARFLEET_COMMAND_CROSSHAIR_HPP
