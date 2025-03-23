#ifndef STARFLEET_COMMAND_DIRECTORINTENSITYRULEENGINE_HPP
#define STARFLEET_COMMAND_DIRECTORINTENSITYRULEENGINE_HPP
#include "IDirectorIntensityRule.hpp"
#include <memory>
#include <vector>

// Forward declaration to avoid circular dependency issue
class AiDirector;

class DirectorIntensityRuleEngine
{
public:
    explicit DirectorIntensityRuleEngine(std::vector<std::shared_ptr<IDirectorIntensityRule>>& rules)
    : _rules(rules) {}

    float CalculatePerceivedIntensityPercentage(AiDirector& director)
    {
        float intensity = 0;
        for (auto & _rule : _rules)
        {
            // Applies the rule which outputs the greatest intensity weighting
            intensity = std::max(intensity, _rule->CalculatePerceivedIntensity(director));
        }
        return intensity;
    }

private:
    std::vector<std::shared_ptr<IDirectorIntensityRule>> _rules;
};

#endif //STARFLEET_COMMAND_DIRECTORINTENSITYRULEENGINE_HPP
