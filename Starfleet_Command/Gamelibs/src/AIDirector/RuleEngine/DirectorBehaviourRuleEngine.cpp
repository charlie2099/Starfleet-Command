#include "AIDirector/RuleEngine/DirectorBehaviourRuleEngine.hpp"

DirectorBehaviourRuleEngine::DirectorBehaviourRuleEngine(const std::vector<std::shared_ptr<IDirectorBehaviourRule>>& rules)
: _rules(rules) {}

void DirectorBehaviourRuleEngine::EvaluateBehaviourOutput(AiDirector &director)
{
    auto sortedRulesByHighestPriorityValueFirst = _rules;
    std::sort(sortedRulesByHighestPriorityValueFirst.begin(), sortedRulesByHighestPriorityValueFirst.end(), [](const std::shared_ptr<IDirectorBehaviourRule>& a, const std::shared_ptr<IDirectorBehaviourRule>& b){ return a->GetPriority() > b->GetPriority(); });

    for (auto & rule : sortedRulesByHighestPriorityValueFirst)
    {
        if(rule->IsValid(director))
        {
            rule->Execute(director);
            std::cout << rule->GetID() << " rule was executed successfully! | Rule Priority: " << rule->GetPriority() << " | Total Rules Executed So Far: " << ++_numOfRulesSuccessfullyExecuted << std::endl;
            break;
        }
    }
}
