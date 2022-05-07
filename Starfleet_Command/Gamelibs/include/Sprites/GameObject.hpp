#ifndef STARFLEET_COMMAND_GAMEOBJECT_HPP
#define STARFLEET_COMMAND_GAMEOBJECT_HPP
#include "Components/Component.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Components/AnimationComponent.hpp"
#include "Components/AudioComponent.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>

class GameObject
{
public:
    void EventHandler(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow &window, sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    Component* AddComponent(std::unique_ptr<Component> component);

    /*SpriteComponent& GetSpriteComponent() { return _spriteComponent; };
    HealthComponent& GetHealthComponent() { return _healthComponent; };
    PhysicsComponent& GetPhysicsComponent() { return _physicsComponent; };
    AnimationComponent& GetAnimationComponent() { return _animationComponent; };
    AudioComponent& GetAudioComponent() { return _audioComponent; };*/

private:
    std::vector<std::unique_ptr<Component>> components;
    //std::map<int, Component> components;

    /*SpriteComponent _spriteComponent;
    HealthComponent _healthComponent;
    PhysicsComponent _physicsComponent;
    AnimationComponent _animationComponent;
    AudioComponent _audioComponent;*/
};

#endif //STARFLEET_COMMAND_GAMEOBJECT_HPP