#ifndef STARFLEET_COMMAND_DIRECTORBEHAVIOURRULESEVALUATOR_HPP
#define STARFLEET_COMMAND_DIRECTORBEHAVIOURRULESEVALUATOR_HPP
#include "AIDirector/RuleEngine/DirectorBehaviourRuleEngine.hpp"
#include "AIDirector/Rules/BehaviourRules/SpawnWeakStarshipsAtStart_BehaviourRule.hpp"
#include "AIDirector/Rules/BehaviourRules/CounterAttack_BehaviourRule.hpp"
#include "AIDirector/Rules/BehaviourRules/PlayerSpacelaneDominance_BehaviourRule.hpp"
#include <memory>
#include <vector>

class AiDirector;

class DirectorBehaviourRulesEvaluator
{
public:
    DirectorBehaviourRulesEvaluator();
    ~DirectorBehaviourRulesEvaluator();
    void EvaluateBehaviourOutput(AiDirector& director);

private:
    void AddRule(const std::shared_ptr<IDirectorBehaviourRule>& rule);
    std::vector<std::shared_ptr<IDirectorBehaviourRule>> _rules;
};

#endif //STARFLEET_COMMAND_DIRECTORBEHAVIOURRULESEVALUATOR_HPP
