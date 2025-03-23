#ifndef STARFLEET_COMMAND_DIRECTORINTENSITYCALCULATOR_HPP
#define STARFLEET_COMMAND_DIRECTORINTENSITYCALCULATOR_HPP
#include "DirectorIntensityRuleEngine.hpp"
#include "MothershipHealthLowRule.hpp"
#include <memory>
#include <vector>

// Forward declaration to avoid circular dependency issue
class AiDirector;

class DirectorIntensityCalculator
{
public:
    DirectorIntensityCalculator()
    {
        _rules.push_back(std::make_shared<MothershipHealthLowRule>(0,0));
    }

    float CalculatePerceivedIntensityOutput(AiDirector& director)
    {
        DirectorIntensityRuleEngine engine(_rules);
        return engine.CalculatePerceivedIntensityPercentage(director);
    }

private:
    std::vector<std::shared_ptr<IDirectorIntensityRule>> _rules;
};

#endif //STARFLEET_COMMAND_DIRECTORINTENSITYCALCULATOR_HPP
