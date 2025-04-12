#include "AIDirector/RuleCalculator/DirectorBehaviourRulesEvaluator.hpp"

DirectorBehaviourRulesEvaluator::~DirectorBehaviourRulesEvaluator()
{
    _rules.clear();
}

DirectorBehaviourRulesEvaluator::DirectorBehaviourRulesEvaluator()
{
    AddRule(std::make_shared<SpawnWeakStarshipsAtStart_BehaviourRule>(10, 3));

    auto starshipToCounter = StarshipFactory::BATTLESHIP;
    auto counterStarships = std::vector<StarshipFactory::STARSHIP_TYPE> { StarshipFactory::BATTLESHIP, StarshipFactory::SUPPORT_FRIGATE, StarshipFactory::LIGHTFIGHTER };
    AddRule(std::make_shared<CounterAttack_BehaviourRule>(starshipToCounter, counterStarships));

    auto starshipToCounter2 = StarshipFactory::DREADNOUGHT;
    auto counterStarships2 = std::vector<StarshipFactory::STARSHIP_TYPE> { StarshipFactory::DREADNOUGHT, StarshipFactory::SUPPORT_FRIGATE};
    AddRule(std::make_shared<CounterAttack_BehaviourRule>(starshipToCounter2, counterStarships2));

    AddRule(std::make_shared<PlayerSpacelaneDominance_BehaviourRule>(2, 1));
}

void DirectorBehaviourRulesEvaluator::EvaluateBehaviourOutput(AiDirector &director)
{
    //DirectorBehaviourRuleEngine engine((std::vector<std::shared_ptr<IDirectorBehaviourRule>>(_rules)));
    DirectorBehaviourRuleEngine engine(_rules);
    engine.EvaluateBehaviourOutput(director);
}

void DirectorBehaviourRulesEvaluator::AddRule(const std::shared_ptr<IDirectorBehaviourRule>& rule)
{
    _rules.push_back(rule);
}
