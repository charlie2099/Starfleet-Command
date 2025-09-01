#include "AIDirector/RuleEngine/DirectorBehaviourRuleEngine.hpp"

DirectorBehaviourRuleEngine::DirectorBehaviourRuleEngine(const std::vector<std::shared_ptr<IDirectorBehaviourRule>>& rules)
: _rules(rules) {}

void DirectorBehaviourRuleEngine::EvaluateBehaviourOutput(AiDirector &director)
{
    auto sortedRulesByHighestPriorityValueFirst = _rules;
    std::sort(sortedRulesByHighestPriorityValueFirst.begin(), sortedRulesByHighestPriorityValueFirst.end(), [](const std::shared_ptr<IDirectorBehaviourRule>& a, const std::shared_ptr<IDirectorBehaviourRule>& b){ return a->GetPriority() > b->GetPriority(); });

    std::shared_ptr<IDirectorBehaviourRule> fallback_rule;

    for (auto & rule : sortedRulesByHighestPriorityValueFirst)
    {

        if (rule->GetID() == "Initial Assault") {
            rule->Execute(director);
            std::cout << rule->GetID() << " rule was executed successfully! | Rule Priority: " << rule->GetPriority() << " | Total Rules Executed So Far: " << ++_numOfRulesSuccessfullyExecuted << std::endl;
            break;
        }

        if (fallback_rule == nullptr && rule->IsValid(director))
        {
            fallback_rule = rule;
        }

        auto priority_chance_picker = rule->GetPriority();
        auto rand_ = rnd.GenerateNumber();

        std::cout << std::to_string((rand_ + priority_chance_picker + 2)) + " / " + std::to_string(6) << std::endl;

        if ((rand_ + priority_chance_picker + 2) >= 7)
        {
            rule->Execute(director);
            std::cout << rule->GetID() << " rule was executed successfully! | Rule Priority: " << rule->GetPriority() << " | Total Rules Executed So Far: " << ++_numOfRulesSuccessfullyExecuted << std::endl;
            break;
        }

        if (rule == sortedRulesByHighestPriorityValueFirst.back())
        {
            fallback_rule->Execute(director);
            std::cout << fallback_rule->GetID() << " rule was executed successfully! | Rule Priority: " << fallback_rule->GetPriority() << " | Total Rules Executed So Far: " << ++_numOfRulesSuccessfullyExecuted << std::endl;
        }

    }
}
