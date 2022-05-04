#ifndef STARFLEET_COMMAND_HUD_HPP
#define STARFLEET_COMMAND_HUD_HPP
#include "Components/SpriteComponent.hpp"
#include <iostream>

class HUD
{
public:
    HUD();
    ~HUD() = default;
    void Update(sf::RenderWindow& window, sf::Time time);
    void Render(sf::RenderWindow& window);

    void SetTrainingSpeed(float speed);
    void SetTrainingStatus(bool status);
    void SetTrainingCompletedStatus(bool status);

    SpriteComponent& GetSpriteComponent() { return spriteComponent; };
    float GetTrainingSpeed() const { return _trainingSpeed; };
    bool IsTraining() const { return _isTraining; };
    bool IsTrainingComplete() const { return _trainingIsComplete; };

private:
    SpriteComponent spriteComponent;
    SpriteComponent spriteComponent2;
    sf::Font font;
    sf::Text text;
    sf::Vector2f _position;
    float _trainingSpeed = 0.2f;
    bool _isTraining = false;
    bool _trainingIsComplete = false;
};

#endif //STARFLEET_COMMAND_HUD_HPP
