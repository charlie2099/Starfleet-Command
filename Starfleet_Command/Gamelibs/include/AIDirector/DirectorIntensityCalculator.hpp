#ifndef STARFLEET_COMMAND_DIRECTORINTENSITYCALCULATOR_HPP
#define STARFLEET_COMMAND_DIRECTORINTENSITYCALCULATOR_HPP
#include "DirectorIntensityRuleEngine.hpp"
#include "EnemyMothershipHealthLowRule.hpp"
#include <memory>
#include <vector>

// Forward declaration to avoid circular dependency issue
class AiDirector;

class DirectorIntensityCalculator
{
public:
    DirectorIntensityCalculator();
    float CalculatePerceivedIntensityOutput(AiDirector& director);

private:
    void AddRule(const std::shared_ptr<IDirectorIntensityRule>& rule);
    std::vector<std::shared_ptr<IDirectorIntensityRule>> _rules;
};

#endif //STARFLEET_COMMAND_DIRECTORINTENSITYCALCULATOR_HPP
