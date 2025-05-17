#include "AIDirector/Rules/BehaviourRules/SpawnWeakStarshipsAtStart_BehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

SpawnWeakStarshipsAtStart_BehaviourRule::SpawnWeakStarshipsAtStart_BehaviourRule(float timePassedUntilSpawn, int maxSpawnCount, std::string ruleID, int rulePriority)
: _timePassedUntilSpawn(timePassedUntilSpawn), _maxSpawnCount(maxSpawnCount), _id(std::move(ruleID)), _priority(rulePriority)
{
    RNG _randomSpawnCount {1, maxSpawnCount };
    _maxSpawnCount = _randomSpawnCount.GenerateNumber();
}

bool SpawnWeakStarshipsAtStart_BehaviourRule::IsValid(AiDirector &director)
{
    return director.GetElapsedGameTime() <= _timePassedUntilSpawn; // NOTE: Make sure time passed is above the director's calculation rate?
}

void SpawnWeakStarshipsAtStart_BehaviourRule::Execute(AiDirector &director)
{
    /*RNG weakStarshipsRNG;
    auto roll = weakStarshipsRNG.GenerateRandomRoll();

    switch (roll)
    {
        case RNG::PERFECT_ROLL:
        {

        }
        break;
        case RNG::COMMON_ROLL:
        {

        }
        break;
        case RNG::POOR_ROLL:
        {

        }
        break;
    }*/

    for (int i = 0; i < _maxSpawnCount; ++i)
    {
        director.QueueEnemy(StarshipFactory::STARSHIP_TYPE(_randomWeakStarship.GenerateNumber()), _randomLane.GenerateNumber());
    }
}