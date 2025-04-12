#ifndef STARFLEET_COMMAND_PLAYERSPACELANEDOMINANCE_BEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_PLAYERSPACELANEDOMINANCE_BEHAVIOURRULE_HPP
#include "IDirectorBehaviourRule.hpp"
#include <vector>

class PlayerSpacelaneDominance_BehaviourRule : public IDirectorBehaviourRule
{
public:
    explicit PlayerSpacelaneDominance_BehaviourRule(int maxPlayerStarshipsInLane, int maxSpawnCount);
    bool IsValid(AiDirector& director) override;
    void Execute(AiDirector& director) override;

private:
    int _numOfPlayerStarshipsInLaneThreshold;
    std::vector<int> _validLanes;
    int _maxSpawnCount;
    int _targetSpacelane;
    //RNG _randomWeakStarship { 0, 1 };
    //RNG _randomLane { 0, 4 };
};
#endif //STARFLEET_COMMAND_PLAYERSPACELANEDOMINANCE_BEHAVIOURRULE_HPP
