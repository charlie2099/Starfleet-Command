#ifndef STARFLEET_COMMAND_PLAYERSPACELANEDOMINANCE_BEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_PLAYERSPACELANEDOMINANCE_BEHAVIOURRULE_HPP
#include "IDirectorBehaviourRule.hpp"
#include <vector>

class PlayerSpacelaneDominance_BehaviourRule : public IDirectorBehaviourRule
{
public:
    explicit PlayerSpacelaneDominance_BehaviourRule(int maxPlayerStarshipsInLane, std::string ruleID, int rulePriority);
    bool IsValid(AiDirector& director) override;
    void Execute(AiDirector& director) override;

    std::string GetID() override { return _id; }
    int GetPriority() override { return _priority; }

private:
    int _numOfPlayerStarshipsInLaneThreshold;
    std::vector<int> _validLanes;
    int _priority = 0;
    std::string _id;
};
#endif //STARFLEET_COMMAND_PLAYERSPACELANEDOMINANCE_BEHAVIOURRULE_HPP
