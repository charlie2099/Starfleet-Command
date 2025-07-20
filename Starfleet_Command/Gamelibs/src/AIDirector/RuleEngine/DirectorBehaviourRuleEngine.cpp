#include "AIDirector/RuleEngine/DirectorBehaviourRuleEngine.hpp"

DirectorBehaviourRuleEngine::DirectorBehaviourRuleEngine(const std::vector<std::shared_ptr<IDirectorBehaviourRule>>& rules)
: _rules(rules) {}

void DirectorBehaviourRuleEngine::EvaluateBehaviourOutput(AiDirector &director)
{
    auto sortedRulesByHighestPriorityValueFirst = _rules;
    std::sort(sortedRulesByHighestPriorityValueFirst.begin(), sortedRulesByHighestPriorityValueFirst.end(), [](const std::shared_ptr<IDirectorBehaviourRule>& a, const std::shared_ptr<IDirectorBehaviourRule>& b){ return a->GetPriority() > b->GetPriority(); });

    for (auto & rule : sortedRulesByHighestPriorityValueFirst)
    {
        if (rule->GetID() == "Initial Assault") {
            rule->Execute(director);
            std::cout << rule->GetID() << " rule was executed successfully! | Rule Priority: " << rule->GetPriority() << " | Total Rules Executed So Far: " << ++_numOfRulesSuccessfullyExecuted << std::endl;
            break;
        }

        auto priority_chance_picker = 2 + rule->GetPriority();
        auto rand_ = rnd.GenerateNumber();

        std::cout << std::to_string(rand_) + " / " + std::to_string(priority_chance_picker) << std::endl;

        if (rand_ >= priority_chance_picker)
        {
            rule->Execute(director);
            std::cout << rule->GetID() << " rule was executed successfully! | Rule Priority: " << rule->GetPriority() << " | Total Rules Executed So Far: " << ++_numOfRulesSuccessfullyExecuted << std::endl;
            break;
        }
    }
}
