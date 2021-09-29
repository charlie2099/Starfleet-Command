#ifndef STARFLEET_COMMAND_OBJECT_HPP
#define STARFLEET_COMMAND_OBJECT_HPP
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Component.hpp"

class Object
{
 public:
    /// Awake is called when object created. Used to ensure required components are present.
    void awake();

    /// Start is called after Awake method. Used to initialise variables.
    void start();
    void update(sf::Time deltaTime);
    void lateUpdate(sf::Time deltaTime);
    void render(sf::RenderWindow& window);

    template <typename T> std::shared_ptr<T> addComponent()
    {
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

    template <typename T> std::shared_ptr<T> getComponent()
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

#endif //STARFLEET_COMMAND_OBJECT_HPP
