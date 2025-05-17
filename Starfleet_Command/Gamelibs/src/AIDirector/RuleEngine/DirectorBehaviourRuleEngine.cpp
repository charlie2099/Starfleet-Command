#include "AIDirector/RuleEngine/DirectorBehaviourRuleEngine.hpp"

DirectorBehaviourRuleEngine::DirectorBehaviourRuleEngine(const std::vector<std::shared_ptr<IDirectorBehaviourRule>>& rules)
: _rules(rules) {}

void DirectorBehaviourRuleEngine::EvaluateBehaviourOutput(AiDirector &director)
{
    auto sortedRulesByPriority = _rules;
    std::sort(sortedRulesByPriority.begin(), sortedRulesByPriority.end(), [](const std::shared_ptr<IDirectorBehaviourRule>& a, const std::shared_ptr<IDirectorBehaviourRule>& b){ return a->GetPriority() < b->GetPriority(); });

    for (auto & rule : sortedRulesByPriority)
    {
        if(rule->IsValid(director))
        {
            rule->Execute(director);
            std::cout << rule->GetID() << " rule was executed successfully! Priority: " << rule->GetPriority() << std::endl;
            break;
        }
    }
}
