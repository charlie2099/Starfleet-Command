#ifndef STARFLEET_COMMAND_STARSHIPCLASS_HPP
#define STARFLEET_COMMAND_STARSHIPCLASS_HPP
#include "Interfaces/IBehaviour.hpp"
#include <iostream>
#include <memory>
#include <vector>

class StarshipClass
{
public:
    StarshipClass(std::string texturePath, int health, int damage, std::unique_ptr<IBehaviour> behaviour);

    template<class T>
    T* GetBehaviour() { return dynamic_cast<T*>(_behaviours.back().get()); }
    std::string GetTexturePath() { return _texturePath; };
    int GetMaxHealth() const { return _maxHealth; };
    int GetDamage() const { return _damage; };

private:
    std::vector<std::unique_ptr<IBehaviour>> _behaviours;
    std::string _texturePath;
    int _maxHealth;
    int _damage;
    //std::vector<std::unique_ptr<IAbility>> _abilities;
    // Command / Action / Behaviour?
    // Animation?
    // Audio?
};

#endif //STARFLEET_COMMAND_STARSHIPCLASS_HPP
