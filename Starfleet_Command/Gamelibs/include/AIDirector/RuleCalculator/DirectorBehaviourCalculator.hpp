#ifndef STARFLEET_COMMAND_DIRECTORBEHAVIOURCALCULATOR_HPP
#define STARFLEET_COMMAND_DIRECTORBEHAVIOURCALCULATOR_HPP
#include "AIDirector/RuleEngine/DirectorBehaviourRuleEngine.hpp"
#include "AIDirector/Rules/BehaviourRules/SpawnWeakStarshipsAtStartRule.hpp"
#include "AIDirector/Rules/BehaviourRules/TestBehaviourRule.hpp"
#include <memory>
#include <vector>

class AiDirector;

class DirectorBehaviourCalculator
{
public:
    DirectorBehaviourCalculator();
    void ApplyBehaviourOutput(AiDirector& director);

private:
    void AddRule(const std::shared_ptr<IDirectorBehaviourRule>& rule);
    std::vector<std::shared_ptr<IDirectorBehaviourRule>> _rules;
};

#endif //STARFLEET_COMMAND_DIRECTORBEHAVIOURCALCULATOR_HPP
