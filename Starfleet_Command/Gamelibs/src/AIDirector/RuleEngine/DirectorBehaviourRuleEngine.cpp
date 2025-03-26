#include "AIDirector/RuleEngine/DirectorBehaviourRuleEngine.hpp"

DirectorBehaviourRuleEngine::DirectorBehaviourRuleEngine(std::vector<std::shared_ptr<IDirectorBehaviourRule>> &rules)
        : _rules(rules) {}

void DirectorBehaviourRuleEngine::ApplyBehaviourOutput(AiDirector &director)
{
    for (auto & _rule : _rules)
    {
        // Applies every rule when their conditions are met
        _rule->ApplyBehaviour(director);
    }
}
