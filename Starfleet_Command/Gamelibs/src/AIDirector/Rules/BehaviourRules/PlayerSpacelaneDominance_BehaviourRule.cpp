#include "AIDirector/Rules/BehaviourRules/PlayerSpacelaneDominance_BehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

PlayerSpacelaneDominance_BehaviourRule::PlayerSpacelaneDominance_BehaviourRule(int maxPlayerStarshipsInLane, int maxSpawnCount)
: _maxPlayerStarshipsInLane(maxPlayerStarshipsInLane), _maxSpawnCount(maxSpawnCount)
{
    std::cout << "[PlayerSpacelaneDominance_BehaviourRule]: ACTIVE" << std::endl;
}

void PlayerSpacelaneDominance_BehaviourRule::ApplyBehaviour(AiDirector &director)
{
    /*if(director.GetNumOfEnemyUnitsInSpacelane(0) >= director.GetNumOfPlayerUnitsInSpacelane(0))
    {
        return;
    }*/

    if(director.IsQueueFull())
    {
        return;
    }

    // NOTE: if the behaviour calculation check is called again before a lightfighter has finished spawning, it will spawn another! This prevents this.
    if(director.IsEnemyStarshipTypeInQueue(StarshipFactory::LIGHTFIGHTER))
    {
        return;
    }

    for (int spacelane = 0; spacelane < director.GetSpacelaneCount(); ++spacelane)
    {
        if(director.GetNumOfPlayerUnitsInSpacelane(spacelane) >= _maxPlayerStarshipsInLane)
        {
            if(director.GetNumOfEnemyUnitsInSpacelane(spacelane) < _maxPlayerStarshipsInLane)
            {
                director.QueueEnemy(StarshipFactory::LIGHTFIGHTER, spacelane);
            }
        }
    }
}
