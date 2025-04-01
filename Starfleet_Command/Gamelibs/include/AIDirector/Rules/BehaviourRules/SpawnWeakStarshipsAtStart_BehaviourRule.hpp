#ifndef STARFLEET_COMMAND_SPAWNWEAKSTARSHIPSATSTART_BEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_SPAWNWEAKSTARSHIPSATSTART_BEHAVIOURRULE_HPP
#include "IDirectorBehaviourRule.hpp"
#include "Utility/RNG.hpp"

class SpawnWeakStarshipsAtStart_BehaviourRule : public IDirectorBehaviourRule
{
public:
    explicit SpawnWeakStarshipsAtStart_BehaviourRule(float timePassedUntilSpawn, int spawnCount);
    void ApplyBehaviour(AiDirector& director) override;

private:
    int _spawnCount;
    float _timePassedUntilSpawn;
    RNG _randomWeakStarship { 0, 1 };
    RNG _randomLane { 0, 4 };
};

#endif //STARFLEET_COMMAND_SPAWNWEAKSTARSHIPSATSTART_BEHAVIOURRULE_HPP
