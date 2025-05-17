#ifndef STARFLEET_COMMAND_SPAWNWEAKSTARSHIPSATSTART_BEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_SPAWNWEAKSTARSHIPSATSTART_BEHAVIOURRULE_HPP
#include "IDirectorBehaviourRule.hpp"
#include "Utility/RNG.hpp"

class SpawnWeakStarshipsAtStart_BehaviourRule : public IDirectorBehaviourRule
{
public:
    explicit SpawnWeakStarshipsAtStart_BehaviourRule(float timePassedUntilSpawn, int maxSpawnCount, std::string ruleID, int rulePriority);
    bool IsValid(AiDirector& director) override;
    void Execute(AiDirector& director) override;

    std::string GetID() override { return _id; }
    int GetPriority() override { return _priority; }

private:
    int _maxSpawnCount;
    float _timePassedUntilSpawn;
    RNG _randomWeakStarship { 0, 1 };
    RNG _randomLane { 0, 4 };
    int _priority = 0;
    std::string _id;
};

#endif //STARFLEET_COMMAND_SPAWNWEAKSTARSHIPSATSTART_BEHAVIOURRULE_HPP
