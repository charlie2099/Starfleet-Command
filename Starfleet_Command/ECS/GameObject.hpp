#ifndef STARFLEET_COMMAND_GAMEOBJECT_HPP
#define STARFLEET_COMMAND_GAMEOBJECT_HPP
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Component.hpp"

/// credit: https://thatgamesguy.co.uk/cpp-game-dev-7/

class GameObject
{
 public:
    void Awake();
    void Start();
    void Update(sf::Time deltaTime);
    void LateUpdate(sf::Time deltaTime);
    void Render(sf::RenderWindow& window);

    template <typename T> std::shared_ptr<T> AddComponent()
    {
        /// This ensures that we only try to add a class the derives from Component.
        /// This is tested at compile time.
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        /// Check that we don't already have a component of this type.
        for (auto& existingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(existingComponent))
            {
                return std::dynamic_pointer_cast<T>(existingComponent);
            }
        }

        std::shared_ptr<T> newComponent = std::make_shared<T>(this);
        components.push_back(newComponent);

        return newComponent;
    };

    template <typename T> std::shared_ptr<T> GetComponent()
    {
        /// Check that we don't already have a component of this type.
        for (auto& existingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(existingComponent))
            {
                return std::dynamic_pointer_cast<T>(existingComponent);
            }
        }

        return nullptr;
    };

 private:
    std::vector<std::shared_ptr<Component>> components;
};

#endif //STARFLEET_COMMAND_GAMEOBJECT_HPP
