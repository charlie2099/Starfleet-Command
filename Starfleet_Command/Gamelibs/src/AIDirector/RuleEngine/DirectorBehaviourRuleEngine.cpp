#include "AIDirector/RuleEngine/DirectorBehaviourRuleEngine.hpp"

DirectorBehaviourRuleEngine::DirectorBehaviourRuleEngine(std::vector<std::shared_ptr<IDirectorBehaviourRule>> &rules)
        : _rules(rules) {}

void DirectorBehaviourRuleEngine::EvaluateBehaviourOutput(AiDirector &director)
{
    for (auto & _rule : _rules)
    {
        // Applies all rules where their conditions have been met
        _rule->ApplyBehaviour(director);

        //auto choice = std::min(_rule, _rule.priority)
    }
}
