#include "AIDirector/RuleCalculator/DirectorBehaviourCalculator.hpp"

DirectorBehaviourCalculator::~DirectorBehaviourCalculator()
{
    _rules.clear();
}

DirectorBehaviourCalculator::DirectorBehaviourCalculator()
{
    AddRule(std::make_shared<SpawnWeakStarshipsAtStart_BehaviourRule>(10, 2));

    AddRule(std::make_shared<CounterAttack_BehaviourRule>(
            StarshipFactory::BATTLESHIP,
            std::vector<StarshipFactory::STARSHIP_TYPE>
            {
                StarshipFactory::BATTLESHIP,
                StarshipFactory::SUPPORT_FRIGATE,
                StarshipFactory::LIGHTFIGHTER
            }));
    AddRule(std::make_shared<PlayerSpacelaneDominance_BehaviourRule>(2, 1));
}

void DirectorBehaviourCalculator::EvaluateBehaviourOutput(AiDirector &director)
{
    //DirectorBehaviourRuleEngine engine((std::vector<std::shared_ptr<IDirectorBehaviourRule>>(_rules)));
    DirectorBehaviourRuleEngine engine(_rules);
    engine.EvaluateBehaviourOutput(director);
}

void DirectorBehaviourCalculator::AddRule(const std::shared_ptr<IDirectorBehaviourRule>& rule)
{
    _rules.push_back(rule);
}
