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
    explicit DirectorIntensityRuleEngine(std::vector<std::shared_ptr<IDirectorIntensityRule>>& rules);
    float CalculatePerceivedIntensityPercentage(AiDirector& director);

private:
    std::vector<std::shared_ptr<IDirectorIntensityRule>> _rules;
};

#endif //STARFLEET_COMMAND_DIRECTORINTENSITYRULEENGINE_HPP
