#include "AIDirector/RuleEngine/DirectorIntensityRuleEngine.hpp"

DirectorIntensityRuleEngine::DirectorIntensityRuleEngine(const std::vector<std::shared_ptr<IDirectorIntensityRule>> &rules)
: _rules(rules) {}

float DirectorIntensityRuleEngine::CalculatePerceivedIntensitySum(AiDirector &director)
{
    float intensity = 0;
    for (auto & rule : _rules)
    {
        // Applies the rule which outputs the greatest intensity weighting
        //intensity = std::max(intensity, _rule->CalculatePerceivedIntensity(director));

        if(rule->IsValid(director))
        {
            // Applies all valid rules and sum's their intensity values
            intensity += rule->CalculatePerceivedIntensity(director);
        }

        //intensity = director.ApplyIntensityCalculationStrategy()
    }
    return intensity;
}
