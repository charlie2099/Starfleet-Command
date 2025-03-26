#ifndef STARFLEET_COMMAND_SPAWNWEAKSTARSHIPSATSTARTRULE_HPP
#define STARFLEET_COMMAND_SPAWNWEAKSTARSHIPSATSTARTRULE_HPP
#include "IDirectorBehaviourRule.hpp"
#include "Utility/RNG.hpp"

class SpawnWeakStarshipsAtStartRule : public IDirectorBehaviourRule
{
public:
    explicit SpawnWeakStarshipsAtStartRule(int spawnCount);
    void ApplyBehaviour(AiDirector& director) override;

private:
    int _spawnCount;
    RNG _randomWeakStarship { 0, 2 };
    RNG _randomLane { 0, 4 };
};

#endif //STARFLEET_COMMAND_SPAWNWEAKSTARSHIPSATSTARTRULE_HPP
