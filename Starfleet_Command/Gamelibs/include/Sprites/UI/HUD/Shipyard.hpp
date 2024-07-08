#ifndef STARFLEET_COMMAND_HUD_HPP
#define STARFLEET_COMMAND_HUD_HPP
#include "Components/SpriteComponent.hpp"

class Shipyard
{
public:
    Shipyard();
    ~Shipyard() = default;
    void Update(sf::RenderWindow& window, sf::Time time);
    void Render(sf::RenderWindow& window);

    void SetPosition(sf::Vector2<float> pos);
    void SetTrainingSpeed(float speed);
    void SetTrainingStatus(bool status);
    void SetTrainingCompletedStatus(bool status);
    void SetDeployText(const std::string& text);

    SpriteComponent& GetSpriteComponent() { return _spriteComponent; };
    float GetTrainingSpeed() const { return _trainingSpeed; };
    bool IsTraining() const { return _isTraining; };
    bool IsTrainingComplete() const { return _trainingIsComplete; };

private:
    SpriteComponent _spriteComponent;
    SpriteComponent _spriteComponent2;
    sf::Font _font;
    sf::Text _deployText;
    sf::Vector2f _position;
    float _trainingSpeed = 0.2f;
    bool _isTraining = false;
    bool _trainingIsComplete = false;
};

#endif //STARFLEET_COMMAND_HUD_HPP
