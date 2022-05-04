#ifndef STARFLEET_COMMAND_GAMEOBJECT_HPP
#define STARFLEET_COMMAND_GAMEOBJECT_HPP
#include "../Interfaces/IComponent.hpp"
#include "../Components/NewSpriteComponent.hpp"
#include <memory>
#include <vector>
#include <typeindex>

class GameObject
{
public:
    GameObject() = default;

    virtual void EventHandler(sf::RenderWindow& window, sf::Event& event);
    virtual void Update(sf::RenderWindow &window, sf::Time deltaTime);
    virtual void Render(sf::RenderWindow& window);

    /// Not all GameObjects may contain a sprite or physics
    //void AddComponent(const std::shared_ptr<IComponent>& component);
    //template <typename T>
    //std::shared_ptr<T> GetComponent();

    IComponent* AddComponent(std::unique_ptr<IComponent> component);
    /*template<typename ComponentType>
    ComponentType* GetComponent();*/
    //std::unique_ptr<IComponent> GetComponent(std::unique_ptr<IComponent> component);
    //NewSpriteComponent* GetNewSpriteComponent() { return dynamic_cast<NewSpriteComponent*>(m_components.back().get()); };

private:
    std::vector<std::unique_ptr<IComponent>> m_components;
    //std::map<std::type_index, std::shared_ptr<IComponent>> m_components;

    //std::unordered_map<std::string, IComponent*> components;
    //std::multimap<std::unique_ptr<IComponent>, int> _componenetID{};
    //std::map<std::unique_ptr<IComponent>, int> _map;
};

#endif //STARFLEET_COMMAND_GAMEOBJECT_HPP
