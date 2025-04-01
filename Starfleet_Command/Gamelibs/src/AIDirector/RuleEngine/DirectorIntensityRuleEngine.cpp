#include "AIDirector/RuleEngine/DirectorIntensityRuleEngine.hpp"

DirectorIntensityRuleEngine::DirectorIntensityRuleEngine(std::vector<std::shared_ptr<IDirectorIntensityRule>> &rules)
: _rules(rules) {}

float DirectorIntensityRuleEngine::CalculatePerceivedIntensityPercentage(AiDirector &director)
{
    float intensity = 0;
    for (auto & _rule : _rules)
    {
        // Applies the rule which outputs the greatest intensity weighting
        //intensity = std::max(intensity, _rule->CalculatePerceivedIntensity(director));

        // Applies all rules where their conditions have been met and sum's their intensity values
        intensity += _rule->CalculatePerceivedIntensity(director);

        //intensity = director.ApplyIntensityCalculationStrategy()
    }
    return intensity;
}
