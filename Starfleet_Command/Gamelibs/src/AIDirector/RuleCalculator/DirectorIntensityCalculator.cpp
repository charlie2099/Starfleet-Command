#include "AIDirector/RuleCalculator/DirectorIntensityCalculator.hpp"

DirectorIntensityCalculator::DirectorIntensityCalculator()
{
    AddRule(std::make_shared<PlayerMothershipHealthLowRule>(2000.0F, 25.0F));
    AddRule(std::make_shared<EnemyMothershipHealthLowRule>(2000.0F, 25.0F));
}

float DirectorIntensityCalculator::CalculatePerceivedIntensityOutput(AiDirector &director)
{
    DirectorIntensityRuleEngine engine(_rules);
    return engine.CalculatePerceivedIntensityPercentage(director);
}

void DirectorIntensityCalculator::AddRule(const std::shared_ptr<IDirectorIntensityRule>& rule)
{
    _rules.push_back(rule);
}
