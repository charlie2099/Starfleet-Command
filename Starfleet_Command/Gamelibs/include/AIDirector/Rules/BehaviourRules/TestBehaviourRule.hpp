#ifndef STARFLEET_COMMAND_TESTBEHAVIOURRULE_HPP
#define STARFLEET_COMMAND_TESTBEHAVIOURRULE_HPP
#include "IDirectorBehaviourRule.hpp"

class TestBehaviourRule : public IDirectorBehaviourRule
{
public:
    TestBehaviourRule();
    void ApplyBehaviour(AiDirector& director) override;

private:
};

#endif //STARFLEET_COMMAND_TESTBEHAVIOURRULE_HPP
