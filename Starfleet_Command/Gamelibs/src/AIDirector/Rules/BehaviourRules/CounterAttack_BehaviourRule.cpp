#include "AIDirector/Rules/BehaviourRules/CounterAttack_BehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

CounterAttack_BehaviourRule::CounterAttack_BehaviourRule(StarshipFactory::STARSHIP_TYPE starshipTypeToCounter, const std::vector<StarshipFactory::STARSHIP_TYPE>& counterStarshipTypes)
: _starshipTypeToCounter(starshipTypeToCounter), _counterStarshipTypes(counterStarshipTypes)
{
    std::cout << "[CounterAttack_BehaviourRule]: ACTIVE" << std::endl;
}

void CounterAttack_BehaviourRule::ApplyBehaviour(AiDirector &director)
{
    if(director.IsQueueFull())
    {
        return;
    }

    // NOTE: if the behaviour calculation check is called again before a battleship has finished spawning, it will spawn another! This prevents this.
    if(director.IsEnemyStarshipTypeInQueue(_counterStarshipTypes[0]))
    {
        return;
    }

    for (int spacelane = 0; spacelane < director.GetSpacelaneCount(); ++spacelane)
    {
        if(director.GetNumOfPlayerUnitTypesInSpacelane(spacelane, _starshipTypeToCounter) > 0 and
           director.GetNumOfEnemyUnitTypesInSpacelane(spacelane, _counterStarshipTypes[0]) < director.GetNumOfPlayerUnitTypesInSpacelane(spacelane, _starshipTypeToCounter))
        {
            for (auto & counterStarshipType : _counterStarshipTypes)
            {
                director.QueueEnemy(counterStarshipType, spacelane);
            }
        }
    }
}

