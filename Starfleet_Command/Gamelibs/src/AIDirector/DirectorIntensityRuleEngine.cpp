#include "AIDirector/DirectorIntensityRuleEngine.hpp"

DirectorIntensityRuleEngine::DirectorIntensityRuleEngine(std::vector<std::shared_ptr<IDirectorIntensityRule>> &rules)
: _rules(rules) {}

float DirectorIntensityRuleEngine::CalculatePerceivedIntensityPercentage(AiDirector &director)
{
    float intensity = 0;
    for (auto & _rule : _rules)
    {
        // Applies the rule which outputs the greatest intensity weighting
        intensity = std::max(intensity, _rule->CalculatePerceivedIntensity(director));
    }
    return intensity;
}
