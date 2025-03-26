#include "SpawnWeakStarshipsAtStartRule.hpp"
#include "AIDirector/AiDirector.hpp"

SpawnWeakStarshipsAtStartRule::SpawnWeakStarshipsAtStartRule(int spawnCount)
: _spawnCount(spawnCount) {}

void SpawnWeakStarshipsAtStartRule::ApplyBehaviour(AiDirector &director)
{
    if(director.GetElapsedGameTime() <= 5)
    {
        for (int i = 0; i < _spawnCount; ++i)
        {
            director.SpawnEnemy(StarshipFactory::STARSHIP_TYPE(_randomWeakStarship.GenerateNumber()), _randomLane.GenerateNumber());
        }
    }
}