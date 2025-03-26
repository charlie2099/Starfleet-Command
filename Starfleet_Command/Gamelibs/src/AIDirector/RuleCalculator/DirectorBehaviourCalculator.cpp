#include "AIDirector/RuleCalculator/DirectorBehaviourCalculator.hpp"

DirectorBehaviourCalculator::DirectorBehaviourCalculator()
{
    AddRule(std::make_shared<SpawnWeakStarshipsAtStartRule>(3));
    AddRule(std::make_shared<TestBehaviourRule>());
}

void DirectorBehaviourCalculator::ApplyBehaviourOutput(AiDirector &director)
{
    DirectorBehaviourRuleEngine engine(_rules);
    return engine.ApplyBehaviourOutput(director);
}

void DirectorBehaviourCalculator::AddRule(const std::shared_ptr<IDirectorBehaviourRule>& rule)
{
    _rules.push_back(rule);
}