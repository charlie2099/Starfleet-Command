#ifndef STARFLEET_COMMAND_UNIT_HPP
#define STARFLEET_COMMAND_UNIT_HPP
#include "Components/SpriteComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/WeaponComponent.hpp"
#include "Interfaces/IBehaviour.hpp"

class Unit
{
public:
    void AddBehaviour(std::unique_ptr<IBehaviour> behaviour);
    void AddWeapon(int weapon);

    const SpriteComponent &GetSpriteComponent() { return m_spriteComponent; };
    const HealthComponent &GetHealthComponent() { return m_healthComponent; };
    const WeaponComponent &GetWeaponComponent() { return m_weaponComponent; };
    const std::vector<std::unique_ptr<IBehaviour>> &GetBehaviours() { return m_behaviours; };

private:
    SpriteComponent m_spriteComponent;
    HealthComponent m_healthComponent;
    WeaponComponent m_weaponComponent;
    std::vector<std::unique_ptr<IBehaviour>> m_behaviours;
    std::vector<int> m_weapons;
    int m_damage;
};

//starship.AddBehaviour(Chase);
//starship.AddWeapon(plasmaCannon);
//starship.GetWeaponComponent().AddWeapon();

#endif //STARFLEET_COMMAND_UNIT_HPP
