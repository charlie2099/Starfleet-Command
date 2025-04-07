#include <iostream>
#include "AIDirector/RuleEngine/DirectorBehaviourRuleEngine.hpp"

DirectorBehaviourRuleEngine::DirectorBehaviourRuleEngine(const std::vector<std::shared_ptr<IDirectorBehaviourRule>>& rules)
        : _rules(rules) {}

void DirectorBehaviourRuleEngine::EvaluateBehaviourOutput(AiDirector &director)
{
    for (auto & _rule : _rules)
    {
        if(_rule == nullptr)
        {
            std::cout << "Error: Null rule encountered!" << std::endl;
            return;
        }

        // Applies all rules where their conditions have been met
        _rule->ApplyBehaviour(director);

        //auto choice = std::min(_rule, _rule.priority)
    }
}
