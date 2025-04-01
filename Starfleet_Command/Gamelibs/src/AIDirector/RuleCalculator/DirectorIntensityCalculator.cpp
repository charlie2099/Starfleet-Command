#include "AIDirector/RuleCalculator/DirectorIntensityCalculator.hpp"

DirectorIntensityCalculator::DirectorIntensityCalculator()
{
    // Positive intensity factors
    AddRule(std::make_shared<PlayerMothershipHealthLow_IntensityRule>(2000.0F, 25.0F));
    AddRule(std::make_shared<EnemyStarshipsInPlay_IntensityRule>(0.25F));
    //AddRule(std::make_shared<PlayerScrapSurplus_IntensityRule>(2000, 1.0F));

    // Negative intensity factors
    AddRule(std::make_shared<EnemyMothershipHealthLow_IntensityRule>(2000.0F, -25.0F));
    AddRule(std::make_shared<PlayerStarshipsInPlay_IntensityRule>(-0.25F));
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
