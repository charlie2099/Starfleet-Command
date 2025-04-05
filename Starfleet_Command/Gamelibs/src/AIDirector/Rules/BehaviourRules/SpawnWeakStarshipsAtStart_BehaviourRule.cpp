#include "AIDirector/Rules/BehaviourRules/SpawnWeakStarshipsAtStart_BehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

SpawnWeakStarshipsAtStart_BehaviourRule::SpawnWeakStarshipsAtStart_BehaviourRule(float timePassedUntilSpawn, int maxSpawnCount)
: _timePassedUntilSpawn(timePassedUntilSpawn), _maxSpawnCount(maxSpawnCount)
{
    std::cout << "[SpawnWeakStarshipsAtStart_BehaviourRule]: ACTIVE" << std::endl;
    RNG _randomSpawnCount {1, maxSpawnCount };
    _maxSpawnCount = _randomSpawnCount.GenerateNumber();
}

void SpawnWeakStarshipsAtStart_BehaviourRule::ApplyBehaviour(AiDirector &director)
{
    if(director.GetElapsedGameTime() <= _timePassedUntilSpawn) // NOTE: Make sure time passed is above the director's calculation rate?
    {
        for (int i = 0; i < _maxSpawnCount; ++i)
        {
            director.QueueEnemy(StarshipFactory::STARSHIP_TYPE(_randomWeakStarship.GenerateNumber()), _randomLane.GenerateNumber());
        }
    }
}