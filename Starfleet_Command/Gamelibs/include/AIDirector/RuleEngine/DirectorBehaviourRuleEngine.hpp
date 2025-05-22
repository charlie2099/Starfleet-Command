#ifndef STARFLEET_COMMAND_DIRECTORBEHAVIOURRULEENGINE_HPP
#define STARFLEET_COMMAND_DIRECTORBEHAVIOURRULEENGINE_HPP
#include "AIDirector/Rules/BehaviourRules/IDirectorBehaviourRule.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class AiDirector;

class DirectorBehaviourRuleEngine
{
public:
    explicit DirectorBehaviourRuleEngine(const std::vector<std::shared_ptr<IDirectorBehaviourRule>>& rules);
    void EvaluateBehaviourOutput(AiDirector& director);

private:
    std::vector<std::shared_ptr<IDirectorBehaviourRule>> _rules;
    int _numOfRulesSuccessfullyExecuted = 0;
};

#endif //STARFLEET_COMMAND_DIRECTORBEHAVIOURRULEENGINE_HPP
