#include <utility>

#include "AIDirector/Rules/BehaviourRules/CounterAttack_BehaviourRule.hpp"
#include "AIDirector/AiDirector.hpp"

CounterAttack_BehaviourRule::CounterAttack_BehaviourRule(StarshipFactory::STARSHIP_TYPE starshipTypeToCounter, const std::vector<StarshipFactory::STARSHIP_TYPE>& counterStarshipTypes, std::string ruleID, int rulePriority)
: _starshipTypeToCounter(starshipTypeToCounter), _counterStarshipTypes(counterStarshipTypes), _id(std::move(ruleID)), _priority(rulePriority)
{}

bool CounterAttack_BehaviourRule::IsValid(AiDirector &director)
{
    if(director.IsQueueFull())
    {
        return false;
    }

    bool isCounterStarshipAlreadyQueued = director.IsEnemyStarshipTypeInQueue(_counterStarshipTypes[0]);
    if(isCounterStarshipAlreadyQueued)
    {
        return false;
    }

    for (int spacelane = 0; spacelane < director.GetSpacelaneCount(); ++spacelane)
    {
        int numOfPlayerUnitTypesInLane = director.GetNumOfPlayerUnitTypesInSpacelane(spacelane, _starshipTypeToCounter);
        int numOfEnemyUnitTypesInLane = director.GetNumOfEnemyUnitTypesInSpacelane(spacelane, _counterStarshipTypes[0]);

        bool isTargetShipsToCounter = numOfPlayerUnitTypesInLane > 0;
        if(! isTargetShipsToCounter)
        {
            continue; // Skip to next iteration in loop
        }

        bool isNumOfEnemyUnitTypesLessThanPlayersInLane = numOfEnemyUnitTypesInLane < numOfPlayerUnitTypesInLane;
        if(isNumOfEnemyUnitTypesLessThanPlayersInLane)
        {
            _targetSpacelane = spacelane;
            return true;
        }
    }

    return false;
}

void CounterAttack_BehaviourRule::Execute(AiDirector &director)
{
    RNG counterAttackRNG;
    auto roll = counterAttackRNG.GenerateRandomRoll();

    switch (roll)
    {
        case RNG::PERFECT_ROLL:
        {
            for (int i = 0; i < _counterStarshipTypes.size(); ++i)
            {
                director.QueueEnemy(_counterStarshipTypes[i], _targetSpacelane);
            }
        }
        break;
        case RNG::COMMON_ROLL:
        {
            int shipsToSpawn = std::max(0, static_cast<int>(_counterStarshipTypes.size() * 0.75F));
            for (int i = 0; i < shipsToSpawn; ++i)
            {
                director.QueueEnemy(_counterStarshipTypes[i], _targetSpacelane);
            }
        }
        break;
        case RNG::POOR_ROLL:
        {
            int shipsToSpawn = std::max(0, static_cast<int>(_counterStarshipTypes.size() * 0.50));
            for (int i = 0; i < shipsToSpawn; ++i)
            {
                director.QueueEnemy(_counterStarshipTypes[i], _targetSpacelane);
            }
        }
        break;
    }
}
