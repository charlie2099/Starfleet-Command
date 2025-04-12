#include "AIDirector/RuleEngine/DirectorBehaviourRuleEngine.hpp"

DirectorBehaviourRuleEngine::DirectorBehaviourRuleEngine(const std::vector<std::shared_ptr<IDirectorBehaviourRule>>& rules)
        : _rules(rules) {}

void DirectorBehaviourRuleEngine::EvaluateBehaviourOutput(AiDirector &director)
{
    for (auto & rule : _rules)
    {
        if(rule->IsValid(director))
        {
            rule->Execute(director);
        }

        //auto choice = std::min(_rule, _rule.priority)
    }
}
