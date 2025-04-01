#include "AIDirector/RuleCalculator/DirectorBehaviourCalculator.hpp"

DirectorBehaviourCalculator::DirectorBehaviourCalculator()
{
    AddRule(std::make_shared<SpawnWeakStarshipsAtStart_BehaviourRule>(10, 5));
}

void DirectorBehaviourCalculator::EvaluateBehaviourOutput(AiDirector &director)
{
    DirectorBehaviourRuleEngine engine(_rules);
    return engine.EvaluateBehaviourOutput(director);
}

void DirectorBehaviourCalculator::AddRule(const std::shared_ptr<IDirectorBehaviourRule>& rule)
{
    _rules.push_back(rule);
}