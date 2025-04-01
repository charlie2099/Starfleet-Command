#include "AIDirector/Rules/BehaviourRules/SpawnWeakStarshipsAtStart_BehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

SpawnWeakStarshipsAtStart_BehaviourRule::SpawnWeakStarshipsAtStart_BehaviourRule(float timePassedUntilSpawn, int spawnCount)
: _timePassedUntilSpawn(timePassedUntilSpawn), _spawnCount(spawnCount) {}

void SpawnWeakStarshipsAtStart_BehaviourRule::ApplyBehaviour(AiDirector &director)
{
    if(director.GetElapsedGameTime() <= _timePassedUntilSpawn) // NOTE: Make sure time passed is above the director's calculation rate?
    {
        for (int i = 0; i < _spawnCount; ++i)
        {
            director.QueueEnemy(StarshipFactory::STARSHIP_TYPE(_randomWeakStarship.GenerateNumber()), _randomLane.GenerateNumber());
        }
    }
}